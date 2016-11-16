/*
  Simon Chen
  N10013388
  Homework 1

  The goal of this function is to understand Big Oh, through testing the scaling of various functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <time.h>

using namespace std;

class timer {
public:
  timer() : start(clock()) {}
  double elapsed() { return ( clock() - start ) / CLOCKS_PER_SEC; }
  void reset() { start = clock(); }
private:
  double start;
};

//Use the following code from Weiss’ book ”Data Structures and Algorithm Analysis in C++” (4th edition) http://users.cis.fiu.edu/~weiss/dsaa_c++4/code/MaxSumTest.cpp


/**
 * Cubic maximum contiguous subsequence sum algorithm.
 */
int maxSubSum1( const vector<int> & a ){
  int maxSum = 0;

  for( size_t i = 0; i < a.size(); ++i )
    for( size_t j = i; j < a.size( ); ++j )
      {
	int thisSum = 0;

	for( size_t k = i; k <= j; ++k )
	  thisSum += a[ k ];

	if( thisSum > maxSum )
	  maxSum   = thisSum;
      }

  return maxSum;
}


/**
 * Quadratic maximum contiguous subsequence sum algorithm.
 */
int maxSubSum2( const vector<int> & a )
{
  int maxSum = 0;

  for( size_t i = 0; i < a.size(); ++i )
    {
      int thisSum = 0;
      for( size_t j = i; j < a.size( ); ++j )
	{
	  thisSum += a[ j ];

	  if( thisSum > maxSum )
	    maxSum = thisSum;
	}
    }

  return maxSum;
}


/**
 * Linear-time maximum contiguous subsequence sum algorithm.
 */

int maxSubSum4( const vector<int> & a )
{
  int maxSum = 0, thisSum = 0;

  for( size_t j = 0; j < a.size( ); ++j )
    {
      thisSum += a[ j ];

      if( thisSum > maxSum )
	maxSum = thisSum;
      else if( thisSum < 0 )
	thisSum = 0;
    }

  return maxSum;
}

vector<int> makeList(const int len){

  vector<int> list(len);
  cout << "Making List of len "<<len << '\n';
  for(int i = 0; i < len; i++){
    list.push_back((rand() % 2001) - 1000);
  }
  return list; 
}

void question1(){
  //==========Timer Settings========================
  timer start;
  cout.setf( ios::fixed, ios::floatfield );
  cout.precision( 6 );
  
  //Question 1====================================================
  
  //========First Test===============================
  cout << "====================First Test====================" << endl;
  
  int firstTest = pow(2,7);

  vector<int> firstList = makeList(firstTest);

  start.reset();
  cout << "Max Sum 1: " << maxSubSum1(firstList) << endl;
  cout << "Time for Sum1: " << start.elapsed() << endl;

  start.reset();
  cout << "Max Sum 2: " << maxSubSum2(firstList) << endl;
  cout << "Time for Sum2: " << start.elapsed() << endl;

  start.reset();
  cout << "Max Sum 4: " << maxSubSum4(firstList) << endl;
  cout << "Time for Sum4: " << start.elapsed() << endl;


  //========Second Test===============================
  cout << "====================Second Test====================" << endl;
  int secondTest = pow(2,8);

  vector<int> secondList = makeList(secondTest);

  start.reset();
  cout << "Max Sum 1: " << maxSubSum1(secondList) << endl;
  cout << "Time for Sum1: " << start.elapsed() << endl;

  start.reset();
  cout << "Max Sum 2: " << maxSubSum2(secondList) << endl;
  cout << "Time for Sum2: " << start.elapsed() << endl;

  start.reset();
  cout << "Max Sum 4: " << maxSubSum4(secondList) << endl;
  cout << "Time for Sum4: " << start.elapsed() << endl;

  
  //========third Test===============================
  cout << "====================Third Test====================" << endl;
  int thirdTest = pow(2,9);

  vector<int> thirdList = makeList(thirdTest);

  start.reset();
  cout << "Max Sum 1: " << maxSubSum1(thirdList) << endl;
  cout << "Time for Sum1: " << start.elapsed() << endl;

  start.reset();
  cout << "Max Sum 2: " << maxSubSum2(thirdList) << endl;
  cout << "Time for Sum2: " << start.elapsed() << endl;

  start.reset();
  cout << "Max Sum 4: " << maxSubSum4(thirdList) << endl;
  cout << "Time for Sum4: " << start.elapsed() << endl;

  //========fourth Test===============================
  cout << "====================Fourth Test====================" << endl;
  int fourthTest = pow(2,10);

  vector<int> fourthList = makeList(fourthTest);

  start.reset();
  cout << "Max Sum 1: " << maxSubSum1(fourthList) << endl;
  cout << "Time for Sum1: " << start.elapsed() << endl;

  start.reset();
  cout << "Max Sum 2: " << maxSubSum2(fourthList) << endl;
  cout << "Time for Sum2: " << start.elapsed() << endl;

  start.reset();
  cout << "Max Sum 4: " << maxSubSum4(fourthList) << endl;
  cout << "Time for Sum4: " << start.elapsed() << endl;

  //========fifth Test===============================
  cout << "====================Fifth Test=========================" << endl;
  int fifthTest = pow(2,11);

  vector<int> fifthList = makeList(fifthTest);

  start.reset();
  cout << "Max Sum 1: " << maxSubSum1(fifthList) << endl;
  cout << "Time for Sum1: " << start.elapsed() << endl;

  start.reset();
  cout << "Max Sum 2: " << maxSubSum2(fifthList) << endl;
  cout << "Time for Sum2: " << start.elapsed() << endl;

  start.reset();
  cout << "Max Sum 4: " << maxSubSum4(fifthList) << endl;
  cout << "Time for Sum4: " << start.elapsed() << endl;

  //========sixth Test===============================
  cout << "=================Sixth Test====================" << endl;
  int sixthTest = pow(2,12);

  vector<int> sixthList = makeList(sixthTest);

  start.reset();
  cout << "Max Sum 1: " << maxSubSum1(sixthList) << endl;
  cout << "Time for Sum1: " << start.elapsed() << endl;

  start.reset();
  cout << "Max Sum 2: " << maxSubSum2(sixthList) << endl;
  cout << "Time for Sum2: " << start.elapsed() << endl;

  start.reset();
  cout << "Max Sum 4: " << maxSubSum4(sixthList) << endl;
  cout << "Time for Sum4: " << start.elapsed() << endl;


  //CPU Speed
  cout <<"CPU SPEED: " << CLOCKS_PER_SEC << endl;


}

void function2b(int n){
  int sum = 0;
  for (int i = 0; i < n; i++) ++sum;
}

void function2c(int n){
  int sum = 0;
  for (int i = 0; i < n; i++) 
    for (int j = 0; j < n; ++j) 
      ++sum;
}

void function2d(int n){
  int sum = 0;
  for (int i = 0; i < n; i++) 
    for (int j = 0; j < i; ++j) 
      ++sum;

}

void function2e(int n){
  int sum = 0;
  for (int i = 0; i < n; i++) 
    for (int j = 0; j < n; ++j) 
      for(int k = 0; k < n; ++k)
	++sum;

}

//2b - 2e
void question2(){
  //==========Timer Settings========================
  timer start;
  cout.setf( ios::fixed, ios::floatfield );
  cout.precision( 6 );

  //==============First Test=======================
  cout << "==============First Test=======================\n";
  int firstTest = pow(2, 8);
  cout << "Testing " << firstTest << endl;

  //2b
  start.reset();
  function2b(firstTest);
  cout << "Time for 2b: " << start.elapsed() << endl;

  //2c
  start.reset();
  function2c(firstTest);
  cout << "Time for 2c: " << start.elapsed() << endl;

  //2d
  start.reset();
  function2d(firstTest);
  cout << "Time for 2d: " << start.elapsed() << endl;

  //2e
  start.reset();
  function2e(firstTest);
  cout << "Time for 2e: " << start.elapsed() << endl;
  
  //==============Second Test=======================
  cout << "==============Second Test=======================\n";
  int secondTest = pow(2, 9);
  cout << "Testing " << secondTest << endl;

  //2b
  start.reset();
  function2b(secondTest);
  cout << "Time for 2b: " << start.elapsed() << endl;

  //2c
  start.reset();
  function2c(secondTest);
  cout << "Time for 2c: " << start.elapsed() << endl;

  //2d
  start.reset();
  function2d(secondTest);
  cout << "Time for 2d: " << start.elapsed() << endl;

  //2e
  start.reset();
  function2e(secondTest);
  cout << "Time for 2e: " << start.elapsed() << endl;

  //==============Third Test=======================
  cout << "==============Third Test=======================\n";
  int thirdTest = pow(2, 10);
  cout << "Testing " << thirdTest << endl;

  //2b
  start.reset();
  function2b(thirdTest);
  cout << "Time for 2b: " << start.elapsed() << endl;

  //2c
  start.reset();
  function2c(thirdTest);
  cout << "Time for 2c: " << start.elapsed() << endl;

  //2d
  start.reset();
  function2d(thirdTest);
  cout << "Time for 2d: " << start.elapsed() << endl;

  //2e
  start.reset();
  function2e(thirdTest);
  cout << "Time for 2e: " << start.elapsed() << endl;

  //==============Fourth Test=======================
  cout << "==============Fourth Test=======================\n";
  int fourthTest = pow(2, 11);
  cout << "Testing " << fourthTest << endl;

  //2b
  start.reset();
  function2b(fourthTest);
  cout << "Time for 2b: " << start.elapsed() << endl;

  //2c
  start.reset();
  function2c(fourthTest);
  cout << "Time for 2c: " << start.elapsed() << endl;

  //2d
  start.reset();
  function2d(fourthTest);
  cout << "Time for 2d: " << start.elapsed() << endl;

  //2e
  start.reset();
  function2e(fourthTest);
  cout << "Time for 2e: " << start.elapsed() << endl;

  //==============Fifth Test=======================
  cout << "==============Fifth Test=======================\n";
  int fifthTest = pow(2, 12);
  cout << "Testing " << fifthTest << endl;

  //2b
  start.reset();
  function2b(fifthTest);
  cout << "Time for 2b: " << start.elapsed() << endl;

  //2c
  start.reset();
  function2c(fifthTest);
  cout << "Time for 2c: " << start.elapsed() << endl;

  //2d
  start.reset();
  function2d(fifthTest);
  cout << "Time for 2d: " << start.elapsed() << endl;

  //2e
  start.reset();
  function2e(fifthTest);
  cout << "Time for 2e: " << start.elapsed() << endl;

}


int main(){
  cout << "======================================Question 1=================================================" << endl;
  question1();

  cout << "======================================Question 2=================================================" << endl;
  question2();

  //==========2a==============
}
