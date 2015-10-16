#include <iostream>
#include <string>

#include "travex/Event.h"
#include "travex/Track.h"
#include "travex/Hit.h"


tvx::Event::Event() : TObject(),
   fTracks(),
   fHits()
{
}


void tvx::Event::Clear(Option_t *opt)
{
   fTracks.clear();
   fHits.clear();
}


void tvx::Event::Print(Option_t *opt) const
{
   std::cout << "Event::Print(" << std::string(opt) << ")" << "\n"
             << "Num. of tracks: " << fTracks.size() << "\n"
             << "Num. of hits:   " << fHits.size()
             << std::endl;

   if (std::string(opt).find("all") == std::string::npos)
      return;

   for (const auto& track : fTracks) {
      track.Print();
   }
}
