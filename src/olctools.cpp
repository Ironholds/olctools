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

//'@title Encode Latitude and Longitude Pairs as Open Location Codes
//'@description \code{encode_olc} creates Open Location Codes from
//'latitude and longitude values, of a specified length.
//'
//'@param lats a numeric vector of latitudes.
//'
//'@param longs a numeric vector of longitudes, equivalent in size to \code{lats}
//'
//'@param length the length you want the resulting OLCs to be. The conventional lengths
//'are 10 or 11, with any number above 8 and any \emph{even} number below it being acceptable. \code{length}
//'should consist of either a single value, if you want all codes to be calculated to the same length, or a
//'vector of values the same size as \code{lats} and \code{longs} if you want to pre-set values.
//'
//'@examples
//'encode_olc(20.375, 2.775,6)
//'
//'@export
//[[Rcpp::export]]
std::vector < std::string > encode_olc(std::vector < double > lats, std::vector < double > longs,
                                       std::vector < int > length){
  olc_coders code_inst;
  return code_inst.olc_encode_vector(lats, longs, length);
}

//'@export
//[[Rcpp::export]]
DataFrame decode_olc(std::vector < std::string > olcs){
  olc_coders code_inst;
  return code_inst.olc_decode_vector(olcs);
}
