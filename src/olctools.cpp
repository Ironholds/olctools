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
LogicalVector validate_olc(CharacterVector codes){
  olc_validate validate_inst;
  return validate_inst.olc_check_either_vector(codes);
}

//'@rdname olc_validate
//'@export
//[[Rcpp::export]]
LogicalVector validate_short(CharacterVector codes){
  olc_validate validate_inst;
  return validate_inst.olc_check_short_vector(codes);
}

//'@rdname olc_validate
//'@export
//[[Rcpp::export]]
LogicalVector validate_full(CharacterVector codes){
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
//'@seealso \code{\link{decode_olc}} for the opposite operation, and \code{\link{shorten_olc}} to convert
//'"full" Open Location Codes to "short" Open Location Codes.
//'
//'@examples
//'encode_olc(20.375, 2.775,6)
//'
//'@export
//[[Rcpp::export]]
CharacterVector encode_olc(NumericVector lats, NumericVector longs, IntegerVector length){
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
//'@seealso \code{\link{encode_olc}} for the opposite operation, and \code{\link{shorten_olc}} to convert
//'"full" Open Location Codes to "short" Open Location Codes.
//'
//'@export
//[[Rcpp::export]]
DataFrame decode_olc(CharacterVector olcs){
  olc_coders code_inst;
  return code_inst.olc_decode_vector(olcs);
}

//'@title Shorten Full Open Location Codes
//'@description One of the things that makes OLCs useful is that they can shortened - you can trim
//'characters off them, saving space without substantially compromising the accuracy. \code{shorten_olc}
//'takes full-length OLCs (generated with \code{\link{encode_olc}} or any other way) and shortens them.
//'
//'@param olcs a vector of open location codes, generated with \code{\link{encode_olc}} or through
//'any other means.
//'
//'@param lats a numeric vector of latitudes.
//'
//'@param longs a numeric vector of longitudes, equivalent in size to \code{lats}.
//'
//'@seealso \code{\link{encode_olc}} to create full Open Location Codes.
//'@examples
//'#Encode an OLC and then shorten it
//'olc <- encode_olc(51.3708675,-1.217765625, 12)
//'validate_full(olc)
//'# [1] TRUE
//'
//'olc <- shorten_olc(olc, 51.3708675,-1.217765625)
//'validate_short(olc)
//'# [1] TRUE
//'
//'@export
//[[Rcpp::export]]
CharacterVector shorten_olc(CharacterVector olcs, NumericVector lats, NumericVector longs){
  olc_manipulate manip_inst;
  return manip_inst.shorten_vector(olcs, lats, longs);
}

//'@title Recover Full Open Location Codes From Shortened Codes
//'@description \code{\link{shorten_olc}} (and other sources) shorten a code, reducing
//'the space it occupies. They also limit its ability to be translated back into latitude/longitude
//'pairs. \code{recover_olc} recovers a full code from a shortened one, allowing it to be decoded with
//'\code{\link{decode_olc}}. \emph{Some} loss of accuracy or precision is expected - and as it finds
//'the closest match to the coordinates rather than to the original code, the characters may be very
//'different.
//'
//'@param olcs a vector of short open location codes, generated with \code{\link{shorten_olc}} or through
//'any other means.
//'
//'@param lats a numeric vector of latitudes.
//'
//'@param longs a numeric vector of longitudes, equivalent in size to \code{lats}.
//'
//'@examples
//'# Shorten an OLC and then recover the nearest full code. Note the actual characters differ.
//'shortened_code <- shorten_olc("8FVC9G8F+6X", 47.5, 8.5);
//'recovered_code <- recover_olc(shortened_code, 47.4, 8.6);
//'
//'@export
//[[Rcpp::export]]
CharacterVector recover_olc(CharacterVector olcs, NumericVector lats, NumericVector longs){
  olc_manipulate manip_inst;
  return manip_inst.recover_vector(olcs, lats, longs);
}
