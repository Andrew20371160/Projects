
#ifndef _logic_gates_h_

#define _logic_gates_h_

#include <iostream>
#include <conio.h>
#include <stdint.h>
#include <list>
#include <fstream>
#include <queue>
using namespace std ;


enum{not_leaf = 0, leaf} ;

enum{
    NOT =0,BUFFER,NAND ,AND,NOR ,OR ,XNOR,XOR
};



bool is_valid_gate(const uint16_t&g_type);


class gate{

    friend class graph ;

    uint16_t gate_type;

    bool output ;
    bool *input ;
    uint32_t input_size ;


    gate*parent ;
    gate*next;
    gate*prev;

    gate*children ;

    uint32_t children_count ;

    list<gate*>wire_input;
    list<gate*>wire_output;


    public:
        gate*get_gate(const uint16_t&g_type,const uint32_t&in_size);//good

        bool resize_input(const uint32_t);//good
        bool change_type(const uint16_t&g_type);//good

        bool buffer_not_condition(const gate*ptr);//good

        bool append_right(const uint16_t&g_type,const uint32_t&in_size) ;//good
        bool append_child(const uint16_t&g_type,const uint32_t &in_size) ;//good
        void wire_system(string wiring);

        /*
        wiring system
        */
        bool connect_wire( gate*&src_input);//good
        bool disconnect_wire( gate*&src_input);//good
        bool disconnect_wires_in(void) ;//good
        bool disconnect_wires_out(void) ;//good

        /*returns pointer to first gate fount with no input
        no selfinput ,no children ,no wires
        */
        gate*first_no_input(void);
        //returns a list of gates that have no src of input
        list<gate*>all_no_input(void);

        gate* get_to(string gate_path);

        /*printing section*/
        void print_input_logic(void);//good
        void print_input_sticks(void);//good
        void print_input_gates(void);//good
        void print(void);//good

        void remove_all(gate*&root);
    };

class graph{

    gate*root ;
    mutable gate*traverser ;

    void evaluate_and_nand(gate*ptr) ;
    void evaluate_or_nor(gate*ptr) ;
    void evaluate_xor_xnor(gate*ptr) ;
    void evaluate_buffer_not(gate*ptr) ;
    void evaluate(gate*ptr = NULL) ;
    void set_input(const string&input_logic ,uint32_t &logic_counter,gate*ptr);

    void remove_links(gate*);//good
    void remove_gate(gate*);//good
    //pass pointer and this functions returns a string of path leading to it
    /*{
        "" for root
        c->children
        n->next

    }
    */

    string get_path(gate*);//good

    public :
        graph(void);//good
        ~graph(void);//good
        //remote control
        bool move(void);//good
        uint32_t count_list(gate*head);

        void insert(void);//good
        bool remove(void);//good
        void evaluate(void);

        bool connect(void);
        bool disconnect(void);

        void set_input(const string&input_logic);
        void view_logic(void);

        void remove_graph(void);


        void save(void);
        void load(void);

        void get_path(void) ;
        bool assign_parent(gate*head,gate*parent) ;
        string get_wiring(void);
        bool append_child(gate*component) ;
        bool append_right(gate*component) ;

    };

#endif
