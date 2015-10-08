#ifndef tvx_Track_h
#define tvx_Track_h

#include <set>

#include "TObject.h"

#include "travex/GenericTrack.h"
#include "travex/TrackNode.h"


namespace tvx {

class Event;


class Track : public TObject, public GenericTrack<Event>
{
public:

   Track();
   explicit Track(Event* event);

   virtual Event* GetParentEvent() { return fEvent; }
   virtual const std::set<TrackNode>& GetNodes() const { return fNodes; }
   virtual double GetEnergyLosses() const { return fEnergyLosses; }
   virtual AddHitResult AddToParentEvent(const Hit& stiHit);
   virtual void SetClosestHits(const std::set<Hit>& stiHits);
   virtual void FindCandidateHits(const std::set<Hit>& stiHits);
   virtual void Print(Option_t *opt = "") const;

protected:

   /// Pointer to mother event containing this track
   Event  *fEvent;   //!

   /// Container with all available track nodes/states
   std::set<TrackNode> fNodes;

   /// Total track energy lost in all volumes
   double  fEnergyLosses;

   ClassDef(Track, 1)
};

}

#endif
