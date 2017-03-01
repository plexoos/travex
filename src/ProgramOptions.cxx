#include <exception>
#include <iostream>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/program_options/parsers.hpp>

#include "travex/utils.h"
#include "travex/ProgramOptions.h"


using namespace tvx;


/**
 * Creates a number of options which can be used in a typical application
 * reading a file (containing e.g. a ROOT TTree) and producing an output (e.g.
 * a ROOT file with histograms and their corresponding images).
 */
ProgramOptions::ProgramOptions(int argc, char **argv) :
   fArgc(argc), fArgv(argv),
   fOptions("Available program options", 120),
   fOptionsValues(),
   fInFilePath(),
   fOutPrefix("./"),
   fMaxEventsUser(0),
   fSparsity(1),
   fSaveGraphics(false)
{
   fOptions.add_options()
      ("help,h",        "Print this help message")

      ("input-file,f",  po::value<std::string>(&fInFilePath),
                        "Full path to a ROOT file containing a TTree OR a text file with a list of such ROOT files")

      ("out-prefix,o",  po::value<std::string>(&fOutPrefix)->default_value("./")->implicit_value(""),
                        "Absolute or relative path to prefix output files. Default is the current directory. " \
                        "If no argument provided deducted from input file")

      ("max-events,n",  po::value<unsigned int>(&fMaxEventsUser)->default_value(0),
                        "Maximum number of events to process")

      ("sparsity,s",    po::value<double>(&fSparsity)->default_value(1),
                        "Approximate fraction of events to read and process")

      ("save-graph,g",  po::value<bool>(&fSaveGraphics)->default_value(false)->implicit_value(true),
                        "Use this option to save histograms and such as images")
   ;
}


/**
 * Takes the standard command line arguments and parses them with the boost
 * program_options utility. Additional checks are implemented to verify the
 * validity of the supplied arguments.
 */
void ProgramOptions::ProcessOptions()
{
   try {

      po::store(po::parse_command_line(fArgc, fArgv, fOptions), fOptionsValues);
      po::notify(fOptionsValues);

      VerifyOptions();

   } catch(const po::error& ex)
   {
      TVX_ERROR(ex.what());
      std::cout << "\n" << fOptions << std::endl;
      _exit(EXIT_FAILURE);

   } catch(...)
   {
      std::cout << "\n" << fOptions << std::endl;
      _exit(EXIT_FAILURE);
   }
}


/** Prints the options and their values. */
void ProgramOptions::Print() const
{
   std::cout << "\nProgram options set to following values:\n";

   for (const std::pair< std::string, po::variable_value >& option : fOptionsValues)
   {
      std::cout << "\t" << option.first << ":\t" << option.second.value() << "\n";
   }
}


/**
 * Performs basic test of values provided by the user in the command line to
 * maker sure that they are valid.
 */
void ProgramOptions::VerifyOptions()
{
   if (fOptionsValues.count("help"))
      throw std::logic_error("Just print help");

   // Validate input-file option
   if (fOptionsValues.count("input-file"))
   {
      std::ifstream tmpFileCheck(fInFilePath.c_str());

      if (!tmpFileCheck.good()) {
         TVX_FATAL("File \"%s\" does not exist", fInFilePath.c_str());
      }

   } else
      throw po::required_option("input-file");

   // Validate out-prefix option
   if (fOptionsValues.count("out-prefix"))
   {
      if (fOutPrefix.empty()) {
         boost::filesystem::path outputPathFile(fInFilePath);
         fOutPrefix = outputPathFile.parent_path().string();
         fOptionsValues.at("out-prefix").value() = boost::any( fOutPrefix );
      }
   }

   if (fOptionsValues.count("sparsity"))
   {
      if (fSparsity > 1 || fSparsity <= 0) {
         TVX_WARNING("Sparsity specified value outside allowed limits. Set to 1");
         fSparsity = 1;
         fOptionsValues.at("sparsity").value() = boost::any( fSparsity );
      }
   }
}


/**
 * Create a name for the output file from the input file's base name, a suffix,
 * and a new extension provided as arguments. For example,
 *
 * some/path/to/input_file_name    -> input_file_name_<suffix>.<extension>
 * /a/path/to/input_file_name.blah -> input_file_name_blah_<suffix>.<extension>
 *
 */
std::string ProgramOptions::GetOutFileName(std::string suffix, std::string extension) const
{
   boost::filesystem::path outputPathFile(fInFilePath);

   // Remove the extension if present
   outputPathFile.replace_extension("");

   // Append to the base file name
   outputPathFile += suffix.empty() ? "" : "_" + suffix;

   // Append new extension
   outputPathFile.replace_extension(extension);

   return outputPathFile.string();
}


std::ostream& tvx::operator<<(std::ostream& os, const boost::any& any_value)
{
   // List all types you want to try
   if(!out_to_stream<int>(os, any_value))
   if(!out_to_stream<unsigned int>(os, any_value))
   if(!out_to_stream<float>(os, any_value))
   if(!out_to_stream<double>(os, any_value))
   if(!out_to_stream<bool>(os, any_value))
   if(!out_to_stream<std::string>(os, any_value))
      os << "{non-std type}"; // all cast are failed, an unknown type of any

   return os;
}
