#include <Rcpp.h>
#include <regex>
using namespace Rcpp;

#ifndef __OLC_VALIDATE__
#define __OLC_VALIDATE__

class olc_validate {

protected:

  std::string valid_chars = "CFGHJMPQRVWX23456789+0";

  std::string separator = "+";

  int separator_position = 8;

  std::string padding = "0";

  std::regex padding_regex = std::regex((padding + "+"));

  std::string character_set = "23456789CFGHJMPQRVWX";

  int charset_length = character_set.size();

  int max_latitude = 90;

  int max_longitude = 100;

private:

  bool olc_check_single(std::string olc);

  bool olc_check_full_single(std::string olc);

  bool olc_check_short_single(std::string olc);

  bool olc_check_either_single(std::string olc);

public:

  std::vector < bool > olc_check_full_vector(std::vector < std::string > olc);
  std::vector < bool > olc_check_short_vector(std::vector < std::string > olc);
  std::vector < bool > olc_check_either_vector(std::vector < std::string > olc);

};

#endif
