#include "manipulate.h"

std::string olc_manipulate::shorten_single(std::string olc, double latitude, double longitude){
  if(!olc_check_full_single(olc)){
    throw std::range_error("The Open Location Codes provided must be complete. Incomplete code: " + olc);
  }

  if(olc.find(padding) != std::string::npos){
    throw std::range_error("The Open Location Codes provided cannot have padding characters. Padded code: " + olc);
  }

  for(unsigned int i = 0; i < olc.size(); i++){
    olc[i] = toupper(olc[i]);
  }

  std::vector < double > decoded_code = olc_decode_single(olc);
  if(decoded_code[6] < min_trim_length){
    throw std::range_error("Open Location Codes must be >6 in length to be shortened. Offending code: " + olc);
  }

  return olc;
}
