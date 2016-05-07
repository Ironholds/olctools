## Open Location Codes in R

An R implementation of the Google [Open Location Codes](https://openlocationcode.com) standard.

__Author:__ Oliver Keyes<br/>
__License:__ [MIT](https://opensource.org/licenses/MIT)<br/>
__Status:__ Stable

![downloads](https://cranlogs.r-pkg.org/badges/grand-total/olctools)
[![Travis-CI Build Status](https://travis-ci.org/Ironholds/olctools.svg?branch=master)](https://travis-ci.org/Ironholds/olctools)

The Google Open Location Code standard allows you to encode the latitude and longitude of an area into a compressed string,
resolving it down to a 14 square meter box. `olctools` provides a fast, vectorised R implementation of this standard that
you can use to encode, decode, shorten, expand or validate OLCs.

Please note that this project is released with a [Contributor Code of Conduct](https://github.com/Ironholds/olctools/blob/master/CONDUCT.md). By participating in this project you agree to abide by its terms.

## Installation

`olctools` depends on Rcpp but is otherwise dependency-free! It can be grabbed from CRAN with:

    install.packages("olctools")
    
Alternately, the development version can be obtained through:

    devtools::install_github("ironholds/olctools")
