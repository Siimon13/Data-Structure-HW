/*
  Simon Chen
  N10013388
  sc4900
  Homework 4B

  The purpose of this program is to test our knowledge of runtime and using differet collections and to parse a text file for data
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <string>
using namespace std;

template <class Object>
bool dupTestList(const vector<Object>& vec) {
  // put your code here 

  list<Object> dupList;
  

  for(Object i: vec){
    typename list<Object>::iterator itr = dupList.begin();

    for(; itr != dupList.end();++itr){
      if(*itr == i)
	return true;
    }
    dupList.push_back(i);
  }
  
  return false;
  
}

template <class Object>
bool dupTestSort(const vector<Object>& vec) {
  // put your code here
  vector<Object> copy;
  
  for(Object i : vec){
    copy.push_back(i);
  }
  
  sort(copy.begin(),copy.end());

  for(size_t i = 0; copy.size() != 0 && i < copy.size()-1; ++i){
    if (copy[i] == copy[i+1])
      return true;
  }
  return false;
}

template <class Object>
bool dupTestSet(const vector<Object>& vec) {
  // put your code here 
  set<Object> testSet;

  for(Object i : vec){
    pair<typename set<Object>::iterator,bool> ret = testSet.insert(i);
    if(!ret.second) 
      return true;
  }

  return false;
}

template <class Object>
bool dupTestUnorderedSet(const vector<Object>& vec) {
  // put your code here 
  unordered_set<Object> testUnOrdSet;

  for(Object i : vec){
    pair<typename unordered_set<Object>::iterator,bool> ret = testUnOrdSet.insert(i);
    if(!ret.second) 
      return true;

  }

  return false;
}

SCENARIO("Testing check if there is duplicates") {
  GIVEN("A vector of int with no duplicates") {
    vector<int> intvec;
    intvec.push_back(1);
    intvec.push_back(2);
    intvec.push_back(3);
    WHEN("Checking duplicates with list") {
      bool isDup = dupTestList(intvec);
      THEN("It should return false") {
	REQUIRE(isDup == false); 
      }
    }
    WHEN("Checking duplicates with sort+vec") {
      bool isDup = dupTestSort(intvec);
      THEN("It should return false") {
	REQUIRE(isDup == false);
      }
    }
    WHEN("Checking duplicates with set") {
      bool isDup = dupTestSet(intvec);
      THEN("It should return false") {
	REQUIRE(isDup == false);
      }
    }
    WHEN("Checking duplicates with unordered set") {
      bool isDup = dupTestUnorderedSet(intvec);
      THEN("It should return false") {
	REQUIRE(isDup == false);
      }
    }
  }
  GIVEN("A vector of char with duplicates") {
    vector<char> charvec;
    charvec.push_back('a');
    charvec.push_back('c');
    charvec.push_back('a');
    WHEN("Checking duplicates with list") {
      bool isDup = dupTestList(charvec);
      THEN("It should return true") {
	REQUIRE(isDup == true);
      }
    }
    WHEN("Checking duplicates with sort+vec") {
      bool isDup = dupTestSort(charvec);
      THEN("It should return true") {
	REQUIRE(isDup == true);
      }
    }
    WHEN("Checking duplicates with set") {
      bool isDup = dupTestSet(charvec);
      THEN("It should return true") {
	REQUIRE(isDup == true);
      }
    }
    WHEN("Checking duplicates with unordered set") {
      bool isDup = dupTestUnorderedSet(charvec);
      THEN("It should return true") {
	REQUIRE(isDup == true);
      }
    }
  }
  GIVEN("An empty vector of string") {
    vector<string> svec;
    WHEN("Checking duplicates with list") {
      bool isDup = dupTestList(svec);
      THEN("It should return false") {
	REQUIRE(isDup == false);
      }
    }
    WHEN("Checking duplicates with sort+vec") {
      bool isDup = dupTestSort(svec);
      THEN("It should return false") {
	REQUIRE(isDup == false);
      }
    }
    WHEN("Checking duplicates with set") {
      bool isDup = dupTestSet(svec);
      THEN("It should return false") {
	REQUIRE(isDup == false);
      }
    }
    WHEN("Checking duplicates with unordered set") {
      bool isDup = dupTestUnorderedSet(svec);
      THEN("It should return false") {
	REQUIRE(isDup == false);
      }
    }
  }
}
