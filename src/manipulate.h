#include "coders.h"
#include <cmath>

using namespace Rcpp;

#ifndef __OLC_MANIP__
#define __OLC_MANIP__

class olc_manipulate: public olc_coders {

private:

  int min_trim_length;

  std::string shorten_single(std::string olc, double latitude, double longitude);

  std::string recover_single(std::string olc, double latitude, double longitude);

public:

  std::vector < std::string > shorten_vector(std::vector < std::string > olc, std::vector < double > latitude,
                                             std::vector < double > longitude);

  std::vector < std::string > recover_vector(std::vector < std::string > olc, std::vector < double > latitude,
                                             std::vector < double > longitude);

  olc_manipulate();
};
#endif
