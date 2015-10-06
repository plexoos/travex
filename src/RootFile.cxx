#include <boost/filesystem.hpp>

#include "travex/RootFile.h"

#include "TSystem.h"
#include "TROOT.h"

#include "travex/HistContainer.h"
#include "travex/ProgramOptions.h"


using namespace tvx;


RootFile::RootFile(ProgramOptions& prgOpts, Option_t *option, const char *ftitle, Int_t compress) :
   TFile(prgOpts.GetOutFileName().c_str(), option, ftitle, compress),
   fDirs(),
   fPrgOptions(prgOpts)
{
   Info("RootFile", "Created ROOT file: %s", GetName());

   std::string macroPath = std::string(gROOT->GetMacroPath()) + ":" + stitools::gStiToolsMacrosPath;
   gROOT->SetMacroPath(macroPath.c_str());
}


void RootFile::FillDerivedHists()
{
   for (const std::pair<std::string, HistContainer*>& iDir : fDirs)
   {
      std::string  dirName = iDir.first;
      HistContainer *container = iDir.second;

      if (!container) {
         Error("FillDerivedHists", "No container/directory found for key %s. Skipping...", dirName.c_str());
         continue;
      }

      container->FillDerivedHists();
   }
}


void RootFile::Close(Option_t *option)
{
   if (fPrgOptions.SaveGraphics()) {
      SaveAllAs(fPrgOptions.GetOutPrefix());
   }

   TFile::Close(option);
}


void RootFile::SaveAllAs(std::string prefix)
{
   gROOT->Macro("style_hists.C");

   namespace fs = boost::filesystem;

   if (fs::create_directories(prefix))
      Info("SaveAllAs", "Created dir: %s", prefix.c_str());
   else
      Warning("SaveAllAs", "Perhaps dir already exists: %s", prefix.c_str());

   for (const std::pair<std::string, HistContainer*>& iDir : fDirs)
   {
      std::string  dirName = iDir.first;
      HistContainer *container = iDir.second;

      if (!container) {
         Error("SaveAllAs", "No container/directory found for key %s. Skipping...", dirName.c_str());
         continue;
      }

      std::string path = prefix + "/" + dirName;

      if (gSystem->mkdir(path.c_str()) < 0)
         Warning("SaveAllAs", "Perhaps dir already exists: %s", path.c_str());
      else
         Info("SaveAllAs", "Created dir: %s", path.c_str());

      container->SaveAllAs(path);
   }
}