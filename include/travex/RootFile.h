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
 * This is a simple helper class to wrap ROOT's TFile with many options
 * controlled by user settings provided in command line and aggregated by
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

   HistContainers  fDirs;       ///< A string-to-HistContainer map for convenient access to enclosed directories
   ProgramOptions& fPrgOptions; ///< Command line arguments and options requested by the user
};

}

#endif
