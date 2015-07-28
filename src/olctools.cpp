#include "validate.h"
#include "coders.h"
using namespace Rcpp;

//'@title Check the Validity of Open Location Codes
//'@description These functions allow a useR to check whether OLCs they've
//'been provided are valid or not. \code{valid_short} identifies whether
//'a vector of OLCs are valid "short" codes; \code{valid_long} identifies
//'whether OLCs are valid "long" codes, and \code{valid_full} identifies
//'whether OLCs are valid, full stop.
//'
//'@param codes a character vector containing Open Location Codes.
//'
//'@return a vector of TRUE and FALSE values, where TRUE corresponds to a
//'valid code and FALSE an invalid.
//'
//'@examples
//'#Validate that a particular OLC is valid
//'valid_olc("WC2345+G6g")
//'#[1] TRUE
//'
//'#It is! Is it a short?
//'valid_short("WC2345+G6g")
//'#[1] TRUE
//'#Yep!
//'@export
//'@aliases olc_validate
//'@rdname olc_validate
//[[Rcpp::export]]
std::vector < bool > validate_olc(std::vector < std::string > codes){
  olc_validate validate_inst;
  return validate_inst.olc_check_either_vector(codes);
}

//'@rdname olc_validate
//'@export
//[[Rcpp::export]]
std::vector < bool > validate_short(std::vector < std::string > codes){
  olc_validate validate_inst;
  return validate_inst.olc_check_short_vector(codes);
}

//'@rdname olc_validate
//'@export
//[[Rcpp::export]]
std::vector < bool > validate_full(std::vector < std::string > codes){
  olc_validate validate_inst;
  return validate_inst.olc_check_full_vector(codes);
}

//'@export
//[[Rcpp::export]]
std::vector < std::string > encode_olc(std::vector < double > latitude, std::vector < double > longitude,
                                       std::vector < int > code_length){
  olc_coders code_inst;
  return code_inst.olc_encode_vector(latitude, longitude, code_length);
}
