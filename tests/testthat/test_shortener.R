context("Test OLC shortening and recovery")

# https://github.com/google/open-location-code/blob/master/test_data/shortCodeTests.csv
test_that("OLC shortening works for simple cases", {
  expect_equal(shorten_olc("9C3W9QCJ+2VX",51.3701125,-1.217765625), "+2VX")
})

test_that("OLC shortening works +/- .000755", {
  expect_equal(shorten_olc("9C3W9QCJ+2VX",51.3708675,-1.217765625), "CJ+2VX")
  expect_equal(shorten_olc("9C3W9QCJ+2VX",51.3701125,-1.217010625), "CJ+2VX")
})

test_that("OLC shortening works +/- .0151", {
  expect_equal(shorten_olc("9C3W9QCJ+2VX",51.3852125,-1.217765625), "9QCJ+2VX")
  expect_equal(shorten_olc("9C3W9QCJ+2VX",51.3550125,-1.217765625), "9QCJ+2VX")
  expect_equal(shorten_olc("9C3W9QCJ+2VX",51.3701125,-1.232865625), "9QCJ+2VX")
  expect_equal(shorten_olc("9C3W9QCJ+2VX",51.3701125,-1.202665625), "9QCJ+2VX")
})

test_that("OLC recovery works",{
  expect_equal(recover_olc("9G8F+6X", 47.4, 8.6), "8FVC9G8F+6X")
})
