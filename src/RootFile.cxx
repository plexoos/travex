#include <boost/filesystem.hpp>

#include "travex/RootFile.h"

#include "TSystem.h"
#include "TROOT.h"

#include "travex/config.h"
#include "travex/utils.h"
#include "travex/HistContainer.h"
#include "travex/ProgramOptions.h"


using namespace tvx;


RootFile::RootFile(ProgramOptions& prgOpts, Option_t *option, const char *ftitle, Int_t compress) :
   TFile(prgOpts.GetOutFileName().c_str(), option, ftitle, compress),
   fDirs(),
   fPrgOptions(prgOpts)
{
   Info("RootFile", "Created ROOT file: %s", GetName());

   std::string macroPath = std::string(gROOT->GetMacroPath()) + ":" + gTravexMacrosPath;
   gROOT->SetMacroPath(macroPath.c_str());
   gROOT->Macro("style_hists.C");
}


/**
 * Adds the user provided histogram container to the internal collection. Basic
 * checks are performed to validate the pointer.
 */
void RootFile::Add(HistContainer* hist_container)
{
   if (!hist_container || std::string(hist_container->GetName()).empty() ) {
      TVX_WARNING("Cannot add invalid histogram container");
      return;
   }

   std::string hc_name(hist_container->GetName());

   if ( hc(hc_name) )
      TVX_WARNING("Replacing existing histogram %s", hc_name.c_str());

   fDirs[hc_name].reset(hist_container);

   cd();
}


/**
 * For each histogram container calls the method of the same name in order to
 * produce new histograms from already filled histograms.
 */
void RootFile::Finalize()
{
   for (const auto& subDir : fDirs)
   {
      std::string  dirName = subDir.first;
      HistContainer *container = subDir.second.get();

      if (!container) {
         Error("Finalize", "No container/directory found for key %s. Skipping...", dirName.c_str());
         continue;
      }

      container->cd();
      container->Finalize();
   }
}


void RootFile::Close(Option_t *option)
{
   if (fPrgOptions.SaveGraphics()) {
      SaveAllAs(fPrgOptions.GetOutPrefix());
   }

   TFile::Close(option);

   // Since ROOT file owns the subdirectories they will be destroyed at closing.
   // Release the unique_ptr-s to HistContainer-s to avoid segfault in following
   // destructor call
   for (auto& subDir : fDirs)
      subDir.second.release();

   TVX_INFO("Closed ROOT file: %s", GetName());
}


void RootFile::SaveAllAs(std::string prefix)
{
   gROOT->Macro("style_hists.C");

   namespace fs = boost::filesystem;

   if (fs::create_directories(prefix))
      Info("SaveAllAs", "Created directory: %s", prefix.c_str());
   else
      Warning("SaveAllAs", "Perhaps directory already exists: %s", prefix.c_str());

   for (const auto& subDir : fDirs)
   {
      std::string  dirName = subDir.first;
      HistContainer *container = subDir.second.get();

      if (!container) {
         Error("SaveAllAs", "No container/directory found for key %s. Skipping...", dirName.c_str());
         continue;
      }

      std::string path = prefix + "/" + dirName;

      if (gSystem->mkdir(path.c_str()) < 0)
         Warning("SaveAllAs", "Perhaps directory already exists: %s", path.c_str());
      else
         Info("SaveAllAs", "Created directory: %s", path.c_str());

      container->SaveAllAs(path);
   }
}
