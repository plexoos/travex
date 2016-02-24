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

   const HistMap& GetHists() const { return mHs; }
   const TH1*     FindHist(const std::string& hist_name) const;
   virtual void FillDerivedHists() = 0;

	/// Saves all histograms from the container as png images in the `prefix` directory.
   void SaveAllAs(std::string prefix="./");

protected:

   virtual void BookHists() = 0;
   TH1* FindHist(const std::string& hist_name);

	/// A container of unique pointers to TH1 objects indexed by names
   HistMap mHs;
};

}

#endif
