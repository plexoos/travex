#include <iostream>
#include <fstream>
#include <boost/regex.hpp>

#include "travex/utils.h"
#include "travex/ProgramOptions.h"


using namespace tvx;



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
   fOptions.add_options()
      ("help,h",        "Print this help message")
      ("input-file,f",  po::value<std::string>(&fInFilePath), "Full path to a ROOT file, e.g. containing a TTree " \
                        "OR a text file with a list of such ROOT files")
      ("prefix,o",      po::value<std::string>(&fOutPrefix)->default_value("./"), "Absolute or relative path to prefix output files")
      ("max-events,n",  po::value<unsigned int>(&fMaxEventsUser)->default_value(0), "Maximum number of events to process")
      ("sparsity,s",    po::value<float>(&fSparsity)->default_value(1), "Approximate fraction of events to read and process")
      ("save-graph,g",  po::value<bool>(&fSaveGraphics)->default_value(false)->implicit_value(true), "Use this option to save histograms and such as images")
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


void ProgramOptions::Print() const
{
   std::cout << "Program options set to following values:\n";

   for (const std::pair< std::string, po::variable_value >& option : fOptionsValues)
   {
      std::cout << "\t" << option.first << ":\t" << option.second.value() << "\n";
   }
}


void ProgramOptions::VerifyOptions()
{
   if (fOptionsValues.count("help"))
   {
      std::cout << fOptions << std::endl;
      exit(EXIT_SUCCESS);
   }


   if (fOptionsValues.count("input-file"))
   {
      std::string inputFileName = boost::any_cast<std::string>(fOptionsValues["input-file"].value());

      std::ifstream tmpFileCheck(inputFileName.c_str());
      if (!tmpFileCheck.good()) {
         TVX_FATAL("File \"%s\" does not exist", inputFileName.c_str());
      }
   } else {
      TVX_ERROR("Input file not set");
      std::cout << fOptions << std::endl;
      exit(EXIT_FAILURE);
   }

   if (fOptionsValues.count("sparsity"))
   {
      if (fSparsity > 1 || fSparsity <= 0) {
         TVX_WARNING("VerifyOptions", "Sparsity specified value outside allowed limits. Set to 1");
         fSparsity = 1;
      }
   }
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


std::ostream& tvx::operator<<(std::ostream& os, const boost::any& any_value)
{
   // List all types you want to try
   if(!out_to_stream<int>(os, any_value))
   if(!out_to_stream<unsigned int>(os, any_value))
   if(!out_to_stream<float>(os, any_value))
   if(!out_to_stream<bool>(os, any_value))
   if(!out_to_stream<std::string>(os, any_value))
      os<<"{unknown}"; // all cast are failed, an unknown type of any

   return os;
}
