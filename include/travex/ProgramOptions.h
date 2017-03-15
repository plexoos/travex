#ifndef tvx_ProgramOptions_h
#define tvx_ProgramOptions_h

#include <set>
#include <string>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>


namespace tvx {

// A shorthand for a long namespace
namespace po = boost::program_options;


/**
 * Processes and controls user options provided in the command line. An input
 * file is required. The path to an output file is built from the input file
 * name and a prefix path provided by the user.
 */
class ProgramOptions
{
public:

   ProgramOptions(int argc, char **argv, const std::string& postfix="_out");

   std::string  PathToInputFile() const { return fInFilePath; }
   unsigned int GetMaxEventsUser() const { return fMaxEventsUser; }
   double GetSparsity() const { return fSparsity; }
   bool  SaveGraphics() const { return fSaveGraphics; }
   std::string GetOutPrefix() const { return fOutPrefix; }

   /// Form a name for the output file from the input file's base name with an
   /// optional string to be appended to the end if provided as an argument
   std::string GetOutFileName(std::string postfix="") const;

   void ProcessOptions();
   void Print() const;

protected:

   /// Verifies user submitted values
   virtual void VerifyOptions();

   int                     fArgc;
   char**                  fArgv;

   /// User defined command line options defined with boost::program_options
   po::options_description  fOptions;

   /// Option values extracted from the command line argument
   po::variables_map  fOptionsValues;

   /// Full path to either a root file with event tree or a text file with
   /// a list of such root files
   std::string  fInFilePath;

   /// A prefix to specify the location of the output files
   std::string  fOutPrefix;

   /// A postfix provided by the user to append to the output file base name.
   /// Can include an output file extension, e.g. "_out.txt"
   std::string  fOutPostfix;

   /// The maximum number of input events to process
   unsigned int  fMaxEventsUser;

   /// An approximate fraction of events to read and process
   double  fSparsity;

   /// This flag controls whether to produce images for created histograms
   bool  fSaveGraphics;
};


/**
 * A helper function to print values of boost's any type.
 */
template<class T>
bool out_to_stream(std::ostream& os, const boost::any& any_value)
{
   try {
      os << boost::any_cast<T>(any_value);
      return true;
   } catch(boost::bad_any_cast& e) {
      return false;
   }
}

std::ostream& operator<<(std::ostream& os, const boost::any& any_value);

}

#endif
