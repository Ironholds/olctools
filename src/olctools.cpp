#include "validate.h"
#include "coders.h"
#include "manipulate.h"

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
//'@seealso \code{\link{decode_olc}} and \code{\link{encode_olc}} for creating
//'and resolving valid Open Location Codes.
//'
//'@examples
//'#Validate that a particular OLC is valid
//'validate_olc("WC2345+G6g")
//'#[1] TRUE
//'
//'#It is! Is it a short?
//'validate_short("WC2345+G6g")
//'#[1] TRUE
//'#Yep!
//'
//'#So it's not full?
//'validate_full("WC2345+G6g")
//'#[1] FALSE
//'#Nope!
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
//'@seealso \code{\link{decode_olc}} for the opposite operation.
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

//'@title Decode Open Location Codes into Latitude and Longitude Pairs
//'@description \code{decode_olc} takes Open Location Codes and, if they're
//'valid (see \code{\link{validate_full}}) returns the minium, centred and maximum
//'latitude and longitude for those coordinates.
//'
//'@param olcs a vector of Open Location Codes, generated through \code{encode_olc} or
//'an equivalent tool.
//'
//'@examples
//'decode_olc("7FG49Q00+")
//'
//'@seealso \code{\link{encode_olc}} for the opposite operation.
//'
//'@export
//[[Rcpp::export]]
DataFrame decode_olc(std::vector < std::string > olcs){
  olc_coders code_inst;
  return code_inst.olc_decode_vector(olcs);
}

//'@export
//[[Rcpp::export]]
std::vector < std::string > shorten_olc(std::vector < std::string > olcs, std::vector < double > latitudes,
                                        std::vector < double > longitudes){
  olc_manipulate manip_inst;
  return manip_inst.shorten_vector(olcs, latitudes, longitudes);
}
