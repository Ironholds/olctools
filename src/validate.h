//[[Rcpp::depends(BH)]]
#include <Rcpp.h>
#include <boost/regex.hpp>
using namespace Rcpp;

#ifndef __OLC_VALIDATE__
#define __OLC_VALIDATE__

class olc_validate {

protected:

  std::string valid_chars;

  std::string separator;

  int separator_position;

  std::string padding;

  boost::regex padding_regex;

  std::string character_set;

  int charset_length;

  int max_latitude;

  int max_longitude;

  bool olc_check_full_single(std::string olc);

private:

  bool olc_check_single(std::string olc);

  bool olc_check_short_single(std::string olc);

  bool olc_check_either_single(std::string olc);

public:

  std::vector < bool > olc_check_full_vector(std::vector < std::string > olc);
  std::vector < bool > olc_check_short_vector(std::vector < std::string > olc);
  std::vector < bool > olc_check_either_vector(std::vector < std::string > olc);
  olc_validate();
};

#endif
