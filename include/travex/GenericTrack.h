#ifndef tvx_GenericTrack_h
#define tvx_GenericTrack_h

#include <set>


namespace tvx {

class Hit;
class TrackNode;


template<class EventClass>
class GenericTrack
{
public:

   using AddHitResult = typename EventClass::AddHitResult;

	virtual ~GenericTrack() {}

   virtual EventClass* GetParentEvent() = 0;
   virtual const std::set<TrackNode>& GetNodes() const = 0;
   virtual double GetEnergyLosses() const = 0;
   virtual AddHitResult AddToParentEvent(const Hit& stiHit) = 0;
   virtual void SetClosestHits(const std::set<Hit>& hits) = 0;
   virtual void FindCandidateHits(const std::set<Hit>& hits) = 0;
};

}

#endif
