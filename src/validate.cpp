#include "validate.h"

olc_validate::olc_validate(){
  valid_chars = "CFGHJMPQRVWX23456789+";
  separator = "+";
  separator_position = 8;
  padding = "0";
}

bool olc_validate::olc_check_single(std::string olc){

  //Set up for scanning
  bool output = true;
  int input_size = olc.size();

  //Scan for illegal characters
  if(input_size == 0){
    output = false;
  } else {

    for(unsigned int i = 0; i < input_size; i++){
      if(valid_chars.find(toupper(olc[i])) == std::string::npos){
        output = false;
        return output;
      }
    }

  }

  //Check that the separator is present
  size_t separator_location = olc.find(separator);
  if(separator_location == std::string::npos){
    output = false;
    return output;
  }

  //If it is present, are there >1? Also a no-no
  if(separator_location != olc.rfind(separator)){
    output = false;
    return output;
  }

  //If it is present, is it present in a valid location?
  if(separator_location > separator_position || separator_location % 2 == 1){
    output = false;
    return output;
  }

}

bool olc_validate::olc_check_full_single(std::string olc){

  //Run a character check first to avoid being silly.
  bool output = olc_check_single(olc);
  if(!output){
    return output;
  }
  return output;
}

bool olc_validate::olc_check_short_single(std::string olc){

  //Run a character check first to avoid being silly.
  bool output = olc_check_single(olc);
  if(!output){
    return output;
  }

  return output;
}

bool olc_validate::olc_check_either_single(std::string olc){

  if(olc_check_full_single(olc) || olc_check_short_single(olc)){
    return true;
  }

  return false;
}

std::vector < bool > olc_validate::olc_check_full_vector(std::vector < std::string > olc){
  int input_size = olc.size();
  std::vector < bool > output(input_size);

  for(unsigned int i = 0; i < input_size; i++){
    output[i] = olc_check_full_single(olc[i]);
  }

  return output;
}

std::vector < bool > olc_validate::olc_check_short_vector(std::vector < std::string > olc){
  int input_size = olc.size();
  std::vector < bool > output(input_size);

  for(unsigned int i = 0; i < input_size; i++){
    output[i] = olc_check_short_single(olc[i]);
  }

  return output;
}

std::vector < bool > olc_validate::olc_check_either_vector(std::vector < std::string > olc){
  int input_size = olc.size();
  std::vector < bool > output(input_size);

  for(unsigned int i = 0; i < input_size; i++){
    output[i] = olc_check_either_single(olc[i]);
  }

  return output;
}
