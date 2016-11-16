/*
  Simon Chen
  sc4900
  N10013388
  Homework 4A
  The purpose of this code is to understand the vector class and the explroe the STL algorithms and functors.

*/

#define CATCH_CONFIG_MAIN

#include <vector>
#include "catch.hpp"

using namespace std; 

//Insert Recursive Function
int getSumVector(const vector<int> & a, int begin, int end){
  if (begin == end) 
    return a[begin];

  int mid = (begin + end)/2;
  return getSumVector(a,begin,mid) + getSumVector(a,mid+1,end);


 
}


//Insert driver function here
int sumVector( const vector<int> & a){
  return a.size() > 0 ? getSumVector(a,0,a.size()-1) : 0;
}

SCENARIO("Testing sumVector") {
  GIVEN("A vector with just one element") {
    vector<int> singleElement = { 1 }; //Note that this is the STL vector, so we can initialize like this
    WHEN("The sumVector function is called") {
      int sum = sumVector(singleElement);
      THEN("The correct sume is returned") {
	REQUIRE(sum == 1); //testing base case
      }
    }
  }
  GIVEN("A vector with odd number of integers ") {
    vector<int> vOdd = { 1,2,3 };
    WHEN("sumVector function is called ") {
      int recSum = sumVector(vOdd);

      vector<int>::iterator itrStart = vOdd.begin();
      vector<int>::iterator itrEnd = vOdd.end();

      int sizeVector = vOdd.size(); 

      THEN("vector stays same after the function call") {
	REQUIRE(itrStart == vOdd.begin());
	REQUIRE(itrEnd == vOdd.end());
      }
      THEN("The size of the vector doesn't change") {
	REQUIRE(sizeVector == vOdd.size());
      }
      THEN("It sums up properly") {
	REQUIRE(recSum ==6);
      }
    }
    GIVEN("A vector with even number of integers ") {
      vector<int> vEven = { 1,2,3,10 };
			
      vector<int>::iterator itrStart = vEven.begin();
      vector<int>::iterator itrEnd = vEven.end();

      int sizeVector = vEven.size();

      WHEN("sumVector function is called ") {

	int recSum = sumVector(vEven);
		
	THEN("vector stays same after the function call") {
	  REQUIRE(itrStart == vEven.begin());
	  REQUIRE(itrEnd == vEven.end());
	}
	THEN("The size of the vector doesn't change") {
	  REQUIRE(sizeVector == vEven.size());
	}
	THEN("It sums up properly") {
	  REQUIRE(recSum == 16);
	}
      }
    }
  }
}

