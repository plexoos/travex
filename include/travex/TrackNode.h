#ifndef tvx_TrackNode_h
#define tvx_TrackNode_h

#include <set>
#include <string>

#include "TObject.h"
#include "TVector3.h"

#include "travex/Hit.h"
#include "travex/HitProxy.h"


namespace tvx {

class Track;


class TrackNode : public TObject
{
public:

   TrackNode();

   const TVector3& GetPosition()  const { return fPosition; }
   const TVector3& GetMomentum()  const { return fMomentum; }
   const TVector3& GetError()     const { return fError; }
   const TVector3& GetProjError() const { return fProjError; }
   const Hit* GetAcceptedHit() const { return fAcceptedHit; }
   const Hit* GetClosestHit() const { return fClosestHit; }
   const std::set<HitProxy>& GetCandidateHits() const { return fCandidateHits; }
   std::set<const Hit*> GetCandidateBareHits() const;
   void SetClosestHit(const std::set<Hit>& hits) const;
   void FindCandidateHits(const std::set<Hit>& hits) const;

   double   CalcChi2(const Hit& hit) const { return -1; }
   TVector3 CalcDiffProjToFitError() const { return fProjError - fError; }

   double CalcDistanceToClosestHit() const
   {
      return fClosestHit ? (fClosestHit->GetPosition() - GetPosition()).Mag() : -1;
   }

   double CalcDistanceToHit() const
   {
      return fAcceptedHit ? (fAcceptedHit->GetPosition() - GetPosition()).Mag() : -1;
   }

   double CalcDistanceToHit(const Hit& hit) const
   {
      return (hit.GetPosition() - GetPosition()).Mag();
   }

   TVector3 CalcPullToHit(const Hit& hit) const;
   TVector3 CalcPullClosestHit() const;
   virtual void Print(Option_t *opt = "") const;

   friend bool operator< (const TrackNode& lhs, const TrackNode& rhs);

protected:

   const Track*  fTrack;                        //!< Transient pointer to parent track containing this node
   TVector3      fPosition;                     ///< Coordinates of the track state/node position
   TVector3      fMomentum;                     ///< Track momentum vector in global CS
   TVector3      fError;                        ///< Diagonal elements of error matrix after final fit
   TVector3      fProjError;                    ///< The projection error to the node before the fit
   mutable const Hit* fAcceptedHit;             ///< Pointer to the hit associated with this node by the reconstruction algorithm, if any
   mutable const Hit* fClosestHit;              ///< Pointer to the hit closest to this node if any
   mutable std::set<HitProxy> fCandidateHits;   ///< Collection of hits in some proximity of mean track projection

   ClassDef(TrackNode, 1)
};


bool operator< (const TrackNode& lhs, const TrackNode& rhs);

}


#endif
