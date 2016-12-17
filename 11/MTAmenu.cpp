/*
  Simon Chen
  N10013388
  sc4900
  Homework 11
*/


#include<iostream>
#include<vector>
#include<queue>
#include <string>
#include <list>
#include <stack>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
// #include "shortestpaths.cpp"

using namespace std;

const int DEFAULT_VAL =  -1;      // must be less than 0
const string DEFAULT_STRVAL =  "";      // must be less an empty string

struct vertexInf                    // Stores information for a vertex
{                                   
  int dist;  // distance to vertex from the source
  string prev;  // previous node in BFS tree
};

struct hist 
{
  int transfer;
  string route;

};

unordered_map<string,hist> localdb;

class MTA {

public:
  
  MTA(){
    createMTAGraph();
  }

  bool checkPath(string& stop_id){
    return mtaGraph.find(stop_id) != mtaGraph.end();
  }

  pair<int,string> getPath(const string& from_stop_id, const string& to_stop_id){

    // int s = 0;
    // Graph g;
    queue<string> q;             // q is the queue of vertex numbers

	
    unordered_map <string, vertexInf > mtaRoute;  // stores BFS info for the vertices
    // info for vertex j is in position j

  
    for (pair<string, list<string> > j : mtaGraph)                 // Initialize distances and prev values
      { mtaRoute[j.first].dist = DEFAULT_VAL; 
	mtaRoute[j.first].prev = DEFAULT_STRVAL; 
      }   
  
    mtaRoute[from_stop_id].dist = 0;
	
    q.push(from_stop_id);
    string visit_stop;
    string adj_stop;

    while  (!q.empty() )
      {
	visit_stop = q.front();
	// cout << stop << endl;
	q.pop();

	// list<string> asd = mtaGraph[stop];
	list<string>::iterator itr = mtaGraph[visit_stop].begin();
	list<string>::iterator enditr = mtaGraph[visit_stop].end();

	while(itr != enditr){
	  adj_stop = *itr++;
	
	  if (mtaRoute[adj_stop].dist == DEFAULT_VAL){
	    mtaRoute[adj_stop].dist = mtaRoute[visit_stop].dist + 1;
	    mtaRoute[adj_stop].prev = visit_stop;
	    q.push(adj_stop);
	  }

	}

      
	if (visit_stop == to_stop_id) break;

      } 


    int distance = mtaRoute[to_stop_id].dist;
    stack<string> path;
    string route;
    string prev_stop = to_stop_id;
    path.push(to_stop_id);
  
    cout << "Number of Transfers: " <<  distance << endl;

    for (int i = 0; i < distance ; ++i){
      prev_stop = mtaRoute[prev_stop].prev;
      path.push(prev_stop);
    }

    while(!path.empty()){
      
      if (path.size() == 1){
	route += path.top();
      }
      else
	route += path.top() + " -> ";
      path.pop();
    }
    cout << "Route: \n";    
    cout << route << endl;

    return pair<int,string>(distance, route);

  }

private:
  unordered_map <string, list<string> > mtaGraph;

  void getTransferData(){
    ifstream mtaTransferStream("transfers.txt");

    if(!mtaTransferStream){
      cerr << "Couldn't open the transfer file.\n";
    }

    string line;
    getline(mtaTransferStream,line);

    while(getline(mtaTransferStream,line)){
      stringstream ss;
      ss.str(line);
      string element;
      vector<string> elements;

      while(getline(ss,element,',')){
	elements.push_back(element);
      }
      string from_stop_id = elements[0];
      string to_stop_id = elements[1];

      // cout << from_stop_id << to_stop_id << endl;
      if (mtaGraph.find(from_stop_id) == mtaGraph.end()){
	if (from_stop_id != to_stop_id)
	  mtaGraph.insert({from_stop_id, {to_stop_id}});
	else
	  mtaGraph.insert({from_stop_id, {}});
      }
      else{
     
	if (from_stop_id != to_stop_id && 
	    find(mtaGraph[from_stop_id].begin(), 
		 mtaGraph[from_stop_id].end(), 
		 to_stop_id) == mtaGraph[from_stop_id].end())
	  mtaGraph[from_stop_id].push_back(to_stop_id);
      }

    }

    mtaTransferStream.close();

  }

  void createMTAGraph(){
    ifstream mtaDataStream("MTA_train_stop_data.txt");
  
    if(!mtaDataStream){
      cerr << "Couldn't open the mta file.\n";
    }
 
    string line;
    string prevstop = " ";
    getline(mtaDataStream,line);
 
    while(getline(mtaDataStream,line)){
      stringstream ss;
      ss.str(line);
      string element;
      vector<string> elements;

      while(getline(ss,element,',')){
	elements.push_back(element);
      }
      string stop_id = elements[0].substr(0,3); 

      // cout << stop_id << endl;
      if (mtaGraph.find(stop_id) == mtaGraph.end()){
	if (prevstop[0] == stop_id[0] && prevstop != stop_id){
	  mtaGraph.insert({stop_id, {prevstop}});
	  mtaGraph[prevstop].push_back(stop_id);
	}
	else
	  mtaGraph.insert({stop_id, {}});
      }
      prevstop = stop_id;
    }
    mtaDataStream.close();
    getTransferData();
  }


};

void clear(){
  system("clear");
}

int main(){
  
  MTA mta;
  string name;
  string input;
  string message;
  string from_stop_id;
  string to_stop_id;
  pair<int,string> savedata;
  hist data;

  clear();
  cout << "Hi! Welcome to Simon's MTA Planner. Serving the CS2314 since December 2016\n \n";
  
  cout << "Can I get your name? \n";
  
  cin >> name;
  message =  "  Welcome " + name ;

  //    cout << "                                                           " ;
  while (true){
    clear();
    cout << "                             ========== Menu ==========\n" ;

    cout << "                                 "<< message << endl << endl;

    cout << "                             Enter the full/short command\n\n  " ;
    cout << "                                     -Travel(T)\n";
    cout << "                                       -History(H)\n";
    cout << "                                       -Quit(Q)\n";
    
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout<< "================================================================================\n";


    cin >> input;

    if (input == "T" || input == "Travel"){
      clear();
      cout << "From: ";

      cin >> from_stop_id;

      if(!mta.checkPath(from_stop_id)){
	message = "Unable to find " + from_stop_id;
	continue;
      }

      cout << "To: ";

      cin >> to_stop_id;

      if(!mta.checkPath(to_stop_id)){
	message = "Unable to find " + to_stop_id;
	continue;
      }
      
      system("sl");
      clear();
      savedata = mta.getPath(from_stop_id, to_stop_id);
      

      cout << "\n\nWould you like to save this path? (Y/N)\n";

      cin >> input;

      if (input == "Y"){
	clear();
	cout << "Enter a save name: ";
	
	cin >> input;
	data.transfer = savedata.first;
	data.route = savedata.second;

	localdb[input] = data;
	
      } 

      message = "";
    }
    else if (input == "H" || input == "History"){
      clear();
      for (pair<string, hist> d : localdb){
	string dname = d.first;
	hist dhist = d.second;

	cout << d.first << " | Transfers: " << dhist.transfer << endl;
	cout << "Route: \n" << dhist.route << endl;

      }
      cout<< "\n================================================================================\n";
      cout << "\n\nPress enter to continue... ";

      cin >> input;
      message = "";
    }
    else if (input == "Q" || input == "Quit") break;
    else {
      message = "Unknown command";
    }

    // system("sl");
    // mta.getPath("111", "112");
    // break;
  }
  clear();
  cout << "Thank you " << name << "" << endl;

}
