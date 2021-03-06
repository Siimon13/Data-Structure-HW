/*
  Simon Chen
  N10013388
  Homework 2

  The goal of this function is to understand move constructor/assignment and functors.
*/


#include <iostream>
#include <string>

using namespace std;

//=================Question 1==========================

class IntArray{
public:
  IntArray(int n = 0): size(n), array(new int[n]){}
  // add your methods here
  
  //Copy Constructor

  // IntArray(const IntArray& rhs);
  IntArray(const IntArray& rhs){
    
    size = rhs.size;
    array = new int[size];

    for(int i =0; i < size; i++)
      array[i] = rhs.array[i]; 

  }

  //Move Constructor
  IntArray(IntArray && rhs): size(rhs.size) , array(rhs.array){
    rhs.array = nullptr;
    rhs.size = 0;
  }
  
  //Copy Assignment
  IntArray& operator= (const IntArray& rhs){
    if (this != &rhs){
      //Free up resources
      delete [] array;

      //Copy over resources
      size = rhs.size;
      array = new int[size];

      for(int i =0; i < size; i++)
	array[i] = rhs.array[i]; 
      
    }
    return *this;
  }

  //Move Assignment
  IntArray& operator=(IntArray&& rhs){
    int* tmparray = nullptr;
    int tmpsize = size;

    array = rhs.array;
    size = rhs.size;
    
    rhs.array = tmparray;
    rhs.size = tmpsize;

    return *this;
  }


  //Destructor
  ~IntArray(){
    delete[] array;
  }

  void put (int  i, int value);
  int get( int i);
  int* getArray();

private:
  int * array;
  int size; 
};

void IntArray::put(int i, int value){
  if(0 <= i && i < size){
  *(array + i) = value;
  }
  }

  int IntArray::get(int i){
  if(0 <= i && i < size){
  return *(array + i);
  }
  return 0;
  }

  int* IntArray::getArray(){
  return array;
  }




  //=================Question 2===================
  class isEven{

  public:
  bool operator()(int num) const{
  return num % 2 == 0;
  }

  };


  class strLen{

  public:
  bool operator()(const string& lhs, const string& rhs){
  return lhs.size() < rhs.size();
  }

  };

  int main(){
  isEven checkEven;

  int test1 = 1;
  cout << "Checking if " << test1<< " is Even: ";
  if (checkEven(test1))
    cout << "It's Even!\n";
  else 
    cout << "It's Odd!\n";

  int test2 = 2;
  cout << "Checking if " << test2<< " is Even: ";
  if (checkEven(test2))
    cout << "It's Even!\n";
  else 
    cout << "It's Odd!\n";

  string  str1 = "Hello";
  string str2 = "Helloasdf";
  strLen compareString;

  cout << "Comparing " << str1 << " and " << str2 << endl;

  if (compareString(str1,str2))
    cout << "String 1 is shorter\n";
  else 
    cout << "String 2 is shorter\n";
  }
