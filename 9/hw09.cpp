/*
  Simon Chen
  N10013388
  sc4900
  Homework 9
*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;


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
// void rangedPrint(lo,hi )      --> prints everything in the range [lo,hi]
// ******************ERRORS********************************


template <typename Comparable>
class BinarySearchTree
{
public:
  typedef BinaryNode<Comparable> Node;
    
  BinarySearchTree( ) : root{ nullptr }, minDepth(0), maxDepth(0)
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

  //Implement these
  void rangedPrint(int low, int high) const{
    rangedPrint(low,high,root);
  }

  void stringy(){
    stringy(root);
  }

  void levelOrderTraversal() const{
    if( root != nullptr){
      cout << root->element << ",";
      levelOrderTraversal(root);
      
    }
  }

  double average_node_depth() const{
    
    int treesize = size();
    int depth = 0;
    return  average_depth(root, depth)/treesize;
  }

  int size() const { return size(root);}

private:

  BinaryNode<Comparable> *root;
  int minDepth;
  int maxDepth;

  void levelOrderTraversal(Node* t) const{
    if ( t== nullptr)
      return;

    if(t->left != nullptr){
      cout << t->left->element << ",";
    }

    if(t->right != nullptr){
      cout << t->right->element << ",";
    }

    levelOrderTraversal(t->left);
    levelOrderTraversal(t->right);
  }

    
  double average_depth(Node* t, int depth) const {
    if (t == nullptr)
      return 0;

    return depth + average_depth(t->left, depth+1) + average_depth(t->right, depth+1);

  }

  int size(Node* t) const { 
    if (t == nullptr)
      return 0;
    return 1 + size(t->left) + size(t->right);
  }


  
  void stringy(Node*& t){
    if(t == nullptr)
      return;

    Node* tmproot = findMin(t);
    Node* tmpmax = findMax(tmproot);
    Node* bMin = beforeMin(t);
    Node* tmp = t;

    cout << t->element << endl;
    // cout << tmpmax->element << endl;
    cout << tmproot->element << endl;
    // cout << bMin->element << endl;
    printRight();
    cin.get();
    
    if (t->element != tmproot-> element){
      tmpmax->right = t;
      bMin->left = nullptr;
      t = tmproot;
      cout << t->element << endl;
      stringy(tmproot->right);
    }else{
      stringy(tmproot->right);
    }
      
  }

  Node* printRight(){
    Node* t = root;
    while(t != nullptr){
      cout << t->element;
      t = t->right;
    }
  }

  BinaryNode<Comparable> * findMin( Node * t ) const
  {
    while( t->left != NULL && t != NULL )
      t = t->left;
    return t;
  }
  // Node* findMin(Node* t){
  //   while(t-> left != nullptr)
  //     t = t->left;
    
  //   return t;
	
  // }
  
  Node* beforeMin(Node* t){
    while(t-> left != nullptr && t->left->left != nullptr)
      t = t->left;
    
    return t;
  }

  Node* findMax(Node* t){
    while(t-> right != nullptr)
      t = t->right;
    return t;
	
  }

  Node* beforeMax(Node* t){
    while(t-> right != nullptr && t->right->right != nullptr)
      t = t->right;
    return t;
	
  }
  
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
    
  //implement this
  bool contains(const Comparable& x, Node* t) const
  {
    if (t == nullptr)
      return false;
    else if(t->element == x)
      return true;

    if (t->element > x)
      return contains(x,t->left);
    else
      return contains(x,t->right);
  }

  //Ranged Loop
  void rangedPrint(int low, int high, Node* t) const{

    if (t != nullptr || t->element > high)
      return;

    rangedPrint(low,high,t->left);
    rangedPrint(low,high,t->right);

    if (t->element > low){
      cout << t->element; 
    }

  }

  
};

int main(){
  BinarySearchTree<char> bst2;
  bst2.insert('d');
  bst2.insert('b');
  bst2.insert('f');
  bst2.insert('a');
  bst2.insert('c');
  bst2.insert('e');
  // bst2.levelOrderTraversal();
  // bst2.stringy();
  // cout << bst2.average_node_depth();

}
