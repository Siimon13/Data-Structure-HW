#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

void stringToUpper(string &s)
{
  for(unsigned int l = 0; l < s.length(); l++)
    {
      s[l] = toupper(s[l]);
    }
}

// Get point values from the file and store them in the vector
void initValues (vector<int>& pointValues) {
  ifstream ifs("Letter_point_value.txt");
  if (!ifs) cerr << "Failure to open file" << endl;

  char letter;
  int pt;


  vector<int> ptVal(26);
  
  map<char, int> ptdict;

  while (ifs >> pt >> letter) {
    
    int ind = letter - 'A';
    ptVal[ind] = pt;

  }

  pointValues = ptVal;

}
/*
  Simon Chen
  N10013388
  sc4900


*/

// Compute point value of a word
int wordValue (const vector<int>& pointValues, const string& word) {
  int points = 0;
  
  string uWord = word;
  stringToUpper(uWord);

  for(const char& c : uWord) {
    int ind = c-'A';
    points += pointValues[ind];
  }

  return points;

}

// Store all words and their point values in the map
void initWords (const vector<int>& pointValues, map<string, int>& wordValues) {

  ifstream efs("ENABLE.txt");
  if (!efs) cerr << "Failure to open file" << endl;

  string word;

  while(efs >> word){
    wordValues[word] = wordValue(pointValues,word);
  }

}


SCENARIO("Testing words with friends"){
  GIVEN("Given a map and vector"){
    vector<int> pointValues(26,0); 
    map<string, int> wordValues;
    WHEN("The map is initialized with this vector with word values"){
      initValues(pointValues);
      initWords(pointValues, wordValues);       
      THEN("abacterial should be valued 17"){
	string test = "abacterial";
	map<string, int>::iterator itr = wordValues.find(test);
	REQUIRE(itr->second == 17);
      }
      THEN("zyzzyva should be valued 42"){
	string test = "zyzzyva";
	map<string, int>::iterator itr = wordValues.find(test);
	REQUIRE(itr->second == 42);
      }
      THEN("fuzees should be valued 19"){
	string test = "fuzees";
	map<string, int>::iterator itr = wordValues.find(test);
	REQUIRE(itr->second == 19);
      }
      THEN("poly should be valued 10"){
	string test = "poly";
	map<string, int>::iterator itr = wordValues.find(test);
	REQUIRE(itr->second == 10);
      }
    }
  }
}

