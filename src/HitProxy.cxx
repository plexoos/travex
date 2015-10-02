#include "travex/HitProxy.h"
#include "travex/Hit.h"
#include "travex/TrackNode.h"


using namespace tvx;


HitProxy::HitProxy() :
   TObject(),
   fHit(nullptr),
   fTrackNode(nullptr),
   fChi2(-1),
   fDistanceToNode(-1)
{
}


HitProxy::HitProxy(const Hit& hit, const TrackNode& node) :
   TObject(),
   fHit(&hit),
   fTrackNode(&node),
   fChi2(node.CalcChi2(hit)),
   fDistanceToNode(node.CalcDistanceToHit(hit))
{
}


bool tvx::operator< (const HitProxy& lhs, const HitProxy& rhs)
{
   return (lhs.GetDistanceToNode() < rhs.GetDistanceToNode());
}
