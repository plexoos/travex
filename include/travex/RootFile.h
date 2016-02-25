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

   virtual void Close(Option_t *option="");
   void SaveAllAs(std::string prefix="./");

protected:

   /// A string-to-HistContainer map for convenient access to enclosed directories
   HistContainers  fDirs;

   /// Command line arguments and options requested by the user
   ProgramOptions& fPrgOptions;
};

}

#endif
