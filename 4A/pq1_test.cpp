/*
  Simon Chen
  sc4900
  N10013388
  Homework 4A
  The purpose of this code is to understand the vector class and the explroe the STL algorithms and functors.

*/


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

template <typename Object>
class Vector
{
public:
  explicit Vector(int initSize = 0)
    : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }
  {
    objects = new Object[theCapacity];
  }

  Vector(const Vector & rhs)
    : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
  {
    objects = new Object[theCapacity];
    for (int k = 0; k < theSize; ++k)
      objects[k] = rhs.objects[k];
  }

  Vector & operator= (const Vector & rhs)
  {
    Vector copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  ~Vector()
  {
    delete[] objects;
  }

  Vector(Vector && rhs)
    : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
  {
    rhs.objects = nullptr;
    rhs.theSize = 0;
    rhs.theCapacity = 0;
  }

  Vector & operator= (Vector && rhs)
  {
    std::swap(theSize, rhs.theSize);
    std::swap(theCapacity, rhs.theCapacity);
    std::swap(objects, rhs.objects);

    return *this;
  }

  bool empty() const
  {
    return size() == 0;
  }
  int size() const
  {
    return theSize;
  }
  int capacity() const
  {
    return theCapacity;
  }

  Object & operator[](int index)
  {
    return objects[index];
  }

  const Object & operator[](int index) const
  {
    return objects[index];
  }

  void resize(int newSize)
  {
    if (newSize > theCapacity)
      reserve(newSize * 2);
    theSize = newSize;
  }

  void reserve(int newCapacity)
  {
    if (newCapacity < theSize)
      return;

    Object *newArray = new Object[newCapacity];
    for (int k = 0; k < theSize; ++k)
      newArray[k] = std::move(objects[k]);

    theCapacity = newCapacity;
    std::swap(objects, newArray);
    delete[] newArray;
  }

  // Stacky stuff
  void push_back(const Object & x)
  {
    if (theSize == theCapacity)
      reserve(2 * theCapacity + 1);
    objects[theSize++] = x;
  }
  // Stacky stuff
  void push_back(Object && x)
  {
    if (theSize == theCapacity)
      reserve(2 * theCapacity + 1);
    objects[theSize++] = std::move(x);
  }


  // Iterator stuff: not bounds checked
  typedef Object * iterator;
  typedef const Object * const_iterator;

  iterator begin()
  {
    return &objects[0];
  }
  const_iterator begin() const
  {
    return &objects[0];
  }
  iterator end()
  {
    return &objects[size()];
  }
  const_iterator end() const
  {
    return &objects[size()];
  }

  static const int SPARE_CAPACITY = 2;

  iterator erase(iterator vItr) {
    //Insert Code here
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


SCENARIO("Testing Question 1") {
  GIVEN("A vector of 1 element") {
    Vector<int> vOne; 
    vOne.push_back(1); 
    Vector<int>::iterator vOneIterator1 = vOne.end();
    WHEN("The element is erased") {
      Vector<int>::iterator catchItr = vOne.erase(vOne.begin()); 
      THEN("The size should be zero") {
	REQUIRE(vOne.size() == 0);
      }
      THEN("end() should not return the same iterator") {
	REQUIRE(vOne.end() != vOneIterator1);
      }
    }
  }
  GIVEN("A vector of some elements") {
    Vector<int> vSome; 
    vSome.push_back(1); 
    vSome.push_back(2); 
    vSome.push_back(3); 
    int beforeSize = vSome.size(); 
    Vector<int>::iterator beforeErase = vSome.end(); 
    WHEN("The second element is erased") {
      Vector<int>::iterator catchItr = vSome.erase(vSome.begin() + 1); 
      THEN("Make sure the size is decreased by 1") {
	REQUIRE(vSome.size() == beforeSize - 1); 
      }
      THEN("Make sure the order of element is correct") {
	REQUIRE(vSome[0] == 1);
	REQUIRE(vSome[1] == 3); 
				
      }
      THEN("Make sure the last element has been erased") {
	REQUIRE(beforeErase != vSome.end()); 
      }
    }
  }
}
