#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>

using namespace std;


struct node {
    unsigned int ch_num ;
    string ch_name ;
    node * prev ;
    node * next  ;
};
class doubly_list{
private:
    node * tail ;
    unsigned int ch_count ;
    friend class receiver ;
public:
    //updated
    node*get_tail(void) ;
    unsigned int get_count() ;
    doubly_list();
    doubly_list(node*data_set,unsigned int size) ;
    ~doubly_list();
    node * get_node(unsigned int,string&);
    void add_at_end(string & name );
    void add_at_beg(string & name ) ;
    //increments from a selected pointer the channel number
    //untill the end used when inserting data
    void inc_from(node*starting_ptr,bool decrement) ;
    void show() ;
    void add_at_pos(unsigned int pos , string & name   ) ;
    void del_at_beg() ;
    void del_at_end() ;
    void del_at_pos(unsigned int pos ) ;
    void del_all() ;
    void sort ();
    node* search(unsigned int ch_num) ;

    void switch_nodes(node * ptr1 ,node * ptr2) ;
};
class receiver:public doubly_list{
    private:
        node *channel_ptr ;
        bool empty_receiver ;
    public:
        receiver();
        receiver(node*data_set,unsigned int size);
        ~receiver(void) ;
        bool is_empty(void) ;
        void operator ++(void);
        void operator --(void);
        void add(void) ;
        void show_cur(void) ;
        void change_location(void);
        void helper(void);
        void get_to(void) ;
        void del_cur(void) ;
        void del_all(void) ;
        void del_at_pos(void) ;
        void sort(void) ;
        void show(void) ;

};
