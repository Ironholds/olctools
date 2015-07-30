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

double olc_coders::lat_precision(int length){
  if(length < 10){
    return pow(20, floor(length/ -2 +2));
  }
  return pow(20, -3)/pow(grid_rows, length - 10);
}

std::string olc_coders::olc_encode_single(double lat, double longitude, int output_length){

  if(output_length < 2 || (output_length < separator_position && output_length % 2 == 1)){
    throw std::range_error("The code_length value you have provided is not valid; see the documentation");
  }

  std::string output;
  lat = clip_lat(lat);
  longitude = clip_longitude(longitude);

  if(lat == 90){
    lat = lat_precision(output_length);
  }

  int to_encode_length = fmin(output_length, max_pair_length);
  double adjusted_lat = lat + max_latitude;
  double adjusted_long = longitude + max_longitude;
  int digit_value, digit_count = 0;
  double place_value;

  while(digit_count < to_encode_length){

    //Lat first
    place_value = resolution_levels[floor(digit_count/2)];
    digit_value = floor(adjusted_lat/place_value);
    adjusted_lat -= digit_value * place_value;
    output+= character_set[digit_value];
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


  if(output.size() < separator_position){
    while(output.size() < separator_position){
      output += padding;
    }
  }

  if(output.size() == separator_position){
    output += separator;
  }

  return output;
}

std::vector < double > olc_coders::olc_decode_single(std::string olc){


}

std::vector < std::string > olc_coders::olc_encode_vector(std::vector < double > latitude, std::vector < double > longitude,
                                          std::vector < int > code_length){

  if(latitude.size() != longitude.size()){
    throw std::range_error("There must be as many longitude values as latitude values");
  }

  int input_size = latitude.size();
  std::vector < std::string > output(input_size);

  if(code_length.size() == 1){

    for(unsigned int i = 0; i < input_size; i++){
      output[i] = olc_encode_single(latitude[i], longitude[i], code_length[0]);
    }

  } else if(code_length.size() == input_size){

    for(unsigned int i = 0; i < input_size; i++){
      output[i] = olc_encode_single(latitude[i], longitude[i], code_length[i]);
    }

  } else {
    throw std::range_error("the vector code_length must contain either one value, or one value for each input latitude and longitude");
  }

  return output;
}

DataFrame olc_coders::olc_decode_vector(std::vector < std::string > olc){

}
