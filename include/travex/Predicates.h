#ifndef tvx_Predicates_h
#define tvx_Predicates_h

#include <functional>

namespace tvx {

//class GenericTrackNode;
//class GenericHit;


template<class _GenericTrackNode, class _GenericHit>
struct IsHitWithinError : public std::function<bool(_GenericTrackNode, _GenericHit)>
{
   bool operator() (_GenericTrackNode trackNode, _GenericHit hit)
   {
      return (trackNode.CalcDistanceToHit(hit) <= 5*trackNode.GetError().Mag());
   }

};


}

#endif
