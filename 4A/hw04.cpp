/*
  Simon Chen
  sc4900
  N10013388
  Homework 4A
  The purpose of this code is to understand the vector class and the explroe the STL algorithms and functors.

*/

#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

template <typename Object>
class Vector
{
public:
  // explicit 
  Vector( int initSize = 0 )
    : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }
  { objects = new Object[ theCapacity ]; }
    
  Vector( const Vector & rhs )
    : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
  {
    objects = new Object[ theCapacity ];
    for( int k = 0; k < theSize; ++k )
      objects[ k ] = rhs.objects[ k ];
  }
    
  Vector & operator= ( const Vector & rhs )
  {
    Vector copy = rhs;
    std::swap( *this, copy );
    return *this;
  }
    
  ~Vector( )
  { delete [ ] objects; }
    
  Vector( Vector && rhs )
    : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
  {
    rhs.objects = nullptr;
    rhs.theSize = 0;
    rhs.theCapacity = 0;
  }
    
  Vector & operator= ( Vector && rhs )
  {
    std::swap( theSize, rhs.theSize );
    std::swap( theCapacity, rhs.theCapacity );
    std::swap( objects, rhs.objects );
        
    return *this;
  }
    
  bool empty( ) const
  { return size( ) == 0; }
  int size( ) const
  { return theSize; }
  int capacity( ) const
  { return theCapacity; }

  Object & operator[]( int index )
  {
    return objects[ index ];
  }
    
  const Object & operator[]( int index ) const
  {
    return objects[ index ];
  }
    
  void resize( int newSize )
  {
    if( newSize > theCapacity )
      reserve( newSize * 2 );
    theSize = newSize;
  }
    
  void reserve( int newCapacity )
  {
    if( newCapacity < theSize )
      return;
        
    Object *newArray = new Object[ newCapacity ];
    for( int k = 0; k < theSize; ++k )
      newArray[ k ] = std::move( objects[ k ] );
        
    theCapacity = newCapacity;
    std::swap( objects, newArray );
    delete [ ] newArray;
  }
    
  // Stacky stuff
  void push_back( const Object & x )
  {
    if( theSize == theCapacity )
      reserve( 2 * theCapacity + 1 );
    objects[ theSize++ ] = x;
  }
  // Stacky stuff
  void push_back( Object && x )
  {
    if( theSize == theCapacity )
      reserve( 2 * theCapacity + 1 );
    objects[ theSize++ ] = std::move( x );
  }

    
  // Iterator stuff: not bounds checked
  typedef Object * iterator;
  typedef const Object * const_iterator;
    
  iterator begin( )
  { return &objects[ 0 ]; }
  const_iterator begin( ) const
  { return &objects[ 0 ]; }
  iterator end( )
  { return &objects[ size( ) ]; }
  const_iterator end( ) const
  { return &objects[ size( ) ]; }
    
  static const int SPARE_CAPACITY = 2;

  iterator erase( iterator vItr) {
    iterator last = end();
    iterator loop = vItr;
    iterator setloop = vItr;
    while (++loop != last){
      *setloop++ = *loop;
    }
    theSize--;
    return vItr;

  }

    
private:
  int theSize;
  int theCapacity;
  Object * objects;
};


int sumDigits(int x){
  if (x < 0) x *= -1;
  if (x < 10) return x;
  return x%10 +   sumDigits(x/10);
}

int getSumVector(const vector<int> & a, int begin, int end){
  if (begin == end) 
    return a[begin];

  int mid = (begin + end)/2;
  return getSumVector(a,begin,mid) + getSumVector(a,mid+1,end);


 
}

int sumVector( const vector<int> & a){
  return a.size() > 0 ? getSumVector(a,0,a.size()-1) : 0;
}


int main(){
  // cout << sumDigits(-159);
  vector<int> test= {-21,31,14,1,-20};
  vector<int> test2;

  // cout << sumVector(test);

  vector<int> A {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  vector<int> B {1, 2, 1, 2, 1, 2};
  vector<int> C{1, 2, 3, 1, 2, 3};
  vector<int> D(6);
  vector<int> E(10);

  copy(A.begin(), A.begin()+6, D.begin());

  vector<int>::iterator vecItr;
  vecItr = find(A.begin(), A.end(), 5);
  // returns an iterator to 5 in vector A
  if (vecItr != A.end( ))
    cout << *vecItr;
  // prints out the value pointed to by vecItr


  // sort(A.begin(), A.end(), greater<int>());

  A.push_back(10);

  std::pair<std::vector<int>::iterator,int*> mypair;

  cout << *(mismatch(A.begin(), A.end(), C.begin(), equal_to<int>())).first;
  // cout << mItr.first;
}
