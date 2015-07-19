#include <Rcpp.h>
#include "validate.h"
using namespace Rcpp;

#ifndef __OLC_CODE__
#define __OLC_CODE__

class olc_coders: public olc_validate {

private:

  int max_code_length = 10;

  int grid_rows = 5;

  int max_pair_length = 10;

  double clip_lat(double lat);

  double clip_longitude(double longitude);

  double lat_precision(int length);

  std::string olc_encode_single(double lat, double longitude, int output_length);

  std::vector < double > olc_decode_single(std::string olc);

  std::vector < std::string > output_names = {"latitude", "longitude"};

public:

  std::vector < std::string > olc_encode_vector(std::vector < double > latitude, std::vector < double > longitude,
                                                std::vector < int > code_length);

  DataFrame olc_decode_vector(std::vector < std::string > olc);

};

#endif
