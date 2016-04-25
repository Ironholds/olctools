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

  CharacterVector shorten_vector(CharacterVector olc, NumericVector latitude, NumericVector longitude);

  CharacterVector recover_vector(CharacterVector olc, NumericVector latitude, NumericVector longitude);

  olc_manipulate();
};
#endif
