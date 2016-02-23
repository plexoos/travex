#include "travex/Hit.h"
#include "travex/TrackNode.h"



tvx::TrackNode::TrackNode() : TObject(),
   fPosition(),
   fError(),
   fProjError(),
   fMomentum(),
   fAcceptedHit(nullptr),
   fCandidateHits()
{
}


void tvx::TrackNode::Print(Option_t *opt) const
{
   fPosition.Print();
   fMomentum.Print();
}


/**
 * Currently the nodes are ordered based on the transverse coordinates. But in
 * general the sorting should be done along the track.
 */
bool tvx::operator< (const tvx::TrackNode& lhs, const tvx::TrackNode& rhs)
{
   return lhs.fPosition.Perp() < rhs.fPosition.Perp();
}
