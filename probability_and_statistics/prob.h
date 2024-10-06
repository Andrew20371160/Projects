
#ifndef prob_h_
#define prob_h_
#include "bst.h"

#include <math.h>

#include <algorithm>

#include <chrono>

//sample space is phantom
//in sample space s find complement of A

template<typename DataType>
class set{
    /*
    bst stores elements and duplicates are allowed (you can say it's a multi-set or a bag)
    the duplicates are handled such that they are stored in one node only
    also fixed the issue where if an array with duplicates is inserted now it's handled such that
    there are no scattared duplicates around the bst
    the bst only allocates memory for unique elements and the duplicates are stored as a counter
    if you want the class to act as a normal set just use remove_dupllicates
    */
    bst<DataType>tree ;

    /*
    these functions till now built all functions necessary of the set class
    are based on the concept of euler tour that I learned at college
    the idea is simple while inorder traversing elements of phantom if that do the operation you want with the node
    int the other tree or (set) then we push it into the match_vector which is an array of pointers to pointers
    to copy wanted nodes efficiently without wasting memory (no memory leaks dw) if there is tell me though

    for example the intersection of 2 sets is elements that exist in both sets
    so for each element in tree1 if it exists in tree2 put the node with less count into match_Vector
    for example if element1 contains 3 duplicates and the other contains 1 the latter is put into the vector

    same idea is used in union of 2 sets ,probability of events ,conditional probability ,every function till now
    all applicable using one line just foucs on the functionality or what to do when visiting node of tree1
    if it has a property related to tree2

    while traversing tree1 if func_ptr(data ,three2) do something either fill a vector ,increase a counter...etc
    */
    void euler_tour(const node<DataType>*ptr,const bst<DataType>&other_tree,
                    const node<DataType>**,long long &match_counter)const;

    void euler_tour( node<DataType>*ptr, bst<DataType>&other_tree,
                    node<DataType>**,long long &match_counter);
    /*
    the next set of declarations are for functions that are used to fill the array of pointers or the counter
    during the tour
    */
    /*
    this function fills the set with intersection elements between 2 sests
    if there are duplicates it fills it with the one with less count of duplicates
    */
    bool fill_for_intersection(const node<DataType>*ptr, const bst<DataType>&other_tree, long long &counter,  const node<DataType>**match_vec)const;
    /*
    this function fills match vector with elements that are unique to phantom set and the intersection between the 2 sets
    //the intersection being the min of duplicates
    */
    bool fill_for_union(const node<DataType>*ptr, const bst<DataType>&other_tree, long long &counter,  const node<DataType>**match_vec)const;

    //    this function fills match vector with elements that are unique to phantom set only

    bool fill_for_unique(const node<DataType>*ptr, const bst<DataType>&other_tree, long long &counter,  const node<DataType>**match_vec)const;
    /*
    fills the array with elements (addresses of pointers) that exists in the phantom and not in the other set
    and with the intersection aswell
    and in diff function the difference between elements is handled
    for ex : if sample space contains 3 elements and the set contains 1 of that elements then difference is
    2 of that elements
    */
    bool fill_for_diff(const node<DataType>*ptr, const bst<DataType>&other_tree, long long &counter,  const node<DataType>**match_vec)const;
    /*
    this function counts number of elements in both sets
    for duplicates it counts the min of the 2 elements
    */
    bool count_for_intersection(const node<DataType>*ptr, const bst<DataType>&other_tree, long long &counter,  const node<DataType>**match_vec)const;


    /*
    this fucntion fills counter with multiplication of ni choose ki of elements
    where ni is count of element in the sample space and ki is count of the element in the set
    if the element doesn't exist in the sample space the counter is filled with 0
    */
    bool count_for_draw_no_replace( const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter,const node<DataType>**match_vec)const;

    /*
    these functions fills match_vec or counter according to a condition
    */
    bool exist(const node<DataType>*ptr, const bst<DataType>&other_tree, long long &counter,  const node<DataType>**match_vec)const;

    bool not_exist(const node<DataType>*ptr, const bst<DataType>&other_tree, long long &counter,  const node<DataType>**match_vec)const;
    //this function is used to fill the array with pointers of the set
    //it collects the whole bst as an array of pointers to these nodes
    bool always_exist(const node<DataType>*ptr, const bst<DataType>&other_tree, long long &counter, const  node<DataType>**match_vec)const ;

    /*
    this function fills counter with ni * data[i] where ni is count of the ith element in the set and data[i]
     is the ith element
    */
    bool count_for_avg( const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter,const node<DataType>**match_vec)const;

    bool count_for_avg(  node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec);

    bool count_for_var( const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter,const node<DataType>**match_vec)const;

    bool count_for_var(  node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec);

    /*
    this function fills counter with multiplication of  ni ^ ki of each element in the set
    where ni is count in the sample space and ki is count in the other set
    */
    bool count_for_draw_no_replace(  node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec);


    bool count_for_draw_replace( const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter,const node<DataType>**match_vec)const;

    bool count_for_draw_replace(  node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec);

    bool fill_for_intersection( node<DataType>*ptr,  bst<DataType>&other_tree, long long &counter,  node<DataType>**match_vec);

    bool fill_for_union( node<DataType>*ptr,  bst<DataType>&other_tree, long long &counter,  node<DataType>**match_vec);

    bool fill_for_unique( node<DataType>*ptr,  bst<DataType>&other_tree, long long &counter,  node<DataType>**match_vec);

    bool fill_for_diff( node<DataType>*ptr,  bst<DataType>&other_tree, long long &counter,  node<DataType>**match_vec);

    bool count_for_intersection( node<DataType>*ptr,  bst<DataType>&other_tree, long long &counter,  node<DataType>**match_vec);


    bool exist( node<DataType>*ptr,  bst<DataType>&other_tree, long long &counter,  node<DataType>**match_vec);

    bool not_exist( node<DataType>*ptr,  bst<DataType>&other_tree, long long &counter,  node<DataType>**match_vec);

    bool always_exist( node<DataType>*ptr,  bst<DataType>&other_tree, long long &counter,  node<DataType>**match_vec) ;

    /*
    used in euler tour its a pointer to function that has the following segnature
    it's used when using euler tour to put the address of the function in the func_ptr  and then call it from
    the tour
    */
    mutable  bool (set<DataType>::*func_ptr_c)(const node<DataType>*ptr,const bst<DataType>&,long long &,const node<DataType>**)const;

    mutable  bool (set<DataType>::*func_ptr)( node<DataType>*ptr, bst<DataType>&,long long &, node<DataType>**);

    /*
    sets function pointer with the function that will be used in the tour
    */
    void set_function_ptr(bool (set<DataType>::*ptr)(const node<DataType>*ptr,const bst<DataType>&,long long &, const node<DataType>**)const)const;

    void set_function_ptr(bool (set<DataType>::*ptr)( node<DataType>*ptr, bst<DataType>&,long long &, node<DataType>**));


public:
    /*
    constructors
    */
    //empty constructor
    set(void);
    /*
    the set now acts as a multi-set where it allows for more than one instance of an element
    and the duplicates aren't scattered around the tree
    no issues now when inserting a sroted array with duplicates handled efficinetly now same thing for the vector
    */
    //fill a set with initialized array
    set(DataType*_arr,int _size);
    //fill a set with initialized vector
    set(vector<DataType>&_arr);
    //copy constructor
    set(const set&src);
    //assignment operator
    void operator=(const set&) ;
    //destructor
    ~set(void) ;
    //insert an element into the set (by default it inserts one instance only if you want to insert it with a number or count )
    //for it you can do that aswell
    //if it exists already then it returns false
    bool insert(DataType data,int counter = 1) ;
    //insert an array into the set
    //if size or n <0 it doesn't insert elements
    bool insert(DataType *data,int n) ;
    //search for a data in the set
    bool search(const DataType&data)const  ;
    //remove an element completely from a set
    bool remove(const DataType&data) ;

    bool update_count(const DataType&data,const int &count);
    /*
    the following set of functions
    assume that sample-space is phantom always
    so ->s1.comp(s2) ->in sample space s1 get the complement of s2

    all these functions use the concept of euler_tour in them
    */

    /*
        returns a set of elements that exist in both set1 and set2
        if there are duplicates the min count of the element is inserted into the set
    */
    set intersect(const set&)const;
    /*
    returns the union of 2 sets
    if there are duplicates in both it inserts the count of the bigger one
    so if -> {1,1,1,2,2} and {1,1,2,5,6}
    the result is {1,1,1,2,2,5,6}
    */
    set unite(const set&)const;
    //in sample-space phantom get complement of set
    //if the set in't in the sample space then complement doesn't make sense and it returns an empty set
    set comp(const set &)const;
    //returns set of elements that exist in phantom and not set
    //also if {1,1,2,5,6} and {1,2,5}
    //it returns {1,6}
    set diff(const set&)const ;
    //replaces an element with new element
    //the element is replaced with its count
    //so if {1,1,1,2,3,5} and replace(1,4)
    //the result is {2,3,4,4,4,5}
    bool replace(const DataType&old_data,const DataType&new_data) ;
    //retunrs true if sample-space or phantom contains the set src
    bool contain(const set&)const;

    //retunrs true if sample-space or phantom doesn't contain the set src
    bool not_contain(const set&)const;
    //returns true if set1 equals set2
    bool equal(const set &) const;
    //removes every element in the set
    //turns it into phi or empty set
    bool clear(void) ;
    //returns true if a set is phi or empty
    bool empty(void) const;

    /*
    probability related functions
    */
    /*
    returns the probability of drawing an event or a set from the sample space with (no repalcement)
    sample space is phantom and the input function is the event of interest
    if{1,1,1,5,6} is sample space and input is {1,1,1,1,5}
    the result is zero since the ones exceeds the ons in the sample space
    */
    double prob_draw_no_replace(const set&)const ;
    /*
    returns the probability of drawing an event or a set from the sample space with (with repalcement)
    sample space is phantom and the input function is the event of interest
    if{1,1,1,5,6} is sample space and input is {1,1,1,1,5}
    the result isn't zero since there is replacement
    */
    double prob_draw_replace(const set&)const;
    /*
    returns the probability of an event to occur where it locates in the sample space
    if the sample space contains that event then it returns size of event/ size of sample space
    else it returns 0
    */
    double prob(const set&)const;

    /*
    in sample-space (phantom) calculate proability of event src knowing that condition event occurred

    if the sample space contains that event and the condition
    and the condition contains the src then it returns the probability of the event

    else it returns 0
    */
    double prob_cond(const set&src,const set&condition)const;
    /*
        p(src|condition) = p(src intersect condition) /p(condition)
        p(condition|src) = p(src intersect condition) /p(src)
        p(src intersect condition) =p(src|condition) *p(condition) = p(condition|src)*p(src)
        p(condition|src) = p(src|condition)*p(condition)/p(src)
    */
    double bayes(const set&src,const set&condition)const;

    /*
    in sample space (phantom) returns true if s1 and s2 are independent events
    p(s1)*p(s2)==p(s1 intersects s2)
    */
    bool independence(const set&s1,const set&s2)const;
    /*
    in sample space (phantom) returns true if group of sets are independent
    */
    bool independence(const set*,int n)const;
    bool independence(const vector<set<DataType>>&set)const;

    /*
    in sample-space phantom calculate the probability of union of events
    */
    double prob_unite(const set*,int n)const;
    /*
    in sample-space phantom calculate the probability of intersection of events
    */
    double prob_intersect(const set*,int n)const;
    double prob_intersect(const vector<set<DataType>>&set_arr)const;


    /*
    returns average or mean of the set
    sum of xi *ni /total n
    */
    double average(void)const ;

    double variance(void)const ;

    double standard_deviation(void)const ;

    DataType range(void)const ;

    /*
    returns sum of xi*weight[i] *ni /(weigts[i]*ni)
    note:weights must be according to each unique element and they must correspond to the elements in the same in order fashion
    so for set {1,1,1,5,6,7} ->weights are [2.5,65,56] where 2.5 is weight of ones and so on....
    */
    double average(const double*weights,const int &weights_size)const ;


    /*
    returns the median of a set of elements
    sadly it's O(N)
    */
    double median(void)const ;
    /*
    returns a vector where each element of that vector correspond to probability of the instance or element to occur
    for ex :{1,1,1,2,5,8} it returns [3/6,1/6,1/6,1/6] where 3/6 is for ones and so on
    */
    vector<double> pmf(void)const ;

    /*
    returns a vector where each element of that vector correspond to the cmf value of the instance or element to occur
    pmf of {1,1,1,2,5,8} is [3/6,1/6,1/6,1/6]
    so cmf is [3/6,4/6,5/6,6/6] where 3/6 is for ones and 4/6 for 2 and so on
    */
    vector<double> cmf(void)const ;


/*
    removes duplicates if they exist in a set
    if an array inserted into a bst is sorted and there are duplicates this may cause error in the calculations
    so make sure to use remove_duplicates(void) to make sure
*/

    //removes duplicate of an element if exists
    bool remove_duplicates(const DataType&data);

    //removes all duplicates of each element of the set
    //use it if you want to have a normal set not a multi-set
    bool remove_duplicates(void);


    //turns a set into a string
    string to_string(void)const  ;



    //get total number of elements of a set
    long long size(void) const;

    //get number of unique elements of a set
    long long nodes_count(void) const;


};



    template<typename DataType>
    ostream& operator<<(ostream& os, const set<DataType>& obj);
    /*
    prints a set in a visible way->{1,5,53,56,155} or {} for empty sets
    */
    //to enter a set enter the size first then the elements
    //->5 1 1 1 2 3 now you have set of 5 elements and it's {1,1,1,2,3}
    //if data is inserted in sorted fashion then the bst won't be balanced
    template<typename DataType>
    istream& operator>>(istream& is, set<DataType>& obj);

    /*
    will update the next section later
    */
    /*
    binary probability tree section

    */

    /*
    root has most probability in sample space maybe sample space
    then A A' right left
    then A then b .......z
    then after sorting nodes like that
    root intersection with event at right
    root' intersection with event at left

    then event at 2nd level
    event1 with event 2
    event1' with event 2

                root
    root'inter A   root inter A

    */

    /*
        testing some stuff
    */
    //now p_node can be put into a bst
    template <typename DataType>
    class p_node{
        private :
            set<DataType>*set_ptr ;
            set<DataType>*sample_space_ptr ;
        public:
            template<typename p_DataType>
            friend class prob_tree ;
            p_node(void);
            p_node( set<DataType>*&sample_space,const set<DataType>&_set);
            p_node(const p_node&src) ;
            ~p_node(void) ;
            void operator=(const p_node&) ;
            bool operator< (const p_node&)const  ;
            bool operator> (const p_node&)const  ;
            bool operator<=(const p_node&)const  ;
            bool operator>=(const p_node&)const  ;
            bool operator==(const p_node&)const  ;
            bool operator!=(const p_node&)const  ;
    };

    template<typename DataType>

        bool is_leaf(const node<set<DataType>>*ptr)      ;
            template<typename DataType>

        bool is_not_leaf(const node<set<DataType>>*ptr)  ;
    template<typename DataType>

        bool insert_node( node<set<DataType>>*ptr,const set<DataType>&)  ;
    template<typename DataType>

        bool search_node( node<set<DataType>>*ptr,const set<DataType>&)  ;

    template<typename DataType>
    class prob_tree{
        //say sample space is shared among every p_node so they carry only the pointer or its address
        //so no excess copying of sample space
        set<DataType>*sample_space_ptr;
        bst<set<DataType>>tree ;

        //void replace_node( node<DataType>*ptr,const set<DataType>&) ;
        //only way to insert/do anything is through euler tour
        void euler_tour(node<set<DataType>>*ptr,bool (*func_ptr)(node<set<DataType>>*,const set<DataType>&)
        ,const set<DataType>&target_set,bool&search_response);

        public:
            prob_tree(void)  ;
            prob_tree(const set<DataType>&sample_space) ;
            ~prob_tree(void) ;
            //if the set has no intersection with original sample space
            //its not inserted same for the set_arr aswell
            prob_tree(const set<DataType>&sample_space,const set<DataType>*set_arr,int size);

            bool insert(const set<DataType>&) ;

            bool search(const set<DataType>&) ;

            void print(void) const ;
            void move(void)const;
            //bool del(const set<DataType>&) ;
            //bool replace(const set<DataType>&) ;



    };


/*

    template typename <set_DataType>
    class prob_tree{
        bst<set<set_DataType>>tree ;

        public:
            prob_tree(set*events,int size);
            void interface(void) ;

    }

*/
    //you can cin and cout a set easily
    /*
    in cin first you enter the size or number of elements you are  going to insert
    then insert them
    */

#endif
