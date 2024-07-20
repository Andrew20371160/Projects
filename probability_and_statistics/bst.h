
#ifndef _bst_h_
#define _bst_h_

/*Includes*/
#include <iostream>
#include <conio.h>
#include <queue>
#include <limits>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>



using namespace std ;


//node structure conataining template data type
template <typename DataType>
struct node{
    //element of the set
    DataType data ;
    //counter for number of occrrunces of the element
    //the elements are stored with no duplicates but the counter stores their count efficiently
    int counter ;
    //links
    node<DataType>*left;
    node<DataType>*right ;
    node<DataType>*parent ;
};



    /*
    to_string overloading for different data types
    if overloading occurs for very large integers these will produce wrong output
    */
    string to_string(const int &data);
    string to_string(const char &data);
    string to_string(const double &data);
    string to_string(const float &data);
    string to_string(const long &data);
    string to_string(const double &data);
    string to_string(const bool &data);
    string to_string(const unsigned int&data);
    string to_string(const string&data);

    //turns a vector into a string
    //this bst an be used to store vectors
    template<typename DataType>
    string to_string(const vector<DataType>&vec);



enum {not_sorted=0,sorted} ;
template<typename DataType>
//helper function to allocate memory for a new node
//by default the number of instances of the element (data) is one
node<DataType>*get_node(const DataType& _data,const int &counter = 1);//passed


/*
The bst is modified to allow multiple instances of the same element
the problem where if an array is inserted immediately using a constructor where elements of the array are sorted
are now handled in the new array constructor
*/
//class bst
template<typename DataType>
class bst{

    template<typename set_DataType>
    friend class set;
    template<typename set_DataType>
    friend class prob_tree;
    //root of the bst
    node<DataType>*root ;
    //this pointer is used in traversing the tree and search and deltetion
    //its mutable so that when searching in a const tree it doesn't cause an error
    mutable node<DataType>*traverser;

    //number of nodes inside the tree
    long long nodes_count ;
    //total number of elements
    //number of occurrences of each element is countet aswell
    long long size ;

    /*
    helper functions that aren't accessible by the user
    */


    //checks if ptr is left or right child or is the root
    bool is_left(node<DataType>*ptr)const ;//passed
    bool is_right(node<DataType>*ptr)const ;//passed
    bool is_root(node<DataType>*ptr)const ;//passed

    /*
    this function makes ptr's parent's link pointing at ptr point at another destiniation
    for example ptr is left child of a parent left and we want it to point to another node
    this function takes care of it
    */
    void fix_parent(node<DataType>*ptr,node<DataType>*dest);//passed

    //returns a pointer to maximum data or rightmost node in the tree
    node<DataType>* get_max(node<DataType>*)const ;//passed

    //returns a pointer to minimum data or leftmost node in the tree
    node<DataType>* get_min(node<DataType>*)const ;//passed

    //takes a root pointer of some tree or a subtree and then makes a copy and then
    //returns resulting root (used in operator=)
    node<DataType>* copy_bst(const node<DataType>*) ;//passed

    //deletes a tree or a subtree where root is ptr
    void del_tree(node<DataType>*ptr) ;//passed

    /*
    these functions fill a bst from sorted data in linear time (O(N))
    and returns the root of the treee
    one from an array and the other one from a file but the indexing file must exist(used in load)
    */
    node<DataType>*fill_sorted(const DataType*arr,long long  beg,long long  size,node<DataType>*ptr);//passed
    node<DataType>*fill_sorted(const vector<DataType>&arr,long long  beg,long long  size,node<DataType>*ptr);//passed
    //this function is used to construct a bst from sorted array of pointers pointers to nodes
    //the array contains addresses of nodes of a bst that's already created
    //used a lot in set class
    node<DataType>*fill_sorted(const node<DataType>**arr,long long  beg,long long  size,node<DataType>*ptr);//passed

public:
    //empty tree
    bst(void);//passed
    //tree filled from an array
    //if data is sorted its filled in O(N) else O(Nlog2N)
    bst(const DataType*arr,const long long  size);//passed
    //filles a sorted array of pointers to nodes of already constructed bst
    //used to efficiently construct a new set from an already existing set
    //it's clean and i'm proud :)
    bst(const node<DataType>**arr,const long long  size);//passed

    //tree filled from an array
    //if data is sorted its filled in O(N) else O(Nlog2N)
    bst(const vector<DataType>&arr);//passed

    //copy constructor
    bst(const bst&src);//passed

    //destructor of the tree
    ~bst(void) ;//passed

    //assignment operator
    //if src is empty then the phantom will be deleted aswell it assigns src to phantom
    //so be careful
    void operator=(const bst&src) ;//passed


    //returns true if data in an array is sorted
    bool is_sorted(const DataType*arr,long long  size);
    //returns true if data in a file is sorted

    bool is_sorted(const vector<DataType>&arr);

    //inserts data into the bst
    //can insert with duplicates (all stored in same node using a counter)
    bool insert(const DataType&data,const int &count=1) ;//passed
    //this function puts traverser on the node containing data if found
    //and returns true

    bool search(const DataType&data,node<DataType>*ptr=NULL)const  ;//passed
    //this function removes node contatining data if found
    //returns true if node is found
    bool remove(const DataType&data,node<DataType>*ptr=NULL) ;


    //this function removes the whole bst
    bool remove_tree(void);//passed

    //this function looks for the node containing data and remvoes the node
    //and the subtree below it
    //if its the root node then whole tree is deleted
    bool remove_subtree(const DataType&data) ;


    /*
    printing functions
    */
    void inorder(node<DataType>*ptr=NULL)const ;//passed

    void preorder(node<DataType>*ptr=NULL)const ;//passed

    void postorder(node<DataType>*ptr=NULL)const ;//passed

    void breadth_first(node<DataType>*ptr=NULL)const ;//passed

    //equality of 2 bst is if they have same structure and same data
    //so breadth first equality is checked via this function
    bool operator==(const bst&src)const  ;
    //compares max of phantom is less than max of src
    bool operator <(const bst&src) const ;
    //compares if max of phantom is bigger than max of src
    bool operator >(const bst&src) const ;
    //turns a bst into a string and stores it into str
    //used in cout<<
    void to_string(string&str,node<DataType>*ptr=NULL)const ;

    //moves traverser in the tree via a set of controls
    void move(void)const ;//passed

    //returns total number of elements
    long long  get_size()const;
    //returns number of unique (nodes) elements in the tree
    long long  get_nodes_count()const;

    DataType access_traverser(void) ;
};



    //turns bst into a string
    template<typename DataType>
    string to_string(const bst<DataType>&tree);


    //you can cout a bst
    template<typename DataType>
    ostream& operator<<(std::ostream& os, const bst<DataType>& obj) ;

    //you can cin>>  into a bst
    //it stops reading data when it sees '\n' you have to type it manulally
    template<typename DataType>
    istream& operator>>(std::istream& is, bst<DataType>& obj);


    #include "bst.tpp"


#endif
