#ifndef tvx_TrackNode_h
#define tvx_TrackNode_h

#include <set>
#include <string>

#include "TObject.h"
#include "TVector3.h"

#include "travex/Hit.h"
#include "travex/GenericTrackNode.h"


namespace tvx {



class TrackNode : public TObject, public GenericTrackNode<TVector3, std::set<Hit> >
{
public:

   using Hit_t = typename TrackNodeHitContainer_t::value_type;

   TrackNode();

   const TVector3& GetPosition()  const { return fPosition; }
   const TVector3& GetMomentum()  const { return fMomentum; }
   const TVector3& GetError()     const { return fError; }
   const TVector3& GetProjError() const { return fProjError; }
   const Hit_t* GetAcceptedHit() const { return fAcceptedHit; }
   const TrackNodeHitContainer_t& GetCandidateHits() const { return fCandidateHits; }

   virtual void Print(Option_t *opt = "") const;

   friend bool operator< (const TrackNode& lhs, const TrackNode& rhs);

protected:

   TVector3      fPosition;          ///< Coordinates of the track state/node position
   TVector3      fMomentum;          ///< Track momentum vector in global CS
   TVector3      fError;             ///< Diagonal elements of error matrix after final fit
   TVector3      fProjError;         ///< The projection error to the node before the fit
   const Hit_t*  fAcceptedHit;       ///< Pointer to the hit associated with this node by the reconstruction algorithm, if any
   TrackNodeHitContainer_t fCandidateHits;   ///< Collection of hits in some proximity of mean track projection

   ClassDef(TrackNode, 1)
};


bool operator< (const TrackNode& lhs, const TrackNode& rhs);

}


#endif
