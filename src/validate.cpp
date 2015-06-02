#include "validate.h"

olc_validate::olc_validate(){
  valid_chars = "CFGHJMPQRVWX23456789+0";
  separator = "+";
  separator_position = 8;
  padding = "0";
  padding_regex = std::regex((padding + "+"));
}

bool olc_validate::olc_check_single(std::string olc){

  //Scan for illegal characters
  int input_size = olc.size();
  if(input_size == 0){
    return false;
  } else {

    for(unsigned int i = 0; i < input_size; i++){
      if(valid_chars.find(toupper(olc[i])) == std::string::npos){
        return false;

      }
    }

  }

  //Check that the separator is present
  size_t separator_location = olc.find(separator);
  if(separator_location == std::string::npos){
    return false;
  }

  //Are there >1? Also a no-no
  if(separator_location != olc.rfind(separator)){
    return false;

  }

  //Is it present in a valid location?
  if(separator_location > separator_position || separator_location % 2 == 1){
    return false;
  }

  //Is there only 1 character after the separator? (you don't need to have chars but
  //you can't have just 1)
  //(C++ is 0-offset and that includes find() results. Sigh.)
  if((olc.size() - separator_location) == 2){
    return false;
  }

  //Check if padding is present
  std::sregex_iterator iter(olc.begin(), olc.end(), padding_regex);
  std::sregex_iterator end;
  std::smatch results;
  int regex_count = 0;

  while(iter != end){
    results = *iter;
    iter++;
    regex_count++;
  }

  //If it is present..
  if(regex_count){

    //Multiple instances is verboten
    if(regex_count > 1){
      return false;
    }

    //So is a single instant with a non-even count.
    if(results.length(0) % 2 == 1){
      return false;
    }

    //..and so is a single instance starting at 0
    if(results.position(0) == 0){
      return false;
    }
  }

  return true;
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
