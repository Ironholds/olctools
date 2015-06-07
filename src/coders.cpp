#include "coders.h"

std::string olc_coders::olc_encode_single(double lat, double long, int output_length){

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

  } else if(code_length.size() == input_size){

  } else {
    throw std::range_error("the vector code_length must contain either one value, or one value for each input latitude and longitude");
  }

}

DataFrame olc_coders::olc_decode_vector(std::vector < std::string > olc){

}
