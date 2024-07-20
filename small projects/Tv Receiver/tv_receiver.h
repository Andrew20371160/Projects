// Include necessary libraries
#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>

// Use the standard namespace
using namespace std;

// Define a struct for the nodes in the doubly linked list
struct node {
    unsigned int ch_num; // Channel number
    string ch_name; // Channel name
    node * prev; // Pointer to the previous node
    node * next; // Pointer to the next node
};

// Define a class for the doubly linked list
class doubly_list{
private:
    node * tail; // Pointer to the last node in the list
    unsigned int ch_count; // Count of channels in the list
    friend class receiver; // Declare receiver as a friend class
public:
    node* get_tail(void); // Function to get the tail of the list
    unsigned int get_count(); // Function to get the count of channels
    doubly_list(); // Default constructor
    doubly_list(node* data_set, unsigned int size); // Constructor with parameters
    ~doubly_list(); // Destructor
    node * get_node(unsigned int, string&); // Function to get a node
    void add_at_end(string & name); // Function to add a node at the end of the list
    void add_at_beg(string & name); // Function to add a node at the beginning of the list
    void inc_from(node* starting_ptr, bool decrement); // Function to increment or decrement from a starting pointer
    void show(); // Function to display the list
    void add_at_pos(unsigned int pos, string & name); // Function to add a node at a specific position
    void del_at_beg(); // Function to delete a node at the beginning of the list
    void del_at_end(); // Function to delete a node at the end of the list
    void del_at_pos(unsigned int pos); // Function to delete a node at a specific position
    void del_all(); // Function to delete all nodes
    void sort(); // Function to sort the list
    node* search(unsigned int ch_num); // Function to search for a node
    void switch_nodes(node * ptr1, node * ptr2); // Function to switch two nodes
};

// Define a class for the receiver, which inherits from doubly_list
class receiver: public doubly_list{
private:
    node *channel_ptr; // Pointer to the current channel
    bool empty_receiver; // Flag to check if the receiver is empty
public:
    receiver(); // Default constructor
    receiver(node* data_set, unsigned int size); // Constructor with parameters
    ~receiver(void); // Destructor
    bool is_empty(void); // Function to check if the receiver is empty
    void operator ++(void); // Overloaded increment operator to go to the next channel
    void operator --(void); // Overloaded decrement operator to go to the previous channel
    void add(void); // Function to add a channel
    void show_cur(void); // Function to display the current channel
    void change_location(void); // Function to change the location of the current channel
    void helper(void); // Helper function
    void get_to(void); // Function to get to a specific channel
    void del_cur(void); // Function to delete the current channel
    void del_all(void); // Function to delete all channels
    void del_at_pos(void); // Function to delete a channel at a specific position
    void sort(void); // Function to sort the channels
    void show(void); // Function to display all channels
};
