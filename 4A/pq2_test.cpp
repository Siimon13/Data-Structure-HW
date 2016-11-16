/*
  Simon Chen
  sc4900
  N10013388
  Homework 4A
  The purpose of this code is to understand the vector class and the explroe the STL algorithms and functors.

*/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

int sumDigits(int x) {
  //Insert Code here
  if (x < 0) x *= -1;
  if (x < 10) return x;
  return x%10 +   sumDigits(x/10);

}

SCENARIO("Testing Question 2") {
  GIVEN("A one digit positive integer ") {
    WHEN("sumDigits is called") {
      int sum = sumDigits(5);
      THEN("theSum should be ") {
	REQUIRE(sum == 5);
      }
    }
  }
  GIVEN("A one digit negative integer") {
    WHEN("sumDigits is called") {
      int sum = sumDigits(-5);
      THEN("theSum should be ") {
	REQUIRE(sum == 5);
      }
    }
  }
  GIVEN("A positive integer ") {
    WHEN("sumDigits is called") {
      int sum = sumDigits(363);
      THEN("theSum should be ") {
	REQUIRE(sum == 12);
      }
    }
  }
  GIVEN("A negative integer") {
    WHEN("sumDigits is called") {
      int sum = sumDigits(-363);
      THEN("theSum should be ") {
	REQUIRE(sum == 12);
      }
    }
  }
}
