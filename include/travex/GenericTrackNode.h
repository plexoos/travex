#ifndef tvx_GenericTrackNode_h
#define tvx_GenericTrackNode_h


namespace tvx {


/**
 * A templated abstract base class interface with a basic functionality common
 * to all track nodes identified by a tracking algorithm.
 *
 * \todo The type (Coordinates_t) for Errors should be renamed of course
 */
template<class _Coordinates, class _TrackNodeHitContainer>
class GenericTrackNode
{
public:

   typedef _Coordinates Coordinates_t;
   typedef _TrackNodeHitContainer TrackNodeHitContainer_t;
   typedef typename _TrackNodeHitContainer::value_type Hit_t;

   virtual ~GenericTrackNode() {}

   virtual const Coordinates_t& GetPosition()  const = 0;
   virtual const Coordinates_t& GetMomentum()  const = 0;
   virtual const Coordinates_t& GetError()     const = 0;
   virtual const Coordinates_t& GetProjError() const = 0;
   virtual const Hit_t* GetAcceptedHit() const = 0;
   virtual const TrackNodeHitContainer_t& GetCandidateHits() const = 0;

   friend bool operator< (const GenericTrackNode& lhs, const GenericTrackNode& rhs)
   {
      return lhs.GetPosition() < rhs.GetPosition();
   }
};


}

#endif
