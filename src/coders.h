#include <Rcpp.h>
#include "validate.h"
using namespace Rcpp;

#ifndef __OLC_CODE__
#define __OLC_CODE__

class olc_coders {
friend class olc_validate;
private:

  int max_code_length = 10;

  std::string olc_encode_single(double lat, double long, int output_length);

  std::vector < double > olc_decode_single(std::string olc);

  std::vector < std::string > output_names = {"latitude", "longitude"};

public:

  std::vector < std::string > olc_encode_vector(std::vector < double > latitude, std::vector < double > longitude,
                                                std::vector < int > code_length);

  DataFrame olc_decode_vector(std::vector < std::string > olc);

};

#endif
