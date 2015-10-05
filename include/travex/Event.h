#ifndef tvx_Event_h
#define tvx_Event_h

#include <vector>
#include <set>

#include "TObject.h"

#include "travex/Track.h"
#include "travex/Hit.h"


namespace tvx {


class Event : public TObject
{
public:

   Event();

   virtual void Clear(Option_t *opt = "");
   virtual void Print(Option_t *opt = "") const;
   std::pair<std::set<Hit>::iterator, bool>  AddHit(const Hit &stiHit) { return fHits.insert(stiHit); }
   const std::vector<Track>& GetTracks() const { return fTracks; }
   const std::set<Hit>& GetStiHits() const { return fHits; }

protected:

   ///< A collection of all (possibly preselected) tracks in this event
   std::vector<Track>  fTracks;

   ///< A collection of all (possibly preselected) hits in this event
   std::set<Hit>  fHits;

   ClassDef(Event, 1)
};

}

#endif
