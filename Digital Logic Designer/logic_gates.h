
#ifndef _logic_gates_h_

#define _logic_gates_h_

/*
Includes
*/
#include <iostream>
#include <string>
#include <conio.h>
#include <queue>

using namespace std ;


/*
enum for gates
*/

/*
not gate  and BUFFER only has one input if you try to assign more your input is ignored
(no short circuits)
*/
enum{
    NOT =0,BUFFER,AND ,NAND,OR ,NOR ,XNOR,XOR
};

/*
enum for leaves
*/
enum{not_leaf = 0, leaf} ;



/*
the data structure used is a general graph but you can attatch gates right to the root
it's a graph where at the same level there could be a list of gates
and each gate can hold a list of gates or be a leaf
*/
struct gate
{
    /*
    for leaf gates this defines No. of input pins
    */
    int input_size;

    short gate_type ;
    /*
    each gate contains only one output (as it's irl)
    */
    bool output ;
    /*
    if it's a leaf then the self_input which is an array of booleans is allocated and chilren
    which is the head of a list of children gates is nulls
    else if self input is null then this isn't a leaf gate hence
    children is a head for a list of gates
    note: the gate can't contain mixed type of input i.e.
    only list of children gates or an array of booleans (as pins)
    you can use BUFFER as a way to extend the input of a gate

    if you connected a g2 to g1 (where g1 was a leaf gate)
    the memory allocated for the array of booleans is g1 is freed and it's set to null

    */
    bool * self_input ;

    gate * children ;

    /*
    the list of gates that are an input to one gate are conntected together as a doubly linked list
    children of different gates ofcourse aren't connected but their parents could be connected
    */
    gate * next ;
    gate * prev ;

    /*
    each children of the same gate has a parent pointer
    that pointer points to same parent gate
                       |
    like this :       xor
                     / | \
                    g1 g2 g3
    */
    gate *parent ;


};





/*
will be adding more updates
there are no seg-faults (till now)
*/

/*
The graph or board in this context represents a digital logic design environment,
similar to a physical logic board or a breadboard in electronics.
You can place logic gates on this board and connect them to form complex digital circuits.

Each gate in the graph can be a root of its own sub-graph,
meaning it can have its own set of child gates. Gates can also be connected to other gates at the same level,
forming a list of sibling gates.
This allows for the creation of complex, multi-layered digital circuits.

Just like on a physical logic board, gates on this digital board can be connected and disconnected,
inputs can be set, and the output of the entire circuit can be evaluated based on the logic of the gates
and their connections.



*/
class graph{

    private:
        //function to allocate memory for a gate
        /*
        since gates are added to the board then at that moment of time they are leaves
        hence this function always allocates memory for a gate of g_Type with No. of pins (in_size)

        */
        gate *get_gate(short g_type,int in_size);

        //helper function to specify if a gate is leaf
        bool is_leaf(gate*);
        /*
        this is where you constructing the board
        root can be in a list aswell

         |           |          |
        xor         and         or
        xor's       and's       or's children
      children   children

        xor ,and ,or gates will have differnt outputs according to their children only
        their children are spearated from each other
        just like a logic board

        */
        gate *root ;

        /*
        this is the traverser or your remote control through the whole graph
        move it manually to reach the gate you want
        */
        mutable gate *traverser ;
        //number of gates connected
        //not used
        int size ;

        /*
        evaluation functions for each gate and it's inverse

        if you found a zero and it's an "and" gate
        then the o/p is zero if "nand" then logic is true
        if all are ones then if "and" then true else it's false
        note that they evaluate the logic for the gate either it's a leaf or a gate with children
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

        void set_input(const string&,int& logic_counter ,gate*ptr) ;//done

        void edit_input_size(gate*ptr=NULL) ;

        void append_right(short gate_type,int gate_size) ;

        void append_child(short gate_type,int gate_size) ;

    public:
        //empty board or graph
        graph(void) ;//done
        //remove the memory of the graph
        ~graph(void); //done
        //remove a leaf or a subgraph where ptr is the root of it
        //note that if you remove a gate its children are removed aswell
        //if you want to edit the gate_type or the input then use edit function
        //by default it removes the whole graph or board
        void remove_graph(gate* ptr= NULL ) ;//done

        //prints the whole graph in breadth-first fashion
        //not the best way to view it though use move() instead
        void print(void)const ;//done
        /*

        this function is used as a remote control
        to move through the gates using w , a, s ,d
        the function is the only function used to traverse the graph
        created a bit of graphics where if you found
             1
             |
            xor
           | | | then you are at the xor gate where the output is 1 and the input is 0 1 0
           0 1 0
           note that 0 1 0 are output of children gates or the gate's array of booleans if it's a leaf
           note : to view logic correctly
           use set_input and then call view_logic
        */
        bool move(void)const;//done

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
        void insert(void) ;//done


        void edit(void) ;//done

        void remove(void);//done

        void view_logic(void) ;
        /*
        same as normal board
        you put zeros and noes from left to right
        they are inserted to the gate leaves of the board from left to right
        if logic is not defined (not zero or one) or the input string doesn't match No. of leaves' pins
        then by defaulty they are filled with zeroes
        */
        void set_input(const string&) ;
    };

#endif
