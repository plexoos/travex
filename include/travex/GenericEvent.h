#ifndef tvx_GenericEvent_h
#define tvx_GenericEvent_h

#include <utility>


namespace tvx {


/**
 * A templated abstract base class interface with a basic functionality common
 * to all events recorded by a tracking detector.
 */
template<typename _TrackContainer, typename _HitContainer>
class GenericEvent
{
public:

   using TrackContainer = _TrackContainer;
   using HitContainer = _HitContainer;

   using AddHitResult   = std::pair< typename HitContainer::iterator, bool>;

   virtual ~GenericEvent() {}

   virtual void AddTracks(const TrackContainer& tracks) = 0;
   virtual void AddTrack(const typename TrackContainer::value_type& track) = 0;
   virtual const TrackContainer& GetTracks() const = 0;

   virtual void AddHits(const HitContainer& hits) = 0;
   virtual AddHitResult AddHit(const typename HitContainer::value_type& hit) = 0;
   virtual const HitContainer& GetHits() const = 0;
};


}

#endif
