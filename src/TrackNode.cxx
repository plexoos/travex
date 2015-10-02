#include <algorithm>
#include <cfloat>

#include "travex/TrackNode.h"


using namespace tvx;


TrackNode::TrackNode() : TObject(),
   fTrack(nullptr),
   fPosition(),
   fError(),
   fProjError(),
   fMomentum(),
   fAcceptedHit(nullptr),
   fClosestHit(nullptr),
   fCandidateHits()
{
}


TVector3 TrackNode::CalcPullToHit(const Hit& hit) const
{
   double pullX = fProjError.X() ? (hit.GetPosition().X() - fPosition.X()) / fProjError.X() : 0;
   double pullY = fProjError.Y() ? (hit.GetPosition().Y() - fPosition.Y()) / fProjError.Y() : 0;
   double pullZ = fProjError.Z() ? (hit.GetPosition().Z() - fPosition.Z()) / fProjError.Z() : 0;

   return TVector3(pullX, pullY, pullZ);
}


/**
 * Calculates and returns uncorrelated three components which can be used in the
 * pull distribution.
 */
TVector3 TrackNode::CalcPullClosestHit() const
{
   if (!fClosestHit) return TVector3(DBL_MAX, DBL_MAX, DBL_MAX);

   return CalcPullToHit(*fClosestHit);
}


void TrackNode::Print(Option_t *opt) const
{
   fPosition.Print();
   fMomentum.Print();
}


bool tvx::operator< (const TrackNode& lhs, const TrackNode& rhs)
{
   return lhs.fPosition.Perp() < rhs.fPosition.Perp();
}


std::set<const Hit*> TrackNode::GetCandidateBareHits() const
{
   std::set<const Hit*> candidateHits;

   std::transform(fCandidateHits.begin(), fCandidateHits.end(),
      std::inserter(candidateHits, candidateHits.begin()), HitProxy::GetBareStiHit);

   return candidateHits;
}


void TrackNode::SetClosestHit(const std::set<Hit>& hits) const
{
   TVector3 distVec;
   double min_dist = DBL_MAX;

   for (const auto& hit : hits)
   {
      distVec = GetPosition() - hit.GetPosition();

      double dist = distVec.Mag();
      if (dist < min_dist) {
         min_dist = dist;
         fClosestHit = &hit;
      }
   }
}


/**
 * Finds all hits within a 5x(track_proj_err) vicinity of the track mean
 * projection and fills this node's fCandidateHits collection with pointers
 * to the found hits. Note that the function also among the candidate hist finds
 * the closest hit to the track node position. The hits are selected from the
 * user provided collection hits which should normaly be a collection of hits
 * in the parent event to which the track belongs.
 */
void TrackNode::FindCandidateHits(const std::set<Hit>& hits) const
{
   TVector3 distVec;
   double min_dist = DBL_MAX;

   for (const auto& hit : hits)
   {
      distVec = GetPosition() - hit.GetPosition();

      if (fabs(distVec.Y()) < 5*fProjError.Y() &&
          fabs(distVec.Z()) < 5*fProjError.Z() )
      {
         fCandidateHits.insert(HitProxy(hit, *this));

         double dist = distVec.Mag();
         if (dist < min_dist) {
            min_dist = dist;
            fClosestHit = &hit;
         }
      }
   }
}
