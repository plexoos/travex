#ifndef tvx_GenericHit_h
#define tvx_GenericHit_h


namespace tvx {


/**
 * An abstract base class interface with a basic functionality common to all
 * reconstructed hits registered by a tracking detector.
 */
template<class _Coordinates>
class GenericHit
{
public:

   typedef _Coordinates Coordinates_t;

   enum class Status {Undefined, Accepted, Rejected, Candidate};

   virtual ~GenericHit() {}

   virtual const Coordinates_t& GetPosition() const = 0;

   friend bool operator< (const GenericHit& lhs, const GenericHit& rhs)
   {
      return lhs.GetPosition() < rhs.GetPosition();
   }
};


}

#endif
