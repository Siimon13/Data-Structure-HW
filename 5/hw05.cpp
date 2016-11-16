/*
  Simon Chen
  N10013388
  sc4900
  Homework 5

  The purpose of this program is to test our knowledge of the linked list class, recursion, parsing files.
*/

#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <math.h>
#include <functional>

using namespace std;

//========================================Helper Func================
double degrad(double d) {
return d * M_PI / 180;
}


// Code below is adapted from http://www.movable-type.co.uk/scripts/latlong.html
// FYI: That website has an applet that computes the haversine distance. 
// It also has a link that will show the locations on a map,
// with a line between them.
double haverdist(double lat1, double longit1, double lat2, double longit2)
{
  double r = 6371;
  double dlat = degrad(lat2 - lat1);
  double dlongit = degrad(longit2 - longit1);
  double a = sin(dlat/2)*sin(dlat/2)+
    cos(degrad(lat1))*cos(degrad(lat2))*sin(dlongit/2)*sin(dlongit/2);
  double c = 2*atan2(sqrt(a),sqrt(1-a));
  return r*c;
}
//====================================================================


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


bool checkStop_idDup(const vector<trainStopData>& vecData,const string& stop_id){
  for(size_t i = 0; i < vecData.size() ; ++i){
    size_t n = stop_id.find(vecData[i].get_id());
    if(n != string::npos){
      return false;
    }
  }
  return true;
}

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
    if (checkStop_idDup(vecData, stop_id)){
      vecData.push_back(trainStopData(stop_id,stop_name,stop_lat,stop_lon));
    }
  }

}

class isStopOnRoute{
public:
  isStopOnRoute(char route) : route(route){}

  bool operator()(const trainStopData& data){
    return data.get_id().at(0) == route;
  }

private:
  char route;
};

class isSubwayStop{
public:
  isSubwayStop(const string& stopid) : stopid(stopid){}

  bool operator()(const trainStopData& data){
    return data.get_id() == stopid;
  }

private:
  string stopid;
};


class isSubwayStopNearX{
public:
  isSubwayStopNearX(double d, double latitude, double longitude) :  d(d), latitude(latitude), longitude(longitude){}

  bool operator()(const trainStopData& data){
    return haverdist(data.get_latitude(),data.get_longitude(), latitude, longitude) <= d;
  }

private:
  double d;
  double latitude;
  double longitude;

};


class printTrainStopInfo{
public:
  void operator()(const trainStopData& data){
    cout << "Stop ID: " << data.get_id() << endl;
    cout << "Stop Name: " << data.get_stop_name() << endl;
    cout << "Stop Latitude: " << data.get_latitude() << endl;
    cout << "Stop Longitude: " << data.get_longitude() << endl;
    cout << endl;
  }

};

template<typename Itr, typename Functr1, typename Functr2>
int perform_if(Itr itrStart, Itr itrEnd, Functr1 pred,Functr2 op){
  Itr itr = itrStart;
  int how_many = 0;
  while(itr != itrEnd){
    if(pred(*itr)){
      op(*itr);
      ++how_many;
    }
    ++itr;
  }
  return how_many;
}

void menu(vector<trainStopData>& vecData){
  vector<trainStopData>::iterator begin = vecData.begin();
  vector<trainStopData>::iterator end = vecData.end();

  printTrainStopInfo printData;

  while(true){
    cout << "=====Train Menu=====\nEnter choice number\n";
    cout << "Print All Stops on Route : 1\n";
    cout << "Print Info on Specific TrainStop : 2\n";
    cout << "Print All Stops Within Dist of Lat/Lng : 3\n";
    cout << "Quit : 4\n";
    cout << "====================\n";
    string choice;
    cin >> choice;

    if (choice == "1"){
      cout << "Enter the Route:\n";
      char route;
      cin >> route;

      isStopOnRoute pred(route);

      if (perform_if(begin, end, pred , printData) == 0){
	cout << "Invalid Info\n";
      }
    }
    else if (choice == "2"){
      cout << "Enter the StopId:\n";
      string stopid;
      cin >> stopid;

      isSubwayStop pred(stopid);

      if (perform_if(begin, end, pred , printData) == 0){
	cout << "Invalid Info\n";
      }
    }
    else if (choice == "3"){
      cout << "Enter the Lat:\n";
      double lat;
      cin >> lat;

      cout << "Enter the Lng:\n";
      double lng;
      cin >> lng;

      cout << "Enter the Dist:\n";
      double dist;
      cin >> dist;
      
      isSubwayStopNearX pred(dist, lat, lng);

      if (perform_if(begin, end, pred , printData) == 0){
	cout << "Invalid Info\n";
      }
    }
    else if (choice == "4"){
      cout << "Have a Nice Day\n";
      break;
    }
    else
      cout << "Invalid Choice\n";
  }
}

template<class Comparable>
void printVec(vector<Comparable> & a);

template <class RandItr>
void mergeSort(RandItr tmp,RandItr start, RandItr end )
{
  if (start < end){
    RandItr cntr = start + (end-start)/2;

    mergeSort(tmp, start, cntr);
    mergeSort(tmp, cntr + 1, end);
    merge(start,cntr,cntr+1,end,tmp, start);
  }
}


template <class RandItr>
void mergeSort( RandItr start, RandItr end )
{
  int  sz = end - start;  // or use auto sz = end-start;
  typedef typename iterator_traits< RandItr >::value_type Object; //Xcode
  // typedef  iterator_traits< RandItr >::value_type Object; //Other compilers
  // Don't worry about this line of code
  vector<Object> tmp( sz );

  mergeSort( tmp.begin(), start, end );
    
}


class student{
private:
  string name;
  double gpa;
public:
  student(const string& name, double gpa):name(name), gpa(gpa){}
  string get_name() const {return name;}
  double get_gpa() const {return gpa;}
};

class meFirst{
public:

  meFirst(const string& me) : me(me){}

  bool operator()(const student& rhs, const student& lhs){
    if (rhs.get_name() == me && lhs.get_name() == me)
      return true;
      return rhs.get_name() < lhs.get_name();
    } 


  private:
    string me;
};

//Use merge Sort for Vector of Booleans, Any sorting function will work.


int main(){
  vector<trainStopData> vecData;
  parseTrainData(vecData); 

  //Train Menu

  menu(vecData);


  
}
