#ifndef tvx_Event_h
#define tvx_Event_h

#include <list>
#include <set>

#include "TObject.h"

#include "travex/GenericEvent.h"
#include "travex/Track.h"
#include "travex/Hit.h"


namespace tvx {


/**
 * A simple persistent event container holding collections of tracks and hits.
 * It is an implementation of an abstract GenericEvent.
 */
class Event : public GenericEvent<std::list<Track>, std::set<Hit> >, public TObject
{
public:

   Event();

   virtual void AddTracks(const TrackContainer& tracks) { fTracks = tracks; }
   virtual void AddTrack(const Track& track) { fTracks.push_back(track); }
   virtual const TrackContainer& GetTracks() const { return fTracks; }

   virtual void AddHits(const HitContainer& hits) { fHits = hits; }
   virtual AddHitResult AddHit(const Hit& hit) { return fHits.insert(hit); }
   virtual const HitContainer& GetHits() const { return fHits; }

   virtual void Clear(Option_t *opt = "");
   virtual void Print(Option_t *opt = "") const;

protected:

   ///< A collection of all (possibly preselected) tracks in this event
   TrackContainer  fTracks;

   ///< A collection of all (possibly preselected) hits in this event
   HitContainer  fHits;

   ClassDef(Event, 1)
};

}

#endif
