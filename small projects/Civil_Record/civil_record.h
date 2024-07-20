#include <iostream>
#include <string>
using namespace std ;

struct date{
    unsigned int day,month,year;
};
enum {
    dead=0,alive
};
struct node{
    unsigned int id;
    date bdate;
    string name;
    string mother_name ;
    string address;
    bool life_status ;
    node * parent ;
    node * left ;
    node * right ;
};
class bst{
    private:
        node *root ;
        unsigned int count ;
        node *get_node(node&) ;
        void fix_parent(node*src,node*dest) ;
    public:
        bst();
        bst(node *data);
        bst(node *data_set,unsigned int size);
        ~bst() ;
        node*get_root(void){
            return root ;
        }
        unsigned int get_count(void){
            return count;
        }
        bool insert(node&data);
        node* search(unsigned int id) ;
        bool is_root(node*ptr) ;
        bool is_left(node*ptr) ;
        node *max(node*ptr) ;
        node *min(node*ptr) ;
        bool del(unsigned int id) ;
        bool update(unsigned int id ,unsigned int change_parameter);
        node* del_tree(node*) ;
        void inorder(node*) ;
        void show_node(node*);
};

class civil_rec{
    private:
        bst tree ;
    public:
        civil_rec(){
            tree = bst() ;
        }
        civil_rec(node*data_set,unsigned int size){
           tree =  bst(data_set,size) ;
        }
        ~civil_rec(){
            del_rec() ;
        }
        void insert_person(void);
        void search_for(void) ;
        void update_person(void);
        void show_person(void) ;
        void show_rec(void) ;
        void del_rec(void) ;
        void del_person(void);
};
