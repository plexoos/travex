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
 * A light container to hold and manipulate user histograms. This class may be
 * used by itself or serve as a base class when additional functionality is
 * needed to fill user histograms. When saved in a ROOT file the histograms are
 * placed in a subdirectory named `name` in `motherDir`.
 */
class HistContainer : public TDirectoryFile
{
public:

   HistContainer(const std::string name, TDirectory* motherDir=nullptr, const std::string option="");

   /// This container assumes the ownership of the histogram and can modify it
   void Add(TH1* hist);

   /// Returns a reference to the internal histogram container for external
   /// handling
   const HistMap& GetHists() const;

   /// Returns a reference to the histogram with name `hist_name`, throws
   /// a `std::out_of_range` exception if no such histogram exists
   const TH1& operator[](const std::string& hist_name) const;

   /// Returns a raw pointer to the histogram with `hist_name` name or nullptr
   /// such histogram does not exist
   const TH1* FindHist(const std::string& hist_name) const;

   /// A user implementation of this method can be called when additional
   /// histograms need to be built from the already available ones. Usage cases
   /// include a ratio of two histograms or a fit to the histogram data points
   virtual void Finalize();

   /// Saves all histograms from the container as png images in the `prefix`
   /// directory
   void SaveAllAs(std::string prefix="./", std::string img_format="png");

protected:

   /// Unrestricted access to stored histograms for friends
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


inline void HistContainer::Finalize() {}


inline TH1* HistContainer::h(const std::string& hist_name) const
{
   auto iter = fHs.find(hist_name);
   return ( iter != fHs.end() ) ? iter->second.get() : nullptr;
}

}

#endif
