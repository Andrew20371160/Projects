#include "decision_tree.h"

//cicular doubly linked list where eaach node contains a pointer to a bst
struct list_node{
    //pointer to tree itself
    decision_tree*dtree;
    //name of the tree
    string name ;
    //links
    list_node*next ;
    list_node*prev ;

};



class tree_list{
    //tail of the list
    list_node*tail;
    //the pointer that will move through the list according to user's input
    list_node*traverser ;
    //helper function to allocate memory for a new list node
    list_node*get_list_node(string&tree_name);

public:
    //empty constructor
    tree_list() ;
    //delete every tree first then list nodes
    ~tree_list();
    //add a new tree into the list
    void add(void);
    //move through the list of trees
    bool move(void) ;
    //print the list of trees not trees themselves
    void print() ;
    //searach for a tree
    bool search(void);
    //search by text
    //note that if you wrote a portion of text first node that matchs is returned
    bool search_by_text(void);
    //delete a node
    void del_list_node(void);
    //engineer's interface
    //can alter/create/do any thing with the tree
    void engineer_interface(void);
    //user's interface
    //user isn't allowed to create or alter any thing in the tree
    void user_interface(void) ;
    //retunrs the tree's name that traverser is pointing at
    string get_traverser(void) ;

 };
