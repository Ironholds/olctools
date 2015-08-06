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

  longitude = clip_longitude(longitude);
  latitude = clip_lat(latitude);
  double range = std::max(std::abs((double) decoded_code[5] - longitude), std::abs((double) decoded_code[4] - latitude));

  for(unsigned int i = resolution_levels.size() - 2; i >= 1; i--){
    if(range < (resolution_levels[i] * 0.3)){
      return olc.substr((i+1)*2);
    }
  }
  return olc;
}

std::vector < std::string > olc_manipulate::shorten_vector(std::vector < std::string > olc, std::vector < double > latitude,
                                                          std::vector < double > longitude){

  if(latitude.size() != longitude.size()){
    throw std::range_error("There must be as many longitude values as latitude values");
  }

  unsigned int input_size = olc.size();
  std::vector < std::string > output(input_size);

  if(latitude.size() == 1){

    for(unsigned int i = 0; i < input_size; i++){
      if((i % 10000) == 0){
        Rcpp::checkUserInterrupt();
      }
      output[i] = shorten_single(olc[i], latitude[0], longitude[0]);
    }

  } else if(latitude.size() == input_size){

    for(unsigned int i = 0; i < input_size; i++){
      if((i % 10000) == 0){
        Rcpp::checkUserInterrupt();
      }
      output[i] = shorten_single(olc[i], latitude[i], longitude[i]);
    }

  } else {
    throw std::range_error("the latitude and longitude parameters must contain either one value, or one value for each OLC");
  }

  return output;
}

olc_manipulate::olc_manipulate(){
  min_trim_length = 6;
}
