#include "travex/Event.h"
#include "travex/Track.h"



/**
 * Constructs an orphan empty Track not associated with any Event.
 */
tvx::Track::Track() : TObject(),
   fEvent(nullptr),
	fNodes(),
	fEnergyLosses(0)
{
}


/**
 * Constructs a empty Track without track nodes but associated with the provided Event.
 */
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
