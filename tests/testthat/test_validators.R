context("Test OLC validation")

test_that("Obviously invalid OLCs can be identified", {
  expect_that(valid_olc("this has an invalid character. Lots!"), equals(FALSE))
})
