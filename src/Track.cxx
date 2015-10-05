#include "travex/Track.h"
#include "travex/Event.h"


using namespace tvx;


Track::Track() : TObject(),
   fEvent(nullptr), fNodes(), fEnergyLosses(0)
{
}


Track::Track(Event* event) : TObject(),
   fEvent(event), fNodes(), fEnergyLosses(0)
{
}


std::pair<std::set<Hit>::iterator, bool> Track::AddToParentEvent(const Hit& stiHit)
{
   std::pair<std::set<Hit>::iterator, bool> dummy;
   dummy.second = false;

   return fEvent ? fEvent->AddHit(stiHit) : dummy;
}


/**
 * For each node of this track finds the hit closest to the mean track
 * projection.
 */
void Track::SetClosestHits(const std::set<Hit>& stiHits)
{
   for (const auto& node : fNodes)
   {
      node.SetClosestHit(stiHits);
   }
}


/**
 * For each node of this track finds hits in some proximity to the mean track
 * projection.
 */
void Track::FindCandidateHits(const std::set<Hit>& stiHits)
{
   for (const auto& node : fNodes)
   {
      node.FindCandidateHits(stiHits);
   }
}


void Track::Print(Option_t *opt) const
{
   Info("Print", "fEnergyLosses: %f\n", fEnergyLosses);

   int nodeIdx = 0;

   for (const TrackNode& iNode : fNodes)
   {
      Info("Print", "node index: %d\n", nodeIdx);
      iNode.Print();
      nodeIdx++;
   }
}
