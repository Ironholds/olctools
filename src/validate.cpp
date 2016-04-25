#include "validate.h"

bool olc_validate::olc_check_single(std::string olc){

  //Scan for illegal characters
  unsigned int input_size = olc.size();
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
  size_t regex_result = olc.find(padding);
  if(regex_result == 0){
    return false;
  } else if(regex_result != std::string::npos){

    signed int last_loc = regex_result;
    int match_sum = 1;

    while(regex_result != std::string::npos){
      regex_result = olc.find(padding, regex_result + 1);
      if(regex_result != std::string::npos){
        if(last_loc + 1 != (signed int) regex_result){
          return false;
        }
        match_sum++;
      }
    }

    if(match_sum % 2 == 1){
      return false;
    }

    if(separator_location != (olc.size() - 1)){
      return false;
    }
  }

  return true;
}

bool olc_validate::olc_check_full_single(std::string olc){

  //Run a character check first to avoid being silly.
  //If it's not valid, or is a valid short, it's not a valid full.
  if(!olc_check_single(olc) || olc_check_short_single(olc)){
    return false;
  }

  //Retrieve the first latitude value (the first value), decode
  //it into numeric, and see if it's >= 180. If so, unpossible.
  if( (signed int) (character_set.find(olc[0]) * charset_length) >= (max_latitude * 2)){
    return false;
  }

  //Do the same for longitude, only this time >=360
  if(olc.size() > 1){
    if( (signed int) (character_set.find(olc[1]) * charset_length) >= (max_longitude * 2)){
      return false;
    }
  }

  return true;
}

bool olc_validate::olc_check_short_single(std::string olc){

  //Run a character check first to avoid being silly.
  if(!olc_check_single(olc)){
    return false;
  }

  //If the separator is < separator_position..it's a short.
  if(olc.find(separator) != std::string::npos && (unsigned int) olc.find(separator) < separator_position){
    return true;
  };

  //Otherwise, false.
  return false;
}

bool olc_validate::olc_check_either_single(std::string olc){

  if(olc_check_full_single(olc) || olc_check_short_single(olc)){
    return true;
  }

  return false;
}

LogicalVector olc_validate::olc_check_full_vector(CharacterVector olc){
  unsigned int input_size = olc.size();
  LogicalVector output(input_size);

  for(unsigned int i = 0; i < input_size; i++){
    if((i % 10000) == 0){
      Rcpp::checkUserInterrupt();
    }
    if(olc[i] == NA_STRING){
      output[i] = NA_LOGICAL;
    } else {
      output[i] = olc_check_full_single(Rcpp::as<std::string>(olc[i]));
    }
  }

  return output;
}

LogicalVector olc_validate::olc_check_short_vector(CharacterVector olc){
  unsigned int input_size = olc.size();
  LogicalVector output(input_size);

  for(unsigned int i = 0; i < input_size; i++){
    if((i % 10000) == 0){
      Rcpp::checkUserInterrupt();
    }
    if(olc[i] == NA_STRING){
      output[i] = NA_LOGICAL;
    } else {
      output[i] = olc_check_short_single(Rcpp::as<std::string>(olc[i]));
    }
  }

  return output;
}

LogicalVector olc_validate::olc_check_either_vector(CharacterVector olc){
  unsigned int input_size = olc.size();
  LogicalVector output(input_size);

  for(unsigned int i = 0; i < input_size; i++){
    if((i % 10000) == 0){
      Rcpp::checkUserInterrupt();
    }
    if(olc[i] == NA_STRING){
      output[i] = NA_LOGICAL;
    } else {
      output[i] = olc_check_either_single(Rcpp::as<std::string>(olc[i]));
    }
  }

  return output;
}

olc_validate::olc_validate(){
  valid_chars = "CFGHJMPQRVWX23456789+0";
  separator = "+";
  separator_position = 8;
  padding = "0";
  character_set = "23456789CFGHJMPQRVWX";
  charset_length = character_set.size();
  max_latitude = 90;
  max_longitude = 180;
}
