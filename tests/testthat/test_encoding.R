context("Test OLC encoding")

# Uses https://github.com/google/open-location-code/blob/master/test_data/encodingTests.csv
test_that("OLC encoding works for very simple cases", {
  expect_that(encode_olc(20.375, 2.775, 6), equals("7FG49Q00+"))
  expect_that(encode_olc(20.3700625, 2.7821875, 10), equals("7FG49QCJ+2V"))
})

test_that("OLC encoding works for more-complex cases with lengths > 10",{
  expect_that(encode_olc(20.3701125, 2.782234375, 11), equals("7FG49QCJ+2VX"))
  expect_that(encode_olc(20.3701135, 2.78223535156, 13), equals("7FG49QCJ+2VXGJ"))
  expect_that(encode_olc(47.0000625,8.0000625, 10), equals("8FVC2222+22"))
})

test_that("Negative values can be encoded", {
  expect_that(encode_olc(-41.2730625,174.7859375, 10), equals("4VCPPQGP+Q9"))
})

test_that("OLC encoding throws an error with odd-numbered requested lengths below 8",{
  expect_that(encode_olc(20.375, 2.775, 5), throws_error("The length value"))
  expect_that(encode_olc(20.375, 2.775, 7), throws_error("The length value"))
})

