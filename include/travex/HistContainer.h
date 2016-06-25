#ifndef HistContainer_h
#define HistContainer_h

#include <map>
#include <memory>
#include <string>

#include "TH1.h"
#include "TDirectoryFile.h"


namespace tvx {

typedef std::map<std::string, std::unique_ptr<TH1> >  HistMap;


/**
 * A very light container to hold and manipulate user histograms.
 */
class HistContainer : public TDirectoryFile
{
public:

   HistContainer(const std::string name, TDirectory* motherDir=nullptr, const std::string option="");

   void Add(TH1* hist);
   const HistMap& GetHists() const;

   /// Returns a reference to the histogram with name `hist_name`, throws
   /// a `std::out_of_range` exception if no such histogram exists.
   const TH1& operator[](const std::string& hist_name) const;
   const TH1* FindHist(const std::string& hist_name) const;
   virtual void FillDerivedHists();

   /// Saves all histograms from the container as png images in the `prefix` directory.
   void SaveAllAs(std::string prefix="./", std::string img_format="png");

protected:

   TH1* h(const std::string& hist_name) const;

private:

   /// A container of unique pointers to TH1 objects indexed by names
   HistMap fHs;
};


inline const HistMap& HistContainer::GetHists() const
{
   return fHs;
}


inline const TH1& HistContainer::operator[](const std::string& hist_name) const
{
   return *(fHs.at(hist_name));
}


inline const TH1* HistContainer::FindHist(const std::string& hist_name) const
{
   return h(hist_name);
}


inline void HistContainer::FillDerivedHists() {}


inline TH1* HistContainer::h(const std::string& hist_name) const
{
   auto iter = fHs.find(hist_name);
   return ( iter != fHs.end() ) ? iter->second.get() : nullptr;
}

}

#endif
