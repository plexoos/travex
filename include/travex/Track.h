#ifndef tvx_Track_h
#define tvx_Track_h

#include <set>

#include "TObject.h"

#include "travex/GenericTrack.h"
#include "travex/TrackNode.h"


namespace tvx {

class Event;


class Track : public GenericTrack<Event, std::set<TrackNode> >, public TObject
{
public:

   using TrackNodeContainer_t = typename GenericTrack::TrackNodeContainer_t;

   Track();
   explicit Track(Event* event);

   virtual Event* GetParentEvent() { return fEvent; }
   virtual const TrackNodeContainer_t& GetNodes() const { return fNodes; }
   virtual double GetEnergyLosses() const { return fEnergyLosses; }
   virtual AddHitResult_t AddToParentEvent(const Hit& hit);
   virtual void SetClosestHits(const std::set<Hit>& stiHits);
   virtual void FindCandidateHits(const std::set<Hit>& stiHits);
   virtual void Print(Option_t *opt = "") const;

protected:

   /// Pointer to mother event containing this track
   Event  *fEvent;   //!

   /// Container with all available track nodes/states
   TrackNodeContainer_t fNodes;

   /// Total track energy lost in all volumes
   double  fEnergyLosses;

   ClassDef(Track, 1)
};

}

#endif
