#include "travex/Event.h"
#include "travex/Track.h"



/**
 * Constructs an orphan empty Track not associated with any Event.
 */
tvx::Track::Track() : TObject(), GenericTrack(),
   fEvent(nullptr), fNodes(), fEnergyLosses(0)
{
}


tvx::Track::Track(Event* event) : TObject(),
   fEvent(event), fNodes(), fEnergyLosses(0)
{
}


std::pair<std::set<tvx::Hit>::iterator, bool> tvx::Track::AddToParentEvent(const tvx::Hit& stiHit)
{
   std::pair<std::set<tvx::Hit>::iterator, bool> dummy;
   dummy.second = false;

   return fEvent ? fEvent->AddHit(stiHit) : dummy;
}


/**
 * For each node of this track finds the hit closest to the mean track
 * projection.
 */
void tvx::Track::SetClosestHits(const std::set<tvx::Hit>& stiHits)
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
void tvx::Track::FindCandidateHits(const std::set<tvx::Hit>& stiHits)
{
   for (const auto& node : fNodes)
   {
      node.FindCandidateHits(stiHits);
   }
}


void tvx::Track::Print(Option_t *opt) const
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
