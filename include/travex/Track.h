#ifndef tvx_Track_h
#define tvx_Track_h

#include <set>

#include "TObject.h"

#include "travex/TrackNode.h"


namespace tvx {

class Event;


class Track : public TObject
{
public:

   Track();
   explicit Track(Event* event);

   const Event* GetParentEvent() const { return fEvent; }
   const std::set<TrackNode>& GetNodes() const { return fNodes; }
   double GetEnergyLosses() const { return fEnergyLosses; }
   std::pair<std::set<Hit>::iterator, bool> AddToParentEvent(const Hit& stiHit);
   void SetClosestHits(const std::set<Hit>& stiHits);
   void FindCandidateHits(const std::set<Hit>& stiHits);
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
