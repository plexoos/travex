#include "travex/ProgramOptions.h"


int main(int argc, char **argv)
{
   tvx::ProgramOptions prgOpts(argc, argv);
   prgOpts.ProcessOptions();

   return EXIT_SUCCESS;
}
