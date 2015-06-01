context("Test OLC validation")

test_that("Strings with illegal characters can be identified", {
  expect_that(valid_olc("this has an invalid character. Lots!"), equals(FALSE))
})

test_that("Strings missing a separator can be identified", {
  expect_that(valid_olc("G"), equals(FALSE))
})

test_that("Strings with multiple separators can be identified", {
  expect_that(valid_olc("GG+C+"), equals(FALSE))
})

test_that("Strings with separators in the wrong place can be identified", {
  expect_that(valid_olc("GG2+"), equals(FALSE))
})
