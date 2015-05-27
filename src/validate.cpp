#include "validate.h"

olc_validate::olc_validate(){
  valid_chars = "CFGHJMPQRVWX23456789+";
}

bool olc_validate::olc_check_single(std::string olc){

  bool output = true;
  int input_size = olc.size();

  if(input_size == 0){
    output = false;
  } else {

    for(unsigned int i = 0; i < input_size; i++){
      if(valid_chars.find(toupper(olc[i])) == std::string::npos){
        output = false;
        break;
      }
    }

  }


  return output;
}

bool olc_validate::olc_check_full_single(std::string olc){

  //Run a character check first to avoid being silly.
  bool output = olc_check_single(olc);
  if(!output){
    return output;
  }

}

bool olc_validate::olc_check_short_single(std::string olc){

  //Run a character check first to avoid being silly.
  bool output = olc_check_single(olc);
  if(!output){
    return output;
  }


}


std::vector < bool > olc_validate::olc_check_vector(std::vector < std::string > olc){

  int input_size = olc.size();
  std::vector < bool > output(input_size);

  for(unsigned int i = 0; i < input_size; i++){
    output[i] = olc_check_single(olc[i]);
  }

  return output;
}
