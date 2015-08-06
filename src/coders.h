#include <algorithm>
#include "validate.h"
using namespace Rcpp;

#ifndef __OLC_CODE__
#define __OLC_CODE__

class olc_coders: public olc_validate {

protected:

  int grid_rows;

  int grid_cols;

  double grid_degrees;

  int max_pair_length;

  std::vector < double > resolution_levels;

  double clip_lat(double lat);

  double clip_longitude(double longitude);

  double lat_precision(int length);

  std::vector < double > olc_decode_single(std::string olc);

  std::string olc_encode_single(double lat, double longitude, int output_length);

private:


  std::vector < double > olc_decode_pair(std::string code, int offset);

  std::vector < double > olc_decode_grid(std::string code);


public:

  std::vector < std::string > olc_encode_vector(std::vector < double > latitude, std::vector < double > longitude,
                                                std::vector < int > code_length);

  DataFrame olc_decode_vector(std::vector < std::string > olcs);

  olc_coders();

};

#endif
