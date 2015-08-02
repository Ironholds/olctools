context("Test OLC decoding")

# We need to make sure both are being properly rounded, here.
format_num <- function(n){
  unlist(lapply(n, function(x){
    return(signif(x, 8))
  }))
}

# Uses https://github.com/google/open-location-code/blob/master/test_data/encodingTests.csv
test_that("OLC decoding works for very simple cases", {
  result <- unlist(decode_olc("7FG49Q00+"))
  expect_that(result[c(3,4,7)], is_equivalent_to(c(20.375, 2.775, 6)))
  result <- unlist(decode_olc("7FG49QCJ+2V"))
  expect_that(result[c(3,4,7)], is_equivalent_to(c(20.3700625, 2.7821875, 10)))
})

test_that("OLC decoding works for more-complex cases with lengths > 10", {
  result <- unlist(decode_olc("7FG49QCJ+2VX"))
  expect_that(format_num(result[c(3,4,7)]), is_equivalent_to(format_num(c(20.3700625, 2.7821875, 11))))
  result <- unlist(decode_olc("7FG49QCJ+2VXGJ"))
  expect_that(format_num(result[c(3,4,7)]), is_equivalent_to(format_num(c(20.3700625, 2.7821875, 13))))
  result <- unlist(decode_olc("8FVC2222+22"))
  expect_that(format_num(result[c(3,4,7)]), is_equivalent_to(format_num(c(47.0000625, 8.0000625, 10))))
})

test_that("Negative values can be decoded", {
  result <- unlist(decode_olc("4VCPPQGP+Q9"))
  expect_that(format_num(result[c(3,4,7)]), is_equivalent_to(format_num(c(-41.2730625, 174.7859375, 10))))
})
