/*
  Simon Chen
  N10013388
  sc4900
  Homework 10

*/

#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;


template<typename HashedObj>
class HashTable
{
public:
enum EntryType { ACTIVE, EMPTY, DELETED };
private:
struct HashEntry {
HashedObj element;
EntryType info;
HashEntry( const HashedObj & e = HashedObj(), EntryType i = EMPTY )
  : element( e ), info( i ) {}
  };
public:
typedef typename vector<HashEntry>::const_iterator iterator;
explicit HashTable(int size = 101):currentSize(0) {
array.resize(size);
}

iterator find( const HashedObj & );
bool remove( const HashedObj & );
void makeEmpty();
bool insert( const HashedObj & );
iterator end() const;
int capacity() const;

private:
std::hash<HashedObj> hf;

vector<HashEntry> array;
int currentSize;
void rehash();
};

template< typename HashedObj >
bool HashTable<HashedObj>::insert( const HashedObj & x ) {

  float loadfactor = (currentSize + 0.1)/array.size();
  
  if (loadfactor >= 0.5)
    rehash();

  int index = hf(x) % array.size();

  for( int i = index; i < array.size(); ++i ) {

    if(array[i].element == x && array[i].info == ACTIVE) break;

    if (array[i].info != ACTIVE){
      array[i].info = ACTIVE;
      array[i].element = x;
      ++currentSize;
      return true;
    }
    

  }

  return false;
}

template< class HashedObj >
typename HashTable<HashedObj>::iterator HashTable<HashedObj>::find( const HashedObj & x ) {
  int index = hf(x) % array.size();

  for( typename vector<HashEntry>::iterator i = array.begin() + index; 
       i != array.end(); ++i ) {
      if(i->element == x && i->info == ACTIVE)
	return i;
    }

    return array.end();
  }

  template< typename HashedObj >
    bool HashTable<HashedObj>::remove( const HashedObj & x ) {
    int index =  hf(x) % array.size() ;
    for( int i = index; i < array.size(); ++i ) {
      if ( array[i].info == EMPTY )
	return false;
      if ( array[i].info == ACTIVE && array[i].element == x ) {
	array[i].info = DELETED;
	--currentSize;
	return true;
      }
    }
    for( int i = 0; i < index; ++i ) {
      if ( array[i].info == EMPTY )
	return false;
      if ( array[i].info == ACTIVE && array[i].element == x ) {
	array[i].info = DELETED;
	--currentSize;
	return true;
      }
    }
    /**
     * There's a clever but convoluted way to merge the above two loops into one
     * if you would like to give it a shot.
     */
    return false;
  }

  template< typename HashedObj >
    void HashTable<HashedObj>::rehash() {
    array.resize(array.size()*2 +1);
    return;
  }

  template< typename HashedObj >
    void HashTable<HashedObj>::makeEmpty() {
    for( auto i : array )
      i.info = EMPTY;
  }

  template<typename HashedObj>
    typename HashTable<HashedObj>::iterator HashTable<HashedObj>::end() const {
    return array.end();
  }

  template<typename HashedObj>
    int HashTable<HashedObj>::capacity() const {
    return array.size();
  }

void getTransferData(unordered_map <string, list<string> >& mtaGraph);

void createMTAGraph(unordered_map <string, list<string> >& mtaGraph){
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
  getTransferData(mtaGraph);
}

void getTransferData(unordered_map <string, list<string> >& mtaGraph){
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

int main(){
  unordered_map <string, list<string> > mtaGraph;

  createMTAGraph(mtaGraph);
  
  unordered_map < string, list<string>> ::iterator adjListItr = mtaGraph.find("125");

  vector<string> adjVec;
  
  for (list<string>::iterator litr = adjListItr->second.begin(); litr != adjListItr->second.end(); litr++) {
    adjVec.push_back(*litr);
  }

  for (int i = 0; i < adjVec.size(); i++) {
    cout << adjVec[i] << endl;
  }

  
  // HashTable<int> hst;

  // int capacity = hst.capacity();

  // for( int i = 0; i < 100; ++i ){
  //   // cout << "Inserting: " << i*capacity << endl;
  //   hst.insert(i); 
 
  // }

}
