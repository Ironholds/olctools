context("Test OLC encoding")

# Uses https://github.com/google/open-location-code/blob/master/test_data/encodingTests.csv
test_that("OLC encoding works for very simple cases", {
  expect_that(encode_olc(20.375, 2.775, 6), equals("7FG49Q00+"))
  expect_that(encode_olc(20.3700625, 2.7821875, 10), equals("7FG49QCJ+2V"))
})

test_that("OLC encoding throws an error with odd-numbered requested lengths below 8",{
  expect_that(encode_olc(20.375, 2.775, 5), throws_error("The length value"))
  expect_that(encode_olc(20.375, 2.775, 7), throws_error("The length value"))

})
