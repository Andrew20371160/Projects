
#ifndef _graph_h_

#define _graph_h_
/*
Includes
*/
#include <iostream>
#include <conio.h>
#include <stdint.h>
#include <list>
#include <fstream>
#include <queue>
using namespace std ;



/*
enum for leaves
*/
enum{not_leaf = 0, leaf} ;
/*
enum for gates
*/
/*
not gate  and BUFFER only has one input if you try to assign more your input is ignored
(no short circuits)
*/
enum{
    NOT =0,BUFFER,NAND ,AND,NOR ,OR ,XNOR,XOR
};


//to verify if a gate is valid from input size and the gate type
bool is_valid_gate(const uint16_t&g_type,const uint32_t&in_size);


/*
no objects are to be created from this class
it's used to handle gate's issues not the graph issues
*/
class gate{

    friend class graph ;

    uint16_t gate_type;
    //gate only has one output but it's output can be wired into multiple inputs
    bool output ;
    //array of booleans to store input logic if it's a leaf
    /*
    you can't have a gate with mixed input (array of booleans is always deleted if you assign a child to its gate)
    also if you wire some gate's output to current gate input it's also deleted
    you can only have mixed input in the case if it's children and wires
    also for buffer ,not gates they can only have one source of input no other
    */
    bool *input ;
    uint32_t input_size ;

    //links for the gate
    /*
    each children of the same gate has a parent pointer
    that pointer points to same parent gate
                       |
    like this :       xor
                     / | \
                    g1 g2 g3
    */
    gate*parent ;

    gate*next;
    gate*prev;
    //head of the list of children gates
    gate*children ;
    //counter for the number of children used in saving and loading the graph
    uint32_t children_count ;
    /*
    the wiring system
    if the gate's output is mapped to another gate's input
    say from a to b
    then wire_output of a stores address of b
    and wire_input of b stores a
    */
    list<gate*>wire_input;
    list<gate*>wire_output;

        //allocate memory for a new gate
        gate*get_gate(const uint16_t&g_type,const uint32_t&in_size);//good
        /*
        this function is used when inserting a new gate as a child or at the right
        say you wanna add a child to a buffer
        if the buffer doesn't have any child or any wire as a source of input then it returns true
        if the gate type isn't a buffer ,not it returns true
        if the buffer has input though (array of booleans allocated) it gets deleted while inserting a new gate
        into the tree
        basically to make sure the not ,buffer gates only have one source of input
        */
        bool buffer_not_condition(const gate*ptr);//good

        /*
        wiring system
        */
        /*
        connect a src_input output to caller input
        if caller gate has memory allocated for the array of booleans it's deleted
        if it satisfies the buffer_not_condition it's connected
        */
        bool connect_wire( gate*&src_input);//good
        /*
        disconnect src_input output from caller input
        if caller now has no src of input you can use first_no_input which returns a pointer
        to first gate in the gate's tree to first gate with no input
        you can also use all no input which returns a list of all the gates that have no input src
        */
        bool disconnect_wire( gate*&src_input);//good
        /*returns pointer to first gate fount with no input
        no selfinput ,no children ,no wires
        */
        gate*first_no_input(void);
        //returns a list of gates that have no src of input
        list<gate*>all_no_input(void);
        /*
        this function returns a pointer after following path of gate_path
        for ex: if path is crrc it goes down then right right then down
        */
        gate* get_to(string gate_path);

        /*
        this is used in wiring a component (when loaded from a file)
        */
        void wire_system(string wiring);


        /*
        removes whole gate
        */
        void remove_all(gate*&root);

    public:


        //resize input of the gate and setting input size while doing so
        bool resize_input(const uint32_t);//good
        //change the gate's type
        bool change_type(const uint16_t&g_type);//good

        /*
        append a gate to the right of caller
        if buffer_not_condition is satisfied and gate type is valid it inserts a new gate successfully into the graph
        */
        bool append_right(const uint16_t&g_type,const uint32_t&in_size) ;//good
        /*
        append a gate as a child
        same thing if it satisfies buffer_not_condition gate is inserted
        if the caller is a leaf gate then if it's input (array of booleans) is allocated its memory is freed
        */
        bool append_child(const uint16_t&g_type,const uint32_t &in_size) ;//good


        /*
        disconnect self from all wires connected to it as an input
        */
        bool disconnect_wires_in(void) ;//good
        /*
        disconnect self's output from all gates that has its input as an input
        */
        bool disconnect_wires_out(void) ;//good

        /*printing section*/
        void print_input_logic(void);//good
        void print_input_sticks(void);//good
        void print_input_gates(void);//good
        void print(void);//good

    };



/*
The graph or board in this context represents a digital logic design environment,
similar to a physical logic board or a breadboard in electronics.
You can place logic gates on this board and connect them to form complex digital circuits.

Each gate in the graph can be a root of its own sub-tree,

meaning it can have its own set of child gates. Gates can also be connected to other gates at the same level,
forming a list of sibling gates.
This allows for the creation of complex, multi-layered digital circuits.

Just like on a physical logic board, gates on this digital board can be connected and disconnected,
inputs can be set, and the output of the entire circuit can be evaluated based on the logic of the gates
and their connections.



*/
/*
this is the class used in interfacing with the user
*/
/*
the data structure used is a general graph but you can attatch gates right to the root
it's a graph where at the same level there could be a list of gates
and each gate can hold a list of gates or be a leaf
*/
class graph{
     /*
    this is where you are constructing the board
    root can be in a list aswell

     |           |          |
    xor         and         or
    xor's       and's       or's children
  children   children

    xor ,and ,or gates will have differnt outputs according to their children only
    their children are spearated from each other
    just like a logic board

    */
    gate*root ;
    /*
    this is the traverser or your remote control through the whole graph
    move it manually to reach the gate you want
    */
    mutable gate*traverser ;

     /*
    evaluation functions for each gate and it's inverse

    if you found a zero and it's an "and" gate
    then the o/p is zero if "nand" then logic is true
    if all are ones then if "and" then true else it's false
    note that they evaluate the logic for the gate either it's a leaf or a gate with children or based on wiring
    connected to it
    they are used in evaluate() where it performs post order traverser and evaluate logic for
    children gates first then it does it for the parent gates
    these functions are created knowing previous fact
    */
    void evaluate_and_nand(gate*ptr) ;
    void evaluate_or_nor(gate*ptr) ;
    void evaluate_xor_xnor(gate*ptr) ;
    void evaluate_buffer_not(gate*ptr) ;
    /*
    visit all children evaluate them
    then go to parents
    also if the board has gates next to the root node
    they are evaluated aswell
    */
    void evaluate(gate*ptr = NULL) ;
    /*
    same as normal board
    you put zeros and noes from left to right
    they are inserted to the gate leaves of the board from left to right
    if logic is not defined (not zero or one) or the input string doesn't match No. of leaves' pins
    then by default they are filled with zeroes
    */
    void set_input(const string&input_logic ,uint32_t &logic_counter,gate*ptr);
    /*
    update lins surrounding input gate to prepare it to get deleted
    */
    void remove_links(gate*);//good
    //removes the gate and its children and disconnect all wires related to it
    void remove_gate(gate*);//good

    /*
    this function is used to map the path from the root of the graph to the input gate
    and returns a string represening path leading to it
    if its the root it reutnrs "" else it returns something like this

    crccr which means visit go down go right go down go down and then go right
    its used in automatiting the wiring of the system when saving the graph into files
    */
    string get_path(gate*);//good
    //helper function to count nodes of a list where head is the head of it
    uint32_t count_list(gate*head);
    /*
    goes through each node of head list and assign parent link of them to point to input parent
    */
    bool assign_parent(gate*head,gate*parent) ;
    /*
    after loading a file these function append the component into the graph
    if the component is a list of major trees
    then each parent link of the nodes is assigned to traverser

    */
    bool append_child(gate*component) ;
    /*
    append component to the right with all links assigned correctly
    as if you inserted the whole component by hand
    */
    bool append_right(gate*component) ;


    public :
        //empty graph constructor
        graph(void);//good
        //destructor for the whole graph
        ~graph(void);//good
        //removes the whole graph
        void remove_graph(void);
        /*
        this function is used as a remote control
        to move through the gates using w , a, s ,d
        if you hit s and the connected gates are wires you won't go down

        the function is the only function used to traverse the graph
        created a bit of graphics where if you found
                        1
                        |
                        xor
           |            |                   | then you are at the xor gate where the output is 1 and the input is 0 1 0
           0            1                   0
         input  output of children     output from wires
         array

           note : to view logic correctly
           use set_input and then call view_logic
        */
        bool move(void);//good

        /*
        used to add leaves gates to the board
        you must specify a +ve no. of input pins and the gate type before traversing through the graph
        here move() is called so that you can move through the graph
        you have 2 ways to append a gate one is on the right and the other as an input to another gate
        for ex :
              |
             xor
            |  |
           and or
        if you append "not" right to xor
        then it will be a child of same parent that xor is connected with (if xor is a child gate)
                        parent______gate
                         |            |
        like this ->    xor          not   (where not is now a leaf)
                        | |           |
                    xor's children


        if as input to xor
             |
           xor
         |  |  |
       and or  not
               |

        */
        void insert(void);//good

        bool remove(void);//good
        //evaluate logic for the whole graph
        void evaluate(void);
        /*
        connect output of a gate to input of another gate
        */
        bool connect(void);
        /*
        disconnect output of a gate from input of another gate
        */
        bool disconnect(void);
        /*
        same as normal board
        you put zeros and noes from left to right
        they are inserted to the gate leaves of the board from left to right
        if logic is not defined (not zero or one) or the input string doesn't match No. of leaves' pins
        then by defaulty they are filled with zeroes
        */
        void set_input(const string&input_logic);
        void view_logic(void);



        /*
        saves each tree at a file from 0 to n-1
        say you have a graph like this
        tree1 tree2 tree3
        so you have 3 trees that their output is independent from the other
        each one is saved in a file (you don't have to number it just name the file)
        also no need to write extension its .txt anyway
        also saves wiring of the system into a separate file after saving the whole graph
        into a file with the word "wiring" added to it
        */
        void save(void);
        /*
        say you wanna load a half adder which is saved like this
        path\ha0.txt path\ha1.txt path\hawiring.txt
        this function loads the whole component for you and appends ha1 to ha0
        then wires it using the wiring
        then promts the user to append the component in the place he/she wants
        so you just type path\component's name for ex: path\ha
        and this function handles everything for you
        if there any bugs please let me know
        */
        void load(void);

        /*
        move to a gate and this prints path leading to it
        */
        void get_path(void) ;

        /*
        returns a string representing whole wiring of the system
        in this format
        rcrc:rrr
        ccr:c
        cr:
        rrc:rr
        where left characters are path leading to output of a gate and characters right to ':' are
        path to input of another gate
        in short from:to
        note the empty string represents input going to root -> cr:

        */
        string get_wiring(void);


    };

#endif
