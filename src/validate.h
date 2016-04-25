#include <Rcpp.h>
using namespace Rcpp;

#ifndef __OLC_VALIDATE__
#define __OLC_VALIDATE__

class olc_validate {

protected:

  /**
   * Valid characters for an OLC to have. Basically the character set and + or 0.
   */
  std::string valid_chars;

  /**
   * The separator character for an OLC
   */
  std::string separator;

  /**
   * Where in the OLC the separator character should appear.
   */
  unsigned int separator_position;

  /**
   * The padding character (0).
   */
  std::string padding;

  std::string character_set;

  int charset_length;

  int max_latitude;

  int max_longitude;

  bool olc_check_full_single(std::string olc);

  bool olc_check_short_single(std::string olc);

private:

  bool olc_check_single(std::string olc);

  bool olc_check_either_single(std::string olc);

public:

  LogicalVector olc_check_full_vector(CharacterVector olc);
  LogicalVector olc_check_short_vector(CharacterVector olc);
  LogicalVector olc_check_either_vector(CharacterVector olc);
  olc_validate();
};

#endif
