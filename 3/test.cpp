#include <vector>
#include <list>
#include <iostream>

using namespace std;

int main(){

  vector<int> a {1, 2, 3, 4, 5};
  vector<int>::iterator itra = a.begin();
  cout << *(itra + 3);

  list<int> b {1, 2, 3, 4, 5};
  list<int>::iterator itrb = b.begin();
  cout << *(++itrb);


  list<int> c {1, 2, 3, 4, 5};
  list<int>::iterator itrc = c.end();
  itrc--;
  cout << *(itrc);

  vector<int> d {1, 2, 3, 4, 5};
  vector<char>::iterator itrd = d.begin();
  cout << *(itrd + 3);
}
