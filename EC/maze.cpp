/*
  Simon Chen
  sc4900
  N10013388
  Maze Extra Credit
*/

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <queue>

using namespace std;


class Maze{

private:
  vector<vector<char> > maze;
  stack<pair<int, int> > solutionPath;
  pair<int,int> start;

  void clearMaze(){
    for (vector<char>& i : maze)
      i.clear();
    maze.clear();
  }

  void restartMaze(){
    for (size_t i = 0; i < maze.size(); ++i)
      for (size_t j = 0; j < maze[i].size(); ++j)
	if (maze[i][j] == '-')
	  maze[i][j] = 'x';

  }


  bool findEndRec( pair<int,int> curr){
    int curri = curr.first;
    int currj = curr.second;

    if(curri < 0 || curri >= maze.size() ||
       currj < 0 || currj >= maze[curri].size() ){
      // cout<< "failed" << endl;
      clearPath();
      return false;
    } 

    if(maze[curri][currj] == 'e'){
      printMaze();
      restartMaze();
      cout << endl << "Goal found at: " << curri << ' ' << currj << endl;
      return true;
    }

    maze[curri][currj] = '-';

    pair<int,int> moveLeft(curri,currj-1);

    pair<int,int> moveRight(curri,currj+1);

    pair<int,int> moveUp(curri-1,currj);

    pair<int,int> moveDown(curri+1,currj);

    // printMaze();
    // cin.get();

    // cout<< "Testing Left" << endl;
    if (currj != 0 && maze[curri][currj-1] != '.' && 
	maze[curri][currj-1] != '-' && findEndRec(moveLeft)){
      solutionPath.push(moveLeft);
      return true;
    }

    // cout<< "Testing Right" << endl;
    if (currj < maze[curri].size() && maze[curri][currj+1] != '.' && 
	maze[curri][currj+1] != '-' &&findEndRec( moveRight)){
      solutionPath.push(moveRight);
      return true;
    }

    // cout<< "Testing Up" << endl;
    if (curri != 0 && maze[curri-1][currj] != '.' && 
	maze[curri-1][currj] != '-' &&findEndRec( moveUp)){
      solutionPath.push(moveUp);
      return true;
    }

    // cout<< "Testing Down" << endl;
    if (curri < maze.size() && maze[curri+1][currj] != '.' && 
	maze[curri + 1][currj] != '-' &&findEndRec( moveDown)){
      solutionPath.push(moveDown);
      return true;
    }
  
    return false;
  }


public:
  
  void printPath(){
    while(!solutionPath.empty()){
      cout << solutionPath.top().first << "," << solutionPath.top().second << endl;
      solutionPath.pop();
    }
  }

  void clearPath() {
    while(!solutionPath.empty()){
      solutionPath.pop();
    }
  }

  
  void readMaze(string name){
    ifstream fs;
    fs.open(name);
    
    clearMaze();

    vector<char> mazeline;
    string line;
  
    while(getline(fs,line)){

      for (char c : line){
	mazeline.push_back(c);
      }

      maze.push_back(mazeline);
      mazeline.clear();
    }
    
    findStart();
  }

  void findStart(){

    for (size_t i = 0; i < maze.size(); ++i)
      for (size_t j = 0; j < maze[i].size(); ++j){
	  if (maze[i][j] == 's'){
	    start = make_pair(i,j);
	    return;
	  }
	}
    }


    void printMaze() const{
      for (size_t i = 0; i < maze.size(); ++i){
	for (size_t j = 0; j < maze[i].size(); ++j)
	  cout << maze[i][j];
	cout << endl;
      }
  
    }

    bool findEndRec(){
      clearPath();
      return findEndRec(start);
    }


  void findEndStack(){
    clearPath();
    stack<pair<int,int> > route;
    int curri = start.first;
    int currj = start.second;

    pair<int,int> moveLeft(curri,currj-1);

    pair<int,int> moveRight(curri,currj+1);

    pair<int,int> moveUp(curri-1,currj);

    pair<int,int> moveDown(curri+1,currj);

    route.push(moveLeft);
    route.push(moveRight);
    route.push(moveUp);
    route.push(moveDown);  

    while(!route.empty()){

      pair<int,int> path = route.top();
      route.pop();

      solutionPath.push(path);

      curri = path.first;
      currj = path.second;

      if(curri < 0 || curri >= maze.size() -1 ||
	 currj < 0 || currj >= maze[curri].size() - 1 ){
	clearPath();
	continue;
      } 

      if(maze[curri][currj] == 'e'){
	printMaze();
	cout << endl << "Goal found at: " << curri << ' ' << currj << endl;
	restartMaze();
	return;
      }

      maze[curri][currj] = '-';


      // printMaze();
      // cin.get();

      if (currj != 0 && maze[curri][currj-1] != '.' && 
	  maze[curri][currj-1] != '-'){
	route.push(pair<int,int> (curri,currj-1));

      }

      if (currj < maze[curri].size() && maze[curri][currj+1] != '.' && 
	  maze[curri][currj+1] != '-'){
	route.push(pair<int,int> (curri,currj+1));

      }

      if (curri != 0 && maze[curri-1][currj] != '.' && 
	  maze[curri-1][currj] != '-'){
	route.push(pair<int,int> (curri-1,currj));

      }
    
      if (curri < maze.size() && maze[curri+1][currj] != '.' && 
	  maze[curri + 1][currj] != '-' ){
	route.push(pair<int,int> (curri+1,currj));

      }


    }

  }

  void findEndQueue(){
    clearPath();
    queue<pair<int,int> > route;
    int curri = start.first;
    int currj = start.second;

    pair<int,int> moveLeft(curri,currj-1);

    pair<int,int> moveRight(curri,currj+1);

    pair<int,int> moveUp(curri-1,currj);

    pair<int,int> moveDown(curri+1,currj);

    route.push(moveLeft);
    route.push(moveRight);
    route.push(moveUp);
    route.push(moveDown);  

    while(!route.empty()){

      pair<int,int> path = route.front();
      route.pop();
    
      solutionPath.push(path);

      curri = path.first;
      currj = path.second;

      if(curri < 0 || curri >= maze.size() -1 ||
	 currj < 0 || currj >= maze[curri].size() - 1 ){
	clearPath();
	continue;
      } 

      if(maze[curri][currj] == 'e'){
	printMaze();
	cout << endl << "Goal found at: " << curri << ' ' << currj << endl;
	restartMaze();
	return;
      }

      maze[curri][currj] = '-';


      // printMaze();
      // cin.get();

      if (currj != 0 && maze[curri][currj-1] != '.' && 
	  maze[curri][currj-1] != '-'){
	route.push(pair<int,int> (curri,currj-1));

      }

      if (currj < maze[curri].size() && maze[curri][currj+1] != '.' && 
	  maze[curri][currj+1] != '-'){
	route.push(pair<int,int> (curri,currj+1));

      }
      if (curri != 0 && maze[curri-1][currj] != '.' && 
	  maze[curri-1][currj] != '-'){
	route.push(pair<int,int> (curri-1,currj));

      }
    
      if (curri < maze.size() && maze[curri+1][currj] != '.' && 
	  maze[curri + 1][currj] != '-' ){
	route.push(pair<int,int> (curri+1,currj));

      }

    }

  }

};

void mazeQ(){

  Maze maze;

  maze.readMaze("fmaze.txt");

  // maze.printMaze();
  //question 1
  maze.findEndRec();
  // maze.printPath();

  //question 2
  maze.findEndStack();
  // maze.printPath();

  //question 3
  maze.findEndQueue();
  // maze.printPath();

}


int main(){
  mazeQ();

}
