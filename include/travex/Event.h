#ifndef tvx_Event_h
#define tvx_Event_h

#include <list>
#include <set>

#include "TObject.h"

#include "travex/GenericEvent.h"


namespace tvx {

class Hit;
class Track;


/**
 * A simple persistent event container holding collections of tracks and hits.
 * It is an implementation of an abstract GenericEvent.
 */
class Event : public TObject, public GenericEvent<std::list<Track>, std::set<Hit> >
{
public:

   Event();

   virtual void AddTracks(const TrackContainer_t& tracks) { fTracks = tracks; }
   virtual void AddTrack(const Track& track) { fTracks.push_back(track); }
   virtual const TrackContainer_t& GetTracks() const { return fTracks; }

   virtual void AddHits(const HitContainer_t& hits) { fHits = hits; }
   virtual AddHitResult_t AddHit(const Hit& hit) { return fHits.insert(hit); }
   virtual const HitContainer_t& GetHits() const { return fHits; }

   virtual void Clear(Option_t *opt = "");
   virtual void Print(Option_t *opt = "") const;

protected:

   ///< A collection of all (possibly preselected) tracks in this event
   TrackContainer_t  fTracks;

   ///< A collection of all (possibly preselected) hits in this event
   HitContainer_t  fHits;

   ClassDef(Event, 1)
};

}

#endif
