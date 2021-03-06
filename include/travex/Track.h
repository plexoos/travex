#ifndef tvx_Track_h
#define tvx_Track_h

#include <set>

#include "TObject.h"

#include "travex/GenericTrack.h"
#include "travex/TrackNode.h"


namespace tvx {

class Event;
class Hit;


/**
 * A simple persistent class describing a reconstructed charged particle track
 * with a collection of track nodes. It is implemented as a specialization of
 * a templated abstract GenericTrack.
 */
class Track : public TObject, public GenericTrack<Event, std::set<TrackNode> >
{
public:

   Track();
   explicit Track(Event* event);

   virtual Event* GetParentEvent() { return fEvent; }
   virtual const TrackNodeContainer_t& GetNodes() const { return fNodes; }
   virtual double GetEnergyLosses() const { return fEnergyLosses; }
   virtual AddHitResult_t AddToParentEvent(const Hit& hit);
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
