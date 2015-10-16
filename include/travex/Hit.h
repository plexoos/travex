#ifndef tvx_Hit_h
#define tvx_Hit_h

#include "TObject.h"
#include "TVector3.h"

#include "GenericHit.h"


namespace tvx {


class Hit : public GenericHit<TVector3>, public TObject
{
public:

   Hit();
   const TVector3& GetPosition() const { return fPosition; }
   virtual void Print(Option_t *opt = "") const;

   friend bool operator< (const Hit& lhs, const Hit& rhs);

private:

   TVector3       fPosition;       ///< Global coordinates of the hit in the STAR CS
   std::uint8_t   fTimesUsed;      ///< The number of tracks this hit was assigned to

   ClassDef(Hit, 1)
};


bool operator< (const tvx::Hit& lhs, const tvx::Hit& rhs);

}


#endif
