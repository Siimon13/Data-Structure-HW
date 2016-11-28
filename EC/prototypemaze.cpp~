#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <queue>

using namespace std;

void readMaze(vector< vector<char> > & maze){
  ifstream fs("fmaze.txt");
  vector<char> mazeline;
  string line;
  
  while(getline(fs,line)){

    for (char c : line){
      mazeline.push_back(c);
    }

    maze.push_back(mazeline);
    mazeline.clear();
  }

}

pair<int,int> findStart(vector< vector<char> >& maze){

  for (size_t i = 0; i < maze.size(); ++i)
    for (size_t j = 0; j < maze[i].size(); ++j)
      if (maze[i][j] == 's')
	return make_pair(i,j);
}


void printMaze(vector< vector<char> >& maze){
  for (size_t i = 0; i < maze.size(); ++i){
    for (size_t j = 0; j < maze[i].size(); ++j)
      cout << maze[i][j];
    cout << endl;
  }
  
}

bool findEndRec(pair<int,int> curr,vector< vector<char> >& maze){
  int curri = curr.first;
  int currj = curr.second;

  if(curri < 0 || curri >= maze.size() ||
     currj < 0 || currj >= maze[curri].size() ){
    // cout<< "failed" << endl;

    return false;
  } 

  if(maze[curri][currj] == 'e'){
    printMaze(maze);
    cout << endl << "Goal found at: " << curri << ' ' << currj << endl;
    return true;
  }

  maze[curri][currj] = '-';

  pair<int,int> moveLeft(curri,currj-1);

  pair<int,int> moveRight(curri,currj+1);

  pair<int,int> moveUp(curri-1,currj);

  pair<int,int> moveDown(curri+1,currj);

  // printMaze(maze);
  // cin.get();

  // cout<< "Testing Left" << endl;
  if (currj != 0 && maze[curri][currj-1] != '.' && 
      maze[curri][currj-1] != '-' && findEndRec( moveLeft, maze)){
    cout << "<";
    return true;
  }

  // cout<< "Testing Right" << endl;
  if (currj < maze[curri].size() && maze[curri][currj+1] != '.' && 
      maze[curri][currj+1] != '-' &&findEndRec( moveRight, maze)){
    cout << ">";
    return true;
  }

  // cout<< "Testing Up" << endl;
  if (curri != 0 && maze[curri-1][currj] != '.' && 
      maze[curri-1][currj] != '-' &&findEndRec( moveUp, maze)){
    cout << "^";
    return true;
  }

  // cout<< "Testing Down" << endl;
  if (curri < maze.size() && maze[curri+1][currj] != '.' && 
      maze[curri + 1][currj] != '-' &&findEndRec( moveDown, maze)){
    cout << "v";
    return true;
  }
  
  return false;
}

void findEndStack(pair<int,int> curr,vector< vector<char> >& maze){
  stack<pair<int,int> > route;
  int curri = curr.first;
  int currj = curr.second;

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
    
    curri = path.first;
    currj = path.second;

    cout << curri << endl;
    cout << maze.size()<<endl;

    if(curri < 0 || curri >= maze.size() -1 ||
       currj < 0 || currj >= maze[curri].size() - 1 ){
      continue;
    } 

    if(maze[curri][currj] == 'e'){
      printMaze(maze);
      cout << endl << "Goal found at: " << curri << ' ' << currj << endl;
      return;
    }

    maze[curri][currj] = '-';


    // printMaze(maze);
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

void findEndQueue(pair<int,int> curr,vector< vector<char> >& maze){
  queue<pair<int,int> > route;
  int curri = curr.first;
  int currj = curr.second;

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
    
    curri = path.first;
    currj = path.second;

    cout << curri << endl;
    cout << maze.size()<<endl;

    if(curri < 0 || curri >= maze.size() -1 ||
       currj < 0 || currj >= maze[curri].size() - 1 ){
      continue;
    } 

    if(maze[curri][currj] == 'e'){
      printMaze(maze);
      cout << endl << "Goal found at: " << curri << ' ' << currj << endl;
      return;
    }

    maze[curri][currj] = '-';


    // printMaze(maze);
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

  


void mazeQ(){

  vector<vector<char> > maze;
  readMaze(maze);
  pair<int,int> start = findStart(maze);

  //question 1
  // findEndRec(start,maze);

  //question 2
  // findEndStack(start,maze);

  //question 3
  findEndQueue(start,maze);

}


int main(){
  mazeQ();

}
