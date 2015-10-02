#ifndef tvx_HitProxy_h
#define tvx_HitProxy_h

#include "TObject.h"


namespace tvx {

class TrackNode;
class Hit;


class HitProxy : public TObject
{
public:

   HitProxy();
   HitProxy(const Hit& hit, const TrackNode& node);

   const Hit* GetHit() const { return fHit; }
   double     GetChi2() const { return fChi2; }
   double     GetDistanceToNode() const { return fDistanceToNode; }

   static const Hit* GetBareStiHit(const HitProxy& hitProxy) { return hitProxy.fHit; }
   friend bool operator< (const HitProxy& lhs, const HitProxy& rhs);

private:

   const Hit* fHit;               ///< Pointer to the hit in question
   const TrackNode* fTrackNode;   //!< Pointer to Sti node
   double fChi2;                  ///< Chi2 for this hit and the track node it was associated with
   double fDistanceToNode;

   ClassDef(HitProxy, 1)
};


bool operator< (const HitProxy& lhs, const HitProxy& rhs);

}

#endif
