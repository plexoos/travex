#ifndef RootFile_h
#define RootFile_h

#include <map>
#include <string>

#include "TFile.h"

#include "travex/ProgramOptions.h"
#include "travex/HistContainer.h"


namespace tvx {

typedef std::map<std::string, HistContainer*>   HistContainers;


/**
 * A basic extention of the ROOT's TFile class to manage a set of user defined
 * histogram containers (or any other ROOT objects if desired) by automatically
 * arranging them in subdirectories. This simple helper class can use options
 * provided by the user in the command line and aggregated by
 * tvx::ProgramOptions.
 */
class RootFile : public TFile
{
public:

   RootFile(ProgramOptions& prgOpts, Option_t* option="", const char* ftitle="", Int_t compress=1);

   void FillDerivedHists();
   const ProgramOptions& GetPrgOptions() { return fPrgOptions; }

   virtual void Close(Option_t *option="");
   void SaveAllAs(std::string prefix="./");

protected:

   /// Adds HistContainer to the file
   /// Current implementation is limited to Allocate-Add-Allocate-Add workflow:
   // \code
   // Add(new FooContainer("foo"))
   // Add(new BarContainer("bar"))
   // \endcode
   // Allocate-Allocate-Add-Add will produce a wrong directory tree.
   void Add(HistContainer *hc);

   /// Unrestricted access to a stored histogram container by its name for
   /// friends and those who know what they are doing
   HistContainer* hc(const std::string& hc_name) const;

   /// A string-to-HistContainer map for convenient access to enclosed directories
   HistContainers  fDirs;

   /// Command line arguments and options requested by the user
   ProgramOptions& fPrgOptions;
};



inline HistContainer* RootFile::hc(const std::string& hc_name) const
{
   auto iter = fDirs.find(hc_name);
   return ( iter != fDirs.end() ) ? iter->second : nullptr;
}

}

#endif
