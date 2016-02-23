#ifndef tvx_GenericTrack_h
#define tvx_GenericTrack_h


namespace tvx {


/**
 * A templated abstract base class interface with a basic functionality common
 * to all tracks reconstructed by a tracking algorithm.
 */
template<class _GenericEvent, class _TrackNodeContainer>
class GenericTrack
{
public:

   typedef _GenericEvent Event_t;
   typedef typename _GenericEvent::AddHitResult_t AddHitResult_t;
   typedef typename _GenericEvent::HitContainer_t HitContainer_t;
   typedef _TrackNodeContainer TrackNodeContainer_t;

   virtual ~GenericTrack() {}

   virtual Event_t* GetParentEvent() = 0;
   virtual const TrackNodeContainer_t& GetNodes() const = 0;
   virtual double GetEnergyLosses() const = 0;
   virtual AddHitResult_t AddToParentEvent(const typename HitContainer_t::value_type& hit) = 0;
};

}

#endif
