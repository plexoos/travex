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

   typedef _TrackContainer TrackContainer_t;
   typedef _HitContainer HitContainer_t;
   typedef std::pair< typename _HitContainer::iterator, bool> AddHitResult_t;

   virtual ~GenericEvent() {}

   virtual void AddTracks(const TrackContainer_t& tracks) = 0;
   virtual void AddTrack(const typename TrackContainer_t::value_type& track) = 0;
   virtual const TrackContainer_t& GetTracks() const = 0;

   virtual void AddHits(const HitContainer_t& hits) = 0;
   virtual AddHitResult_t AddHit(const typename HitContainer_t::value_type& hit) = 0;
   virtual const HitContainer_t& GetHits() const = 0;
};

}

#endif
