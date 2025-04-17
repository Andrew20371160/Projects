#ifndef _bst_h_
#define _bst_h_
#include <stdint.h>
#include <iostream>
template<typename DataType> 
class node{
    template<typename T> friend class bst;      
    template<typename T> friend class multiset;    
  
    private :
        DataType data  ;     
        uint32_t counter ; 
        node<DataType>*left ; 
        node<DataType>*right ;
    public:
        node(void) ; 
        node(const DataType&,const uint32_t counter= 1) ;
        bool update_parent_link(node<DataType>*dest) ; 
};

template <typename DataType>
class bst{
    private :
        template<typename T2> friend class multiset;    
        node<DataType>*root ;
        //# of unique elements
        uint32_t nodes_count ;
        //total number of elements
        uint32_t total_count ;
        bool remove_tree_tour(node<DataType>*);
        node<DataType>*get_node(const DataType&)const;
        node<DataType>*remove_node_tour(const DataType&,node<DataType>*);
        void collect_tree_vector_tour(const node<DataType>* ,node<DataType>**tree_vector,uint32_t &current_position)const;
        node<DataType>*balance_tour(const node<DataType>**tree_vector,const uint32_t &start ,const uint32_t& end ) const;        
        int64_t height_tour(const node<DataType>*ptr) const;
        node<DataType>*copy_tree(const node<DataType>*) ;
        node<DataType>*max(void)const ;
        node<DataType>*min(void) const;
        
    public :
        bst(void) ;
        bst(const bst<DataType>&) ;
        bst<DataType>&operator=(const bst<DataType>&) ; 
        ~bst(void) ;
        bool insert(const DataType&,const uint32_t counter =1 );
        bool adjust_count(const DataType&,const uint32_t &new_counter) ;
        bool search(const DataType&)const ; 
        bool remove(const DataType&) ; 
        bool remove_tree(void); 
        uint32_t get_nodes_count(void) const;
        uint32_t get_total_count(void) const;
        void display(const node<DataType>*ptr=NULL)const;
        bool balance(void) ;
        int64_t height(void)  const;


};
    #include "bst.tpp"


#endif
