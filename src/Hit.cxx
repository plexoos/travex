#include "travex/Hit.h"



tvx::Hit::Hit() : TObject(),
   fPosition(),
   fTimesUsed(0)
{
}


void tvx::Hit::Print(Option_t *opt) const
{
   fPosition.Print();
}


bool tvx::operator< (const tvx::Hit& lhs, const tvx::Hit& rhs)
{
   if (lhs.fPosition.Perp() < rhs.fPosition.Perp() )
      return true;
   else if ( lhs.fPosition.Perp() == rhs.fPosition.Perp() &&
             lhs.fPosition.Z() < rhs.fPosition.Z() )
      return true;
   else
      return false;
}
