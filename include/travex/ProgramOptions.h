#ifndef tvx_ProgramOptions_h
#define tvx_ProgramOptions_h

#include <set>
#include <string>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>


namespace tvx {

// A shorthand for a long namespace
namespace po = boost::program_options;


/**
 * Processes and controls user options provided in the command line.
 */
class ProgramOptions
{
public:

   ProgramOptions();
   ProgramOptions(int argc, char **argv);

   std::string  PathToInputFile() const { return fInFilePath; }
   unsigned int GetMaxEventsUser() const { return fMaxEventsUser; }
   float GetSparsity() const { return fSparsity; }
   bool  SaveGraphics() const { return fSaveGraphics; }
   std::string GetOutPrefix() const { return fOutPrefix; }
   std::string GetOutFileName(std::string suffix="hist") const;

   void ProcessOptions();
   void Print() const;

protected:

   void VerifyOptions();

   int                     fArgc;
   char**                  fArgv;
   po::options_description fOptions;
   po::variables_map       fOptionsValues;

   /// Full path to either a root file with event tree or a text file with
   /// a list of such root files
   std::string  fInFilePath;

   /// A prefix to specify the location of the output files
   std::string  fOutPrefix;

   /// The maximum number of input events to process
   unsigned int  fMaxEventsUser;

   /// An approximate fraction of events to read and process
   float  fSparsity;

   /// This flag controls whether to produce images for created histograms
   bool  fSaveGraphics;

private:

   void InitOptions();
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
   } catch(boost:: bad_any_cast& e) {
      return false;
   }
}

std::ostream& operator<<(std::ostream& os, const boost::any& any_value);

}

#endif
