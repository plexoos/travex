#ifndef tvx_GenericTrack_h
#define tvx_GenericTrack_h


namespace tvx {


template<class _GenericEvent, class _TrackNodeContainer>
class GenericTrack
{
public:

   using Event_t = _GenericEvent;
   using AddHitResult_t = typename _GenericEvent::AddHitResult_t;
   using HitContainer_t = typename _GenericEvent::HitContainer_t;
   using TrackNodeContainer_t = _TrackNodeContainer;

	virtual ~GenericTrack() {}

   virtual Event_t* GetParentEvent() = 0;
   virtual const TrackNodeContainer_t& GetNodes() const = 0;
   virtual double GetEnergyLosses() const = 0;
   virtual AddHitResult_t AddToParentEvent(const typename HitContainer_t::value_type& hit) = 0;
};

}

#endif
