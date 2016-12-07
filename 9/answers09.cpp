//
//  Binary Search Tree Class
//
//  Modified code from Weiss
//
#define CATCH_CONFIG_MAIN
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <ctime>
#include "catch.hpp"

using namespace std;

class timer {
public:
    timer() : start( std::clock() ) {}
    double elapsed() { return ( clock() - start ) / CLOCKS_PER_SEC; }
    void reset() { start = clock(); }
private:
    double start;
};


template<class Comparable>
struct BinaryNode
{
    Comparable element;
    BinaryNode *left;
    BinaryNode *right;
    
    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
    : element{ theElement }, left{ lt }, right{ rt }{ }
    
    BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
    : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
};


// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// bool contains( x )     --> Return true if x is present
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************


template <typename Comparable>
class BinarySearchTree
{
public:
    typedef BinaryNode<Comparable> Node;
    typedef pair< Node *, Node *> NodePair;
    
    BinarySearchTree( ) : root{ nullptr }
    {
    }
    
    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }
    
    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }
    
    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
    
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }
    
    
    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }
    
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }
    
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }


    //Only for testing purposes
	BinaryNode<Comparable>* get_root() {
		return root;
	}

    void rangedPrint( const Comparable &low, const Comparable &high ) const {
        try {
            if ( high < low )
                throw 1;
        } catch(int& e) {
            cout << e << "Incorrect Bounds!" << endl;
            return;
        }
        printRange( low, high, root );
    }

    /**
     * Input: Called on a BST
     * Result: Turns BST into a stringy tree
     */
    void stringy() {
        if ( root == nullptr ) return;
        root = stringy( root ).first;
    } 

    void printRightPath() {
        Node* r = root;
        while ( r != nullptr ) {
            cout << r->element << endl;
            cout << right << endl;
            r = r->right;
        }
    }

    void levelOrderTraversal() {
        queue<Node *> q;
        Node * current = root;
        q.push( current );
        while ( !q.empty() ) {
            current = q.front();
            cout << current->element << " ";
            if ( current->left != nullptr )
                q.push( current->left );
            if ( current->right != nullptr )
                q.push( current->right );
            q.pop();
        }
        cout << endl;
    }

    float average_node_depth() {
        pair<int, int> p = average_node_depth( root, 0 );
        return ((float) p.second) / p.first;
    }
   
private:
    
    BinaryNode<Comparable> *root;
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, Node * & t )
    {
        if( t == nullptr )
            t = new Node{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, Node * & t )
    {
        if( t == nullptr )
            t = new Node{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing
    }
    
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( Node * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }
    
    
    /**
     * Internal method to clone subtree.
     */
    Node * clone( Node *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new Node{ t->element, clone( t->left ), clone( t->right ) };
    }
    
    bool contains( const Comparable & x, const Node * t ) const {
        if ( t == nullptr )
            return false;
        if ( t->element == x )
           return true; 
        if ( t->element < x )
            return contains( x, t->right );
        return contains( x, t->left );
    }

    void printRange( const Comparable &low, const Comparable &high, const Node * t ) const {
        if ( t == nullptr )
            return;
        if ( t->element > high ) {
            printRange( low, high, t->left );
            return;
        }
        if ( t->element < low ) {
            printRange( low, high, t->right );
            return;
        }
        printRange( low, high, t->left );
        cout << t->element << endl;
        printRange( low, high, t->right );
        return;
    }

    /**
     * Input: the root node t to a BST
     * Returns: tail node to the stringy tree made from BST
     **/

    NodePair stringy( Node* t)
    {
        if ( t->left == nullptr && t->right == nullptr )
            return { t, t };
        if ( t->left == nullptr ) {
            NodePair r = stringy( t->right );
            t->right = r.first;
            return { t, r.second };
        }
        if ( t->right == nullptr ) {
            NodePair l = stringy( t->left );
            l.second->right = t;
            t->left = nullptr;
            return { l.first, t};
        }
        NodePair l = stringy( t->left  );
        NodePair r = stringy( t->right );
        l.second->right = t;
        t->left = nullptr;
        t->right = r.first;
        return { l.first, r.second };
    }   

    pair<int, int> average_node_depth( Node * t, int d ) { // size, depth
        if ( t->left == nullptr && t->right == nullptr )
            return pair<int, int>( 1, d );
        if ( t->left == nullptr ) {
            pair<int, int> r = average_node_depth( t->right, d+1 );
            r.first = r.first + 1; r.second = r.second + d;
            return r;
        }
        if ( t->right == nullptr ) {
            pair<int, int> l = average_node_depth( t->left, d+1 );
            l.first = l.first + 1; l.second = l.second + d;
            return l;
        }
        pair<int, int> l = average_node_depth( t->left, d+1 );
        pair<int, int> r = average_node_depth( t->right, d+1 );
        l.first += r.first + 1; l.second += r.second + d;
        return l;
    }
};

//For testing purposes
template<class tp>
vector<tp> toVec(stringstream& strm) {
	tp i;
	vector<tp> vec;
	while (strm >> i) {
		vec.push_back(i);
		if (strm.peek() == ' ' || strm.peek() == '\n' || strm.peek() == ',') {
			strm.ignore();
		}
	}
	return vec;
}

//For testing purposes
struct cout_redirect {
	cout_redirect(std::streambuf * new_buffer)
		: old(std::cout.rdbuf(new_buffer))
	{ }

	~cout_redirect() {
		std::cout.rdbuf(old);
	}

private:
	std::streambuf * old;
};

SCENARIO("Testing the BinarySearchTree class") {
	GIVEN("A Binary Search tree with values inserted") {
		BinarySearchTree<int> bst;
		bst.insert(31);
		bst.insert(12);
		bst.insert(53);
		bst.insert(4);
		bst.insert(25);
		bst.insert(46);
		bst.insert(67);
		WHEN("Method contains is used") {
			bool Con_31 = bst.contains(31);
			bool Con_25 = bst.contains(25);
			bool Con_1 = bst.contains(1);
			THEN("31 and 25 should be true, but 1 should be false") {
				REQUIRE(Con_31 == true);
				REQUIRE(Con_25 == true);
				REQUIRE(Con_1 == false);
			}
		}
		WHEN("Method rangedPrint is called") {
			stringstream buffer;
            cout << "test1" << endl;
			cout_redirect redir(buffer.rdbuf());
            cout << "test2" << endl;
			bst.rangedPrint(12, 53);
			vector<int> resVec = { 12,25,31,46,53 };
			vector<int> asVec = toVec<int>(buffer);
			THEN("It should print out all objects in the given range") {
				for (int x = 0; x < asVec.size(); ++x) {
					REQUIRE( resVec[x] == asVec[x] );
				}
			}
		}
		WHEN("Method average_node_depth is called") {
			double depth = bst.average_node_depth();
			REQUIRE(depth <= 1.429);
			REQUIRE(depth >= 1.427);
		}
		WHEN("Method levelOrderTraversal is called") {
			stringstream buffer;
			cout_redirect redir(buffer.rdbuf());
			bst.levelOrderTraversal();
			vector<int> resVec = { 31, 12, 53, 4, 25, 46, 67 };
			vector<int> asVec = toVec<int>(buffer);
			THEN("It should print out items in every level before the next level") {
				for (int x = 0; x < asVec.size(); ++x) {
					REQUIRE(resVec[x] == asVec[x]);
				}
			}
		}
	}
	GIVEN("A Binary Search Tree with values 'a' to 'f' inserted") {
		BinarySearchTree<char> bst2;
		bst2.insert('d');
		bst2.insert('b');
		bst2.insert('f');
		bst2.insert('a');
		bst2.insert('c');
		bst2.insert('e');
		WHEN("Method stringy is called") {
			bst2.stringy();
			THEN("All nodes should have nullptr in left member and tree height should be n-1") {
				int size = -1;
				BinaryNode<char>* root = bst2.get_root();
				vector<char> resVec = { 'a', 'b', 'c', 'd', 'e', 'f'};
				while (root != nullptr) {
					REQUIRE(root->left == nullptr);
					REQUIRE(resVec[size + 1] == root->element);
					size += 1;
					root = root->right;
				}
				REQUIRE(size == 5);
			}

		}
	}
}
