#include "bst.h"

    template<typename DataType>
    node<DataType>::node(void) {
        counter = 0;
        left = NULL;
        right = NULL;
    }
    template<typename DataType>
    node<DataType>::node(const DataType& _d,const uint32_t _c) {
        data = _d   ;
        counter= _c ;        
        left = NULL;
        right = NULL;
    }    

    template<typename DataType>
    bst<DataType>::bst(void) {
        root = NULL ;
        nodes_count = 0 ; 
        total_count =  0 ; 
    }        
    template<typename DataType>
    bst<DataType>::~bst(void) {
        remove_tree_tour(root) ; 
        root = NULL;
        nodes_count=0;
        total_count= 0;
    }
    template<typename DataType>
    bool bst<DataType>::insert(const DataType &d,const uint32_t counter ){
        if(counter!=0){
            if(root==NULL){
                root = new node(d,counter) ; 
                nodes_count =1 ; 
                total_count+=counter ; 
                return 1 ;
            }
            else{
                node<DataType>*ptr = root ; 
                while(1){
                    if(ptr->data==d){
                        ptr->counter +=counter;
                        total_count+=counter; 
                        return 1; 
                    }
                    else if(d<ptr->data){
                        if(ptr->left){
                            ptr=ptr->left;
                        }
                        else{
                            ptr->left = new node(d,counter) ;
                            total_count +=counter; 
                            nodes_count+=1 ; 
                            return 1 ; 
                        }
                    }
                    else{
                        if(ptr->right){
                            ptr=ptr->right;
                        }
                        else{
                            ptr->right = new node(d,counter) ;
                            total_count +=counter; 
                            nodes_count+=1 ; 
                            return 1 ; 
                        }
                    }

                }
            }
        }
        return 0 ;
    }         
    template<typename DataType>
    node<DataType>*bst<DataType>::get_node(const DataType& data)const {
        if(root){
            node<DataType>*ptr =root ; 
            while(1){
                if(ptr->data==data){
                    return ptr;
                }
                else if(data<ptr->data){
                    if(ptr->left){
                        ptr=ptr->left;
                    }
                    else{
                        return NULL;
                    }
                }
                else{
                    if(ptr->right){
                        ptr=ptr->right;
                    }
                    else{
                        return NULL;
                    }
                }
            }
        }
        return NULL;
    }
    template<typename DataType>
    bool bst<DataType>::adjust_count(const DataType& d,const uint32_t &new_counter) {
        node<DataType>*ptr = get_node(d);
        if(ptr){
            if(new_counter!=0){
                total_count-=ptr->counter; 
                total_count+=new_counter ; 
                ptr->counter=new_counter ; 
            }
            else{
                root = remove_node_tour(d,root);
            }
            return 1 ; 
        }
        return 0 ; 
    }
    template<typename DataType>
    bool bst<DataType>::search(const DataType &d)const  {
        return (get_node(d)!=NULL);
    } 
    template<typename DataType>
    bool bst<DataType>::remove(const DataType &d) {
        if(get_node(d)){
            root = remove_node_tour(d,root)  ;
            return 1; 
        }
        return 0;
    }
    template<typename DataType>
    bool bst<DataType>::remove_tree(void){
        if(root){        
            remove_tree_tour(root) ; 
            return 1; 
        }
        return 0;
    } 
    template<typename DataType>
    bool bst<DataType>:: remove_tree_tour(node<DataType>*ptr){
        if(ptr){
            if(ptr->left){
                remove_tree_tour(ptr->left) ; 
                ptr->left=NULL;
            }
            if(ptr->right){
                remove_tree_tour(ptr->right) ;                 
                ptr->right=NULL;
            }
            if(ptr==root){
                root=NULL;
            }            
            nodes_count-- ; 
            total_count-=ptr->counter;
            delete ptr;
            ptr=NULL;

            return 1 ;
        }
        return 0;
    }

    template<typename DataType>
    node<DataType>* bst<DataType>::remove_node_tour(const DataType& data,node<DataType>*ptr) {
        if(root){ 
            if(data<ptr->data){
                if(ptr->left){
                    ptr->left=remove_node_tour(data,ptr->left);
                }
                return ptr ; 
            }
            if(data>ptr->data){
                if(ptr->right){                 
                    ptr->right=remove_node_tour(data,ptr->right);
                }
                return ptr ; 
            }
            else{
                if(ptr->left==NULL&&ptr->right==NULL){
                    nodes_count-- ; 
                    total_count-=ptr->counter ; 
                    delete ptr;
                    ptr =NULL;             
                    return NULL;
                }
                else if(ptr->right==NULL){
                    nodes_count-- ; 
                    total_count-=ptr->counter ; 
                    node<DataType>*temp = ptr->left; 
                    delete ptr;
                    ptr = NULL;        
                    return temp;                    
                }
                else if(ptr->left==NULL){       
                    nodes_count-- ; 
                    total_count-=ptr->counter ;             
                    node<DataType>*temp = ptr->right; 
                    delete ptr;                 
                    ptr = NULL;                     
                    return temp;  
                }
                else{
                    node<DataType>*max_at_left = ptr->left ;
                    while(max_at_left->right){
                        max_at_left=max_at_left->right;
                    }
                    ptr->data = max_at_left->data;
                    ptr->counter= max_at_left->counter;
                    ptr->left=remove_node_tour(ptr->data,ptr->left) ; 
                    return ptr ;
                }
            }
        }
    }
    template<typename DataType>
    uint32_t bst<DataType>::get_nodes_count(void) const{
        return nodes_count; 
    }    
    template<typename DataType>
    uint32_t bst<DataType>::get_total_count(void) const{
        return total_count; 
    }
    template<typename DataType>
    void bst<DataType>::display(const node<DataType>*ptr)const{
        if(ptr==NULL&&root){
            ptr=root;  
        }
        if(ptr){
            if(ptr->left){                
                display(ptr->left) ;                 
            }
            std::cout<<"("<<ptr->data<<","<<ptr->counter<<") ";
            if(ptr->right) {                 

                display(ptr->right) ; 
            }
        }
    }
    template<typename DataType>
    void bst<DataType>:: collect_tree_vector_tour(const node<DataType>* ptr,node<DataType>**tree_vector,uint32_t &current_position)const{
        if(ptr){
            if(ptr->left){
                collect_tree_vector_tour(ptr->left,tree_vector,current_position) ;
            }
            tree_vector[current_position] = ptr;
            current_position++ ; 
            if(ptr->right){
                collect_tree_vector_tour(ptr->right,tree_vector,current_position)  ;
            }
        }
    }    
    template<typename DataType>
    node<DataType>* bst<DataType>::balance_tour(const node<DataType>**tree_vector,const uint32_t &beg ,const uint32_t &end ) const{
        if(beg<=end){
            uint32_t mid = (beg+end)/2;
            node<DataType>*ptr = new node(tree_vector[mid]->data,tree_vector[mid]->counter) ; 
            //so that overflow doesn't happen 
            if(mid!=0){
                ptr->left = balance_tour(tree_vector,beg,mid-1);
            }
            ptr->right = balance_tour(tree_vector,mid+1,end);
            return ptr ; 
        }
        return NULL; 
    }
    template<typename DataType>
    bool bst<DataType>::balance(void) {
        if(root){
            node<DataType>** tree_vector  = new node<DataType>*[nodes_count] ;
            uint32_t position = 0;
            collect_tree_vector_tour(root,tree_vector,position);
            position = 0;
            node<DataType>*temp_root = balance_tour(tree_vector,position,nodes_count-1);
            delete[]tree_vector;
            tree_vector=NULL ;  
            remove_tree_tour(root) ;
            root =temp_root ; 
            return 1 ;
        }
        return 0 ; 
    }
    template<typename DataType>
    int64_t bst<DataType>::height_tour(const node<DataType>*ptr)  const{
        if(ptr){
            int64_t left_height = 0 ;
            int64_t right_height = 0;
            left_height += height_tour(ptr->left);
            right_height += height_tour(ptr->right);
            return (left_height>right_height)?left_height:right_height +1; 
        }
        else{
            return -1;
        }
    }    
    
    template<typename DataType>
    int64_t bst<DataType>::height(void)  const {
        return height_tour(root) ; 
    }
    template<typename DataType>
    node<DataType>*bst<DataType>::copy_tree(const node<DataType>*ptr) {
        if(ptr){
            node<DataType>*ret_root = new node(ptr->data,ptr->counter) ;
            if(ptr->left){
                ret_root->left =copy_tree(ptr->left) ;
            }
            if(ptr->right){
                ret_root->right = copy_tree(ptr->right) ;
            }
            return ret_root ;
        }
        return NULL ;
    }    
    template<typename DataType>
    bst<DataType>::bst(const bst<DataType>&src) {
        remove_tree() ;
        root =copy_tree(src.root) ;
        nodes_count = src.nodes_count ;
        total_count = src.total_count;
    }
    template<typename DataType>
    bst<DataType>&bst<DataType>::operator=(const bst<DataType>&src) {
        remove_tree() ;
        root =copy_tree(src.root) ;
        nodes_count = src.nodes_count ;
        total_count = src.total_count;
        return *this;
    }        
    template<typename DataType>
    node<DataType>*bst<DataType>::max(void)const {
        if(root){
            node<DataType>*max_ptr = root ; 
            while(max_ptr->right){
                max_ptr=max_ptr->right ; 
            }
            return max_ptr ; 
        }
        return NULL; 
    }

    template<typename DataType>
    node<DataType>*bst<DataType>::min(void)const {
       if(root){
            node<DataType>*min_ptr = root ; 
            while(min_ptr->left){
                min_ptr=min_ptr->left ; 
            }
            return min_ptr ;
        }
        return NULL; 
    }
