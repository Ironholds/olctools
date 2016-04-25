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

  unsigned int max_pair_length;

  std::vector < double > resolution_levels;

  double clip_lat(double lat);

  double clip_longitude(double longitude);

  double lat_precision(unsigned int length);

  std::vector < double > olc_decode_single(std::string olc);

  std::string olc_encode_single(double lat, double longitude, unsigned int output_length);

private:


  std::vector < double > olc_decode_pair(std::string code, int offset);

  std::vector < double > olc_decode_grid(std::string code);


public:

  CharacterVector olc_encode_vector(NumericVector latitude, NumericVector longitude,
                                    IntegerVector code_length);

  DataFrame olc_decode_vector(CharacterVector olcs);

  olc_coders();

};

#endif
