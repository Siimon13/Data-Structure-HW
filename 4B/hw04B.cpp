/*
  Simon Chen
  N10013388
  sc4900
  Homework 4B

  The purpose of this program is to test our knowledge of runtime and using differet collections and to parse a text file for data
*/

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <list>
#include <set>
#include <algorithm>
#include <unordered_set>


using namespace std;

class trainStopData {
public:

  trainStopData(const string& stop_id,const string& stop_name, const double stop_lat, const double stop_lon):stop_id(stop_id), stop_name(stop_name), stop_lat(stop_lat), stop_lon(stop_lon) {}


  string get_id( ) const { return stop_id;}
  string get_stop_name( ) const {return stop_name;}
  double get_latitude( ) const {return stop_lat;}
  double get_longitude( ) const {return stop_lon;}

private:
  string stop_id;    // id of train stop (1st token)
  string stop_name;  // name of station (4th token)
  double stop_lat;   // latitude of train stop location
  double stop_lon;   // longitude of train stop location
};

void parseTrainData(vector<trainStopData>& vecData) { 
  //insert code here
  ifstream mtaDataStream("MTA_train_stop_data.txt");
  
  if(!mtaDataStream){
    cerr << "Couldn't open the names file.\n";
  }

  string line;
  getline(mtaDataStream,line);

  while(getline(mtaDataStream,line)){
    stringstream ss;
    ss.str(line);
    string element;
    vector<string> elements;

    while(getline(ss,element,',')){
      elements.push_back(element);
    }
    
    string stop_id = elements[0];
    string stop_name = elements[2];
    double stop_lat = atof(elements[4].c_str());
    double stop_lon = atof(elements[5].c_str());
    vecData.push_back(trainStopData(stop_id,stop_name,stop_lat,stop_lon));
  }

}

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

int main(){
  vector<trainStopData> vecData;
  parseTrainData(vecData); 

  // vector<string> test = {1,235,4356,2113,1,2,34,5,2};
  vector<string> test;
  
  cout << "Testing dup List\n";
  dupTestList(test);

  cout << "Testing dup Sort\n";
  dupTestSort(test);

  cout << "Testing dup Set\n";
  dupTestSet(test);

  cout << "Testing dup UnOrdSet\n";
  dupTestUnorderedSet(test);
}
