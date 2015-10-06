#include <iostream>
#include <fstream>
#include <boost/regex.hpp>

#include "travex/utils.h"
#include "travex/ProgramOptions.h"


using namespace tvx;


ProgramOptions::ProgramOptions() : ProgramOptions(0, nullptr)
{
}


ProgramOptions::ProgramOptions(int argc, char **argv) :
   fArgc(argc), fArgv(argv),
   fOptions("Program options", 120),
   fOptionsValues(),
   fInFilePath(),
   fOutPrefix("./"),
   fMaxEventsUser(0),
   fSparsity(1),
   fSaveGraphics(false)
{
   InitOptions();
}


/**
 * Supported program options should be declared in this private method.
 */
void ProgramOptions::InitOptions()
{
   fOptions.add_options()
      ("help,h",        "Print this help message")
      ("input-file,f",  po::value<std::string>(&fInFilePath), "Full path to a ROOT file, e.g. containing a TTree " \
                        "OR a text file with a list of such ROOT files")
      ("prefix,o",      po::value<std::string>(&fOutPrefix), "Absolute or relative path to prefix output files")
      ("max-events,n",  po::value<unsigned int>(&fMaxEventsUser)->default_value(0), "Maximum number of events to process")
      ("sparsity,s",    po::value<float>(&fSparsity)->default_value(1), "Approximate fraction of events to read and process")
      ("save-graph,g",  "Use this option to save histograms and such as images")
   ;
}


/**
 * Takes the standard command line arguments and parses them with the boost
 * program_options utility. Additional checks are implemented to verify the
 * validity of the supplied arguments.
 */
void ProgramOptions::ProcessOptions()
{
   po::store(po::parse_command_line(fArgc, fArgv, fOptions), fOptionsValues);
   po::notify(fOptionsValues);

   VerifyOptions();
}


void ProgramOptions::VerifyOptions()
{
   if (fOptionsValues.count("help"))
   {
      std::cout << fOptions << std::endl;
      exit(EXIT_SUCCESS);
   }

   //Info("User provided options: %d %s", 5, "ggg");


   if (fOptionsValues.count("input-file"))
   {
      std::string inputFileName = boost::any_cast<std::string>(fOptionsValues["input-file"].value());
      std::cout << "Input file: " << inputFileName << std::endl;

      std::ifstream tmpFileCheck(inputFileName.c_str());
      if (!tmpFileCheck.good()) {
         //Fatal("VerifyOptions", "File \"%s\" does not exist", inputFileName.c_str());
      }
   } else {
      //Fatal("VerifyOptions", "Input file not set");
   }


   if (fOptionsValues.count("max-events"))
   {
      std::cout << "max-events: " << fMaxEventsUser << std::endl;
   }

   if (fOptionsValues.count("sparsity"))
   {
      if (fSparsity > 1 || fSparsity <= 0) {
         //Warning("VerifyOptions", "Sparsity specified value outside allowed limits. Set to 1");
         fSparsity = 1;
      }
      std::cout << "sparsity: " << fSparsity << std::endl;
   }

   if (fOptionsValues.count("save-graph") )
      fSaveGraphics = true;
}


/**
 * Form the name of the output file from the input file name by appending
 * a suffix to it. The following rules applied depending on the input file
 * extension:
 *
 * input_file_name      -> input_file_name.<suffix>.root
 * input_file_name.blah -> input_file_name.blah.<suffix>.root
 * input_file_name.root -> input_file_name.<suffix>.root
 */
std::string ProgramOptions::GetOutFileName(std::string suffix) const
{
   boost::regex extension_regex("^(.*)\\.root$");

   if ( boost::regex_match(fInFilePath, extension_regex) ) {
      return boost::regex_replace(fInFilePath, extension_regex, "\\1." + suffix + ".root");
   } else {
      return fInFilePath + "." + suffix + ".root";
   }
}
