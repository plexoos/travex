#include "travex/Hit.h"

using namespace tvx;


Hit::Hit() : TObject(),
   fPosition(),
   fTimesUsed(0)
{
}


void Hit::Print(Option_t *opt) const
{
   fPosition.Print();
}


bool tvx::operator< (const Hit& lhs, const Hit& rhs)
{
   if (lhs.fPosition.Perp() < rhs.fPosition.Perp() )
      return true;
   else if ( lhs.fPosition.Perp() == rhs.fPosition.Perp() &&
             lhs.fPosition.Z() < rhs.fPosition.Z() )
      return true;
   else
      return false;
}
