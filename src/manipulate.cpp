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

std::string olc_manipulate::recover_single(std::string olc, double latitude, double longitude){

  if(!olc_check_short_single(olc)){
    if(olc_check_full_single(olc)){
      return olc;
    }
    throw std::range_error("codes provided to recover_olc must be valid short Open Location Codes. Offending code: " + olc);
  }

  double ref_longitude = clip_longitude(longitude);
  double ref_latitude = clip_lat(latitude);

  for(unsigned int i = 0; i < olc.size(); i++){
    olc[i] = toupper(olc[i]);
  }

  int padding_length = (separator_position - olc.find(separator));
  double resolution = pow(20.0, (2.0 - (padding_length / 2.0)));
  double area_to_edge = resolution / 2.0;

  std::vector < double > code_area = olc_decode_single(
    olc_encode_single(ref_latitude, ref_longitude, max_pair_length).substr(0, padding_length) + olc
  );

  double degrees_difference = (code_area[4] - ref_latitude);
  if(degrees_difference > area_to_edge){
    code_area[4] -= resolution;
  } else if(degrees_difference < -area_to_edge){
    code_area[4] += resolution;
  }

  degrees_difference = (code_area[5] - ref_longitude);
  if(degrees_difference > area_to_edge){
    code_area[5] -= resolution;
  } else if(degrees_difference < -area_to_edge){
    code_area[5] += resolution;
  }

  return(olc_encode_single(code_area[4], code_area[5], code_area[6]));
}

CharacterVector olc_manipulate::shorten_vector(CharacterVector olc, NumericVector latitude, NumericVector longitude){

  if(latitude.size() != longitude.size()){
    throw std::range_error("There must be as many longitude values as latitude values");
  }

  unsigned int input_size = olc.size();
  CharacterVector output(input_size);

  if(latitude.size() == 1){

    for(unsigned int i = 0; i < input_size; i++){
      if((i % 10000) == 0){
        Rcpp::checkUserInterrupt();
      }

      if(CharacterVector::is_na(olc[i]) || NumericVector::is_na(latitude[0]) || NumericVector::is_na(longitude[0])){
        output[i] = NA_STRING;
      } else {
        output[i] = shorten_single(Rcpp::as<std::string>(olc[i]), latitude[0], longitude[0]);
      }
    }

  } else if(latitude.size() == input_size){

    for(unsigned int i = 0; i < input_size; i++){
      if((i % 10000) == 0){
        Rcpp::checkUserInterrupt();
      }

      if(CharacterVector::is_na(olc[i]) || NumericVector::is_na(latitude[i]) || NumericVector::is_na(longitude[i])){
        output[i] = NA_STRING;
      } else {
        output[i] = shorten_single(Rcpp::as<std::string>(olc[i]), latitude[i], longitude[i]);
      }
    }

  } else {
    throw std::range_error("the latitude and longitude parameters must contain either one value, or one value for each OLC");
  }

  return output;
}

CharacterVector olc_manipulate::recover_vector(CharacterVector olc, NumericVector latitude,
                                                           NumericVector longitude){

  if(latitude.size() != longitude.size()){
    throw std::range_error("There must be as many longitude values as latitude values");
  }

  unsigned int input_size = olc.size();
  CharacterVector output(input_size);

  if(latitude.size() == 1){

    for(unsigned int i = 0; i < input_size; i++){
      if((i % 10000) == 0){
        Rcpp::checkUserInterrupt();
      }
      if(CharacterVector::is_na(olc[i]) || NumericVector::is_na(latitude[0]) || NumericVector::is_na(longitude[0])){
        output[i] = NA_STRING;
      } else {
        output[i] = recover_single(Rcpp::as<std::string>(olc[i]), latitude[0], longitude[0]);
      }

    }

  } else if(latitude.size() == input_size){

    for(unsigned int i = 0; i < input_size; i++){
      if((i % 10000) == 0){
        Rcpp::checkUserInterrupt();
      }
      if(CharacterVector::is_na(olc[i]) || NumericVector::is_na(latitude[i]) || NumericVector::is_na(longitude[i])){
        output[i] = NA_STRING;
      } else {
        output[i] = recover_single(Rcpp::as<std::string>(olc[i]), latitude[i], longitude[i]);
      }
    }

  } else {
    throw std::range_error("the latitude and longitude parameters must contain either one value, or one value for each OLC");
  }

  return output;
}

olc_manipulate::olc_manipulate(){
  min_trim_length = 6;
}
