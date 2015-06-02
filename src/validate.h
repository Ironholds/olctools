#include <Rcpp.h>
#include <regex>
using namespace Rcpp;

#ifndef __OLC_VALIDATE__
#define __OLC_VALIDATE__

class olc_validate {

private:

  std::string valid_chars;
  std::string separator;
  int separator_position;
  std::string padding;
  std::regex padding_regex;

  bool olc_check_single(std::string olc);

  bool olc_check_full_single(std::string olc);

  bool olc_check_short_single(std::string olc);

  bool olc_check_either_single(std::string olc);

public:
  olc_validate();

  std::vector < bool > olc_check_full_vector(std::vector < std::string > olc);
  std::vector < bool > olc_check_short_vector(std::vector < std::string > olc);
  std::vector < bool > olc_check_either_vector(std::vector < std::string > olc);

};

#endif
