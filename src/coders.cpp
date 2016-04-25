#include "coders.h"

double olc_coders::clip_lat(double lat){

  if(lat < -90){
    return -90;
  }

  if(lat > 90){
    return 90;
  }

  return lat;
}

double olc_coders::clip_longitude(double longitude){

  while(longitude < -180){
    longitude = longitude + 360;
  }

  while(longitude >= 180){
    longitude = longitude - 360;
  }

  return longitude;
}

double olc_coders::lat_precision(unsigned int length){
  if(length < max_pair_length){
    return pow(20.0, floor(-(length/2.0) + 2.0));
  }
  return pow(20.0, -3.0)/pow( (double) grid_rows, (double) (length - max_pair_length));
}

std::string olc_coders::olc_encode_single(double lat, double longitude, unsigned int output_length){

  if(output_length < 2 || (output_length < separator_position && output_length % 2 == 1)){
    throw std::range_error("The length value you have provided is not valid; see the documentation");
  }

  std::string output;
  lat = clip_lat(lat);
  longitude = clip_longitude(longitude);

  if(lat == 90){
    lat = lat_precision(output_length);
  }

  unsigned int to_encode_length = fmin(output_length, max_pair_length);
  double adjusted_lat = lat + max_latitude;
  double adjusted_long = longitude + max_longitude;
  int digit_value = 0;
  unsigned int digit_count = 0;
  double place_value;

  while(digit_count < to_encode_length){

    //Lat first
    place_value = resolution_levels[floor(digit_count/2.0)];
    digit_value = floor(adjusted_lat/place_value);
    adjusted_lat -= digit_value * place_value;
    output += character_set[digit_value];
    digit_count++;

    //Long
    digit_value = floor(adjusted_long/place_value);
    adjusted_long -= digit_value * place_value;
    output += character_set[digit_value];
    digit_count++;

    if(digit_count == separator_position && digit_count < to_encode_length) {
      output += "+";
    }
  }

  if((unsigned int) output.size() < separator_position){
    while((unsigned int) output.size() < separator_position){
      output += padding;
    }
  }

  if((unsigned int) output.size() == separator_position){
    output += separator;
  }

  if(output_length > max_pair_length){

    int additional_length = output_length - max_pair_length;
    double lat_values = grid_degrees;
    double long_values = grid_degrees;
    double adjusted_latitude = fmod((lat + max_latitude), lat_values);
    double adjusted_longitude = fmod((longitude + max_longitude), long_values);

    for(signed int i = 0; i < additional_length; i++){
      int row = floor(adjusted_latitude/(lat_values/grid_rows));
      int col = floor(adjusted_longitude/(long_values/grid_cols));
      lat_values = (lat_values/grid_rows);
      long_values = (long_values/grid_cols);

      adjusted_latitude -= row * lat_values;
      adjusted_longitude -= col * long_values;
      output += character_set[row * grid_cols + col];
    }

  }
  return output;
}

std::vector < double > olc_coders::olc_decode_pair(std::string code, int offset){

  unsigned int inval = 0;
  unsigned int input_length = code.size();
  double output_value = 0;
  std::vector < double > output(2);

  while((inval * 2 + offset) < input_length){
    output_value += (character_set.find(code[inval * 2 + offset]) * resolution_levels[inval]);
    inval++;
  }

  output[0] = output_value;
  output[1] = (output_value + resolution_levels[(inval - 1)]);
  return output;
}

std::vector < double > olc_coders::olc_decode_grid(std::string code){
  double latitude_low = 0.0;
  double longitude_low = 0.0;
  double lat_place_value = grid_degrees;
  double long_place_value = grid_degrees;
  int row = 0;
  int col = 0;
  int code_index = 0.0;
  std::vector < double > output(4);

  for(unsigned int i = 0; i < code.size(); i++){
    code_index = character_set.find(code[i]);
    row = floor((double) code_index/ (double) grid_cols);
    col = code_index % grid_cols;
    lat_place_value = (lat_place_value / grid_rows);
    long_place_value = (long_place_value / grid_cols);
    latitude_low += (row * lat_place_value);
    longitude_low += (col * long_place_value);
  }

  output.push_back(latitude_low);
  output.push_back(latitude_low + lat_place_value);
  output.push_back(longitude_low);
  output.push_back(longitude_low + long_place_value);
  return output;
}

std::vector < double > olc_coders::olc_decode_single(std::string olc){

  if(!olc_check_full_single(olc)){
    throw std::range_error("The Open Location Codes provided must be complete. Incomplete code: " + olc);
  }

  //Remove separator and padding character, upper-case
  std::string validated_olc;
  for(unsigned int i = 0; i < olc.size(); i++){
    if(olc[i] != padding[0] && olc[i] != separator[0]){
      validated_olc.push_back(toupper(olc[i]));
    }
  }

  //Decode the pairs
  std::vector < double > output;
  std::vector < double > holding = olc_decode_pair(validated_olc.substr(0, max_pair_length), 0);
  holding[0] -= max_latitude;
  holding[1] -= max_latitude;
  output.insert(output.end(), holding.begin(), holding.end());

  holding = olc_decode_pair(validated_olc.substr(0, max_pair_length), 1);
  holding[0] -= max_longitude;
  holding[1] -= max_longitude;
  output.insert(output.end(), holding.begin(), holding.end());

  if(validated_olc.size() > max_pair_length){
    std::vector < double > grid_decode_results = olc_decode_grid(validated_olc.substr(max_pair_length));
    for(unsigned int i = 0; i < 4; i++){
      output[i] += grid_decode_results[i];
    }
  }

  output.push_back(std::min((output[0] + (output[1] - output[0])/2), (double) max_latitude));
  output.push_back(std::min((output[2] + (output[3] - output[2])/2), (double) max_longitude));
  output.push_back(validated_olc.size());

  return output;
}

CharacterVector olc_coders::olc_encode_vector(NumericVector latitude, NumericVector longitude,
                                              IntegerVector code_length){

  if(latitude.size() != longitude.size()){
    throw std::range_error("There must be as many longitude values as latitude values");
  }

  unsigned int input_size = latitude.size();
  CharacterVector output(input_size);

  if(code_length.size() == 1){
    if(IntegerVector::is_na(code_length[0])){
      for(unsigned int i = 0; i < input_size; i++){
        if((i % 10000) == 0){
          Rcpp::checkUserInterrupt();
        }
        output[i] = NA_STRING;
      }
    } else {
      for(unsigned int i = 0; i < input_size; i++){
        if((i % 10000) == 0){
          Rcpp::checkUserInterrupt();
        }
        if(NumericVector::is_na(latitude[i]) || NumericVector::is_na(longitude[i])){
          output[i] = NA_STRING;
        } else {
          output[i] = olc_encode_single(latitude[i], longitude[i], code_length[0]);
        }
      }
    }

  } else if(code_length.size() == input_size){

    for(unsigned int i = 0; i < input_size; i++){
      if((i % 10000) == 0){
        Rcpp::checkUserInterrupt();
      }

      if(NumericVector::is_na(latitude[i]) || NumericVector::is_na(longitude[i]) || IntegerVector::is_na(code_length[i])){
        output[i] = NA_STRING;
      } else {
        output[i] = olc_encode_single(latitude[i], longitude[i], code_length[i]);
      }
    }

  } else {
    throw std::range_error("the vector code_length must contain either one value, or one value for each input latitude and longitude");
  }

  return output;
}

DataFrame olc_coders::olc_decode_vector(CharacterVector olcs){

  unsigned int input_size = olcs.size();
  NumericVector low_lats(input_size);
  NumericVector low_longs(input_size);
  NumericVector high_lats(input_size);
  NumericVector high_longs(input_size);
  NumericVector center_lats(input_size);
  NumericVector center_longs(input_size);
  IntegerVector code_lengths(input_size);
  NumericVector holding(7);

  for(unsigned int i = 0; i < input_size; i++){

    if(olcs[i] == NA_STRING){
      low_lats[i] = NA_REAL;
      high_lats[i] = NA_REAL;
      low_longs[i] = NA_REAL;
      high_longs[i] = NA_REAL;
      center_lats[i] = NA_REAL;
      center_longs[i] = NA_REAL;
      code_lengths[i] = NA_INTEGER;
    } else {
      holding = olc_decode_single(Rcpp::as<std::string>(olcs[i]));
      low_lats[i] = holding[0];
      high_lats[i] = holding[1];
      low_longs[i] = holding[2];
      high_longs[i] = holding[3];
      center_lats[i] = holding[4];
      center_longs[i] = holding[5];
      code_lengths[i] = holding[6];
    }
  }

  return DataFrame::create(_["latitude_low"] = low_lats,
                           _["longitude_low"] = low_longs,
                           _["latitude_center"] = center_lats,
                           _["longitude_center"] = center_longs,
                           _["latitude_high"] = high_lats,
                           _["longitude_high"] = high_longs,
                           _["code_lengths"] = code_lengths,
                           _["stringsAsFactors"] = false);
}

olc_coders::olc_coders(){
  grid_rows = 5;
  grid_cols = 4;
  grid_degrees = 0.000125;
  max_pair_length = 10;
  resolution_levels.push_back(20.0);
  resolution_levels.push_back(1.0);
  resolution_levels.push_back(.05);
  resolution_levels.push_back(.0025);
  resolution_levels.push_back(.000125);
}
