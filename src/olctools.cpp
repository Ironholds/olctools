#include "validate.h"
using namespace Rcpp;

//'@export
//[[Rcpp::export]]
std::vector < bool > cpp_validate(std::vector < std::string > codes){
  olc_validate validate_inst;
  return validate_inst.olc_check_vector(codes);
}
