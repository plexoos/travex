#include <exception>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/program_options/parsers.hpp>

#include "travex/utils.h"
#include "travex/ProgramOptions.h"


using namespace tvx;

namespace fs = boost::filesystem;


/**
 * Creates a number of options which can be used in a typical application
 * reading a file (containing e.g. a ROOT TTree) and producing an output (e.g.
 * a ROOT file with histograms and their corresponding images).
 */
ProgramOptions::ProgramOptions(int argc, char **argv, const std::string& postfix) :
   fArgc(argc), fArgv(argv),
   fOptions("Available program options", 120),
   fOptionsValues(),
   fInFilePath(),
   fOutPrefix("./"),
   fOutPostfix(postfix),
   fMaxEventsUser(0),
   fSparsity(1),
   fSaveGraphics(false)
{
   fOptions.add_options()
      ("help,h",        "Print this help message")

      ("input-file,i",  po::value<std::string>(&fInFilePath),
                        "Full path to a ROOT file containing a TTree OR a text file with a list of such ROOT files")

      ("out-prefix,o",  po::value<std::string>(&fOutPrefix)->default_value("./")->implicit_value(""),
                        "Absolute or relative path to prefix output files. Default is the current directory. " \
                        "If no argument provided deducted from input file")

      ("out-ending,e",  po::value<std::string>(&fOutPostfix)->default_value(postfix),
                        "Output file ending")

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
      _exit(EXIT_SUCCESS);
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

   std::cout << "\t[output file]:\t" << GetOutFileName() << std::endl;
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
      fs::path in_file_path(fInFilePath);

      if ( !fs::exists(in_file_path) )
         TVX_FATAL("File \"%s\" does not exist", fInFilePath.c_str());

   } else
      throw po::required_option("input-file");

   // Validate out-prefix option
   if (fOptionsValues.count("out-prefix"))
   {
      if (fOutPrefix.empty()) {
         fs::path out_file_path(fInFilePath);
         fOutPrefix = out_file_path.parent_path().string();
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
 * Form a name for the output file from the input file's base name with an
 * optional string to be appended to the end if provided as an argument. For
 * example,
 *
 * some/path/to/input_file_name -> <prefix>/input_file_name_<postfix>
 *
 * If <postfix> = .ext..
 *
 * /a/path/to/input.file.name.blah -> <prefix>/input.ext
 *
 */
std::string ProgramOptions::GetOutFileName(std::string postfix) const
{
   // Allow the user to overwrite internal values
   if ( postfix.empty() ) postfix = fOutPostfix;

   fs::path out_file_path(fOutPrefix);
   fs::path in_file_path(fInFilePath);

   fs::path in_filename  = in_file_path.filename();
   fs::path in_extension = in_file_path.extension();

   // Pop as many "extensions" in the original file name as there are dots at
   // the end of the user extension. Do it at least once
   do {
      in_filename.replace_extension("");

      if (postfix.back() == '.') postfix.pop_back();

   } while(postfix.back() == '.');

   // If there are NO dots in the new extension
   if ( postfix.find(".") == std::string::npos)
   {
      // Reuse the extension of the input file
      postfix += in_extension.string();
   }

   out_file_path /= in_filename;
   // Append to the base file name
   out_file_path += (postfix[0] == '_' || postfix[0] == '.') ?
                     postfix : "_" + postfix;

   return out_file_path.string();
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
