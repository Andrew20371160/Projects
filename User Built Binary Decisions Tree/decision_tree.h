
//includes
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <conio.h>
#include <limits>
using namespace std ;

//node definition
struct node{
    string text ;
    int parent_answer ;
    node*parent,*left,*right ;
};
//returns true if user_input is a substring from tree_node_text
bool is_related(string&user_input,string&tree_node_text);

/*
insure that it won't cause an open loop if a user
enters a number instead of a character and vice versa
*/
bool getInput(int& choice);
bool getInput(char& choice);


//class itself
class decision_tree{
    //helper function to allocate memory for a new node
    node*get_node(string _text,bool p_answer = -1) ;

    //change traverser's parent's link pointing at traverser to another node
    void change_parent_child(node*other);
    //delete subtree where the root of it is traverser
    void del_traverser_with_children(void);
    //move left subtree where the root is pleft to a left link of a node in the tree
    //note that left link must be empty
    void move_left_subtree(node*pleft);
    //move right subtree where the root is pright to a right link of a node in the tree
    //note that right link must be empty
    void move_right_subtree(node*pright);
    //check if this pointer is in the subtree of traverser (not used but implemented)
    bool is_same_subtree(node*ptr) ;
    //root of the binary tree
    node*root ;
    //pointer traversing the tree
    node*traverser ;
public:
    decision_tree(void) ; //empty tree

    decision_tree(string*arr,int size) ;/*fill tree with data set where the answer of a
    previous question is stored in current node*/
    ~decision_tree(void) ;//delete the tree from the heap
    
    void construct(void) ;//interface with the user and construct the decision tree he wants
    //insert one question/answer into the tree
    void insert(void) ;

    void save(void)   ;//save the tree into a file in breadth-first

    void load(void)   ; //load a tree from a file in breadth-first

    void update(void) ;//update a question in the tree (update the text)

    void remove(void) ; //remove a question from the tree can change location of lower subtrees if wanted

    void switch_nodes(void) ; //a node's subtrees are reversed

    bool search(void) ; //search generally

    bool search_by_pattern(string &pattern) ; //search by the pattern leading to the quesion

    bool search_by_text(string&t) ; //search for the string using breadth first

    void print(void)  ; //print the tree using breadth first

    void interface(void);//for testing the tree or user interface

    bool move(void);//interface with traverser pointer and move around the tree

    //promts user to enter a question used when adding a question to current node traverser is pointing at
    void promt_question(void);

    void point_to_root(void) ;//puts traverser into the root

    void switch_answers(void);//switch answers of 2 children (subtrees aren't switched) strings only

    bool is_left(void);//check if traverser is a left child
};
    //delete the subtree where root is ptr
    void del_tree(node*ptr);
