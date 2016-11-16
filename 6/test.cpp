#include <vector>
#include <list>
#include <string>
#include <iostream>

using namespace std;


int main(){
  vector<int> A = {1,2,3,4,5};
  vector<int> B;
  vector<int>::iterator vItr;
  list<int> C = {1, 2,3,4,5};
  list<int> D;
  list<int>::iterator lItr;

  B = A;
  vItr = B.begin();
  B.erase(B.begin()+1);
}
