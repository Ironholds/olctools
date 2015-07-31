context("Test OLC validation")

test_that("Invalid OLCs can be identified", {
  invalid_olcs <- c("8FWC2345+G", "8FWC2_45+G6", "8FWC2η45+G6",
                    "8FWC2345+G6+", "8FWC2300+G6", "WC2300+G6g","WC2345+G")

  expect_that(any(validate_olc(invalid_olcs)), equals(FALSE))
})

test_that("Invalid short OLCs can be identified", {
  invalid_shorts <- c("8FWC2345+G6", "8FWC2345+G6G", "8fwc2345+",
                      "8FWCX400+")
  expect_that(any(validate_short(invalid_shorts)), equals(FALSE))
})

test_that("Valid short OLCs can be identified", {
  valid_shorts <- c("WC2345+G6g","2345+G6", "45+G6", "+G6")
  expect_that(all(validate_short(valid_shorts)), equals(TRUE))
})

test_that("Invalid full OLCs can be identified", {
  invalid_full <- c("WC2345+G6g","2345+G6", "45+G6", "+G6")
  expect_that(any(validate_full(invalid_full)), equals(FALSE))
})

test_that("Valid full OLCs can be identified", {
  valid_fulls <- c("8FWC2345+G6","8FWC2345+G6G", "8FWCX400+")
  expect_that(all(validate_full(valid_fulls)), equals(TRUE))
})
