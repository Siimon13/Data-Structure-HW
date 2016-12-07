// CS2134 Fall 2016
// Homework 10 Programming Question 1
// Implement find, insert, and rehash with linear probing

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <vector>
#include <utility>  // for hash class
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Provided HashTable class
////////////////////////////////////////////////////////////////////////////////

template <class HashedObj>
class HashTable {
public: 
	enum EntryType { ACTIVE, EMPTY, DELETED };
private: 
	struct HashEntry {
		HashedObj element;
		EntryType info;
		HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY)
			: element(e), info(i) {}
	};
public:
    explicit HashTable (int size = 101) : currentSize(0) { array.resize(size); }
    hash<HashedObj> hf;
	//implemented for testing purposes 
	typedef typename vector<HashEntry>::const_iterator iterator;
	/////
    void makeEmpty ();
    bool remove (const HashedObj& x);
	int capacity()const;
	iterator end()const;

    // Signatures for public methods to implement
   // bool find   (const HashedObj& x) const;
    bool insert (const HashedObj& x);
	iterator find(const HashedObj&);
private:
    vector<HashEntry> array;
    int currentSize;

    // Signature for private method to implement
    void rehash();
};

/////////////////////////////////////////////////////////////////////////
// Solution Code: find, insert, and rehash with linear probing
/////////////////////////////////////////////////////////////////////////


//Find implemented with a boolean return
/*
template <class HashedObj>
bool HashTable<HashedObj>::find (const HashedObj& x) const {
    // First, get the appropriate hash so we can look where we expect the element to be
    int i = hf(x) % array.size();
    int count = 0;

    // We need to keep looking until we find the element, get to an EMPTY spot, or go around the whole table
    while (count < array.size()) {

        // If the spot is EMPTY, then the element is not in the table
        if (array[i].info == EMPTY)
            return false;

        // If the spot is DELETED, we move on, since it may have been placed after
        // this element before it was deleted
        else if (array[i].info == DELETED) {
            i = (i+1) % array.size();
            count++;

        // If the spot is occupied, check if it's the element we're looking for
        } else {
            // If it is the element we're looking for, return true
            if (array[i].element == x)
                return true;

            // Otherwise, we need to keep looking
            i = (i+1) % array.size();
            count++;
        };
    };
    return false;
};
*/

//find implemented with an iterator as a return type
template< class HashedObj >
typename HashTable<HashedObj>::iterator HashTable<HashedObj>::find(const HashedObj & x) {

	int index = hf(x) % array.size();
	// look for the item in the upper side of the array
	for (iterator i = array.begin() + index; i < array.end(); ++i) {
		if (i->info == EMPTY)
			return array.end();
		if (i->info == ACTIVE && i->element == x)
			return i;
	}
	// look for the item in the lower side of the array
	// in case the array was wrapped around before inserting
	// Unit test can be adjusted to check for this behaviour
	// by generating capacity()-1 instead of 0 for collison behaviour
	for (iterator i = array.begin(); i != array.begin() + index; ++i) {
		if (i->info == EMPTY)
			return array.end();
		if (i->info == ACTIVE && i->element == x)
			return i;
	}
	return array.end();
}

template <class HashedObj>
bool HashTable<HashedObj>::insert (const HashedObj& x) {
    // Get the appropriate hash so we can insert where we expect the element to be
    int i = hf(x) % array.size();

    // Check first if the element is already in this table, so we don't insert duplicates
	if (find(x) != end())
        return false;

    // If the spot we've hashed to is occupied, we need to move on to the next index
    while (array[i].info == ACTIVE)
        i = (i+1) % array.size();

    // If we've made it here, it means that we've reached a spot where we can insert
    // Set the element here to be 'x' and set the spot to ACTIVE
    array[i].element = x;
    array[i].info = ACTIVE;

    // Make sure that the load balance is respected -- if not, we need to rehash
    if (++currentSize >= array.size() * 0.5)
        rehash();

    return true;
};


template<class HashedObj>
void HashTable<HashedObj>::rehash() {
    // Keep track of the old array before we rehash
    vector<HashEntry> oldarray = array;

    // Clean up the current array and resize it
    array.clear();
    currentSize = 0;
    array.resize(oldarray.size()*2+1);

    // Now re-insert all of the elements to our resized array
    for (int i = 0; i < oldarray.size(); i++)
        if (oldarray[i].info == ACTIVE)
            insert(oldarray[i].element);
};

//arrays implemented for testing purposes
template<typename HashedObj>
int  HashTable<HashedObj>::capacity() const {
	return array.size();
}

template<typename HashedObj>
typename HashTable<HashedObj>::iterator HashTable<HashedObj>::end() const {
	return array.end();
}

template< typename HashedObj >
bool HashTable<HashedObj>::remove(const HashedObj & x) {
	if (array.size() == 0)
		return false;

	int index = hf(x) % array.size();
	for (int i = index; i < array.size(); ++i) {
		if (array[i].info == EMPTY)
			return false;
		if (array[i].info == ACTIVE && array[i].element == x) {
			array[i].info = DELETED;
			// Notice only info is changed to delete the item
			// So while doing find do not look only by item but also by info
			--currentSize;
			return true;
		}
	}
	// if not found in the upper side of the array
	// look for wrap around cases i.e. check on lower side of the array
	for (int i = 0; i < index; ++i) {
		if (array[i].info == EMPTY)
			return false;
		if (array[i].info == ACTIVE && array[i].element == x) {
			array[i].info = DELETED;
			--currentSize;
			return true;
		}
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////
// Test code
////////////////////////////////////////////////////////////////////////////////

SCENARIO("Testing the hash table on movable values with linear probing") {
	HashTable<int> hst;
	int n = 10; //adjust to make it less than 10 when rehash isn't implemented;
	int capacity = hst.capacity();

	GIVEN("A hash table has been created but not filled") {
		WHEN("Method insert is called") {
			THEN("All insertions of original elements should succeed") {
				for (int i = 0; i < n; ++i)
					REQUIRE(hst.insert(i*capacity) == true);
			}
			THEN("All insertions of duplicate elements should fail") {
				for (int i = 0; i < n; ++i) {
					REQUIRE(hst.insert(i * capacity) == true);
					REQUIRE(hst.insert(i * capacity) == false);
				}
			}
		}
	}

	GIVEN("A hash table has been created and filled ") {
		for (int i = 0; i < n; ++i)
			hst.insert(i * capacity);
		capacity = hst.capacity();

		WHEN("Method insert is called") {
			THEN("It should fail on all duplicate elements") {
				for (int i = 0; i < n; ++i) {
					REQUIRE(hst.insert(i*capacity) == false);
				}
			}
			THEN("It should pass on all original elements") {
				for (int i = 0; i < n; ++i) {
					hst.remove(i * capacity);
					REQUIRE(hst.insert(i*capacity) == true);
				}
				for (int i = n; i < 2 * n; ++i) {
					REQUIRE(hst.insert(i*capacity) == true);
				}
			}
		}

		WHEN("Method remove is called") {
			THEN("It should return true for any item in the table.") {
				for (int i = 0; i < n; ++i)
					REQUIRE(hst.remove(i * capacity) == true);
			}
		}

		WHEN("Method remove is called") {
			THEN("It should return false for any item not in the table.") {
				for (int i = n; i < 2 * n; ++i)
					REQUIRE(hst.remove(i * capacity) == false);
			}
		}

		WHEN("Method find is used") {
			for (int i = 0; i < n; ++i)
				hst.insert(i * capacity);
			THEN("All inserted elements should be found") {
				for (int i = 0; i < n; ++i)
					REQUIRE(hst.find(i * capacity)->element == i * capacity);
			}
			THEN("Any non-inserted element should not be found") {
				for (int i = n; i < 2 * n; ++i)
					REQUIRE(hst.find(i*capacity) == hst.end());
			}
			THEN("Any element that is deleted should not be found.") {
				for (int i = 0; i < n; ++i) {
					hst.remove(i * capacity);
					REQUIRE(hst.find(i * capacity) == hst.end());
				}
			}
		}

		WHEN("The load factor is greater than 0.5") {
			const int * temp = &(hst.find(5 * capacity)->element);
			for (int i = 1; i < 100; ++i)
				hst.insert(i);
			THEN("rehash() should be called.") {
				REQUIRE(hst.capacity() != capacity);
			}
		}
	}
}
