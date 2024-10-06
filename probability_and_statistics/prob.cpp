    #include "prob.h"


    template<typename T>
    std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
        os << "[";
        if (!vec.empty()) {
            os << vec[0];
            for (int i = 1; i < vec.size(); i++)
                os << ", " << vec[i];
        }
        os << "]";
        return os;
    }

    long long factorial(const int &num){
        long long res = 1 ;
        for(int i = 0  ; i<num;i++){
            res*=(num-i);
        }
        return res  ;
    }

    int choose(const int&n,const int&k){
        if(n>=k)
            return factorial(n)/(factorial(n-k)*factorial(k)) ;
        return 0;
    }


template<typename DataType>
void set<DataType>::set_function_ptr(bool (set<DataType>::*ptr)(const node<DataType>*ptr,const bst<DataType>&,long long &, const node<DataType>**)const)const{
    func_ptr_c = ptr ;
}

template<typename DataType>
void set<DataType>::set_function_ptr(bool (set<DataType>::*ptr)( node<DataType>*ptr, bst<DataType>&,long long &, node<DataType>**)){
    func_ptr = ptr ;
}
    /*
    prints a set in a visible way->{1,5,53,56,155} or {} for empty sets
    */
    template<typename DataType>
    ostream& operator<<(ostream& os, const set<DataType>& obj) {

        string output= "{";
        output.append(obj.to_string());
        if(output=="{"){
            //never was filled
            output = "{}"  ;
        }
        else{
            output[output.size()-1]='}' ;
        }
        os<<output ;
        return os ;
    }

    //turns a set into a string
    //for printing purpose
    template<typename DataType>
    string set<DataType>::to_string(void)const{
        string str ="" ;
        tree.to_string(str) ;
        return str  ;
    }
    /*
    in cin first you enter the size or number of elements you are  going to insert
    then insert them
    */
    template<typename DataType>
    istream& operator>>(istream& is, set<DataType>& obj){
            int n;
            is>>n;
            DataType data ;
            for(int j= 0 ;j<obj.size();j++){
                is>>data ;
                obj.insert(data) ;
            }
        return is ;
    }



    //empty bst
    template<typename DataType>
    set<DataType>::set(void){
        tree = bst<DataType>() ;
    }

    /*
    if the array inserted into the set is both sorted and contains duplicates this may cause error
    since the array is filled in O(N) apporach to maintain property of a bst
    //check out fill_sorted in bst.tpp for more context
    so make sure to use remove_duplicates(void) if calculations doesn't match what you expected
    */
    template<typename DataType>
    set<DataType>::set(DataType*_arr,int _size){
        if(_arr&&_size>0){
            tree= bst<DataType>(_arr,_size);
        }
        else{
            tree=bst<DataType>() ;
        }
    }


    /*
    if the vector inserted into the set is both sorted and contains duplicates this may cause errors
    since the array is filled in O(N) apporach to maintain property of a bst
    //check out fill_sorted in bst.tpp for more context
    so make sure to use remove_duplicates(void) if calculations doesn't match what you expected
    */
    template<typename DataType>
    set<DataType>::set(vector<DataType>&_arr){
        if(_arr.size()>0){
            tree =bst<DataType>(_arr) ;
        }
        else{
            tree = bst<DataType>() ;
        }
    }

    //copy constructor
    template<typename DataType>
    set<DataType>::set(const set&src){
        tree= src.tree ;
    }
    //assignment operator
    template<typename DataType>
    void set<DataType>::operator=(const set&src) {
        tree = src.tree ;
    }
    //destructor of the set
    //though bst is deleted anyway but just in case :)
    template<typename DataType>
    set<DataType>::~set(void){

        tree.remove_tree() ;

    }
    //insert an element into the set
    template<typename DataType>
    bool set<DataType>::insert(DataType data,int count ){
        if(count>0)
            return tree.insert(data,count) ;
        return 0  ;
    }
    //insert an array into the set

    template<typename DataType>
    bool set<DataType>::insert(DataType *_arr,int n) {
        if(n>0){
                /*
    if tree is empty or set is empty it treats at as a constructor for the bst
    */
            if(tree.get_size()==0){
                tree =bst<DataType>(_arr,n) ;
            }
            else{
                //else insert each element
                for(int i = 0 ; i<n;i++){
                    tree.insert(_arr[i]);
                }
            }
            return 1 ;
        }
        return 0  ;
    }


    template<typename DataType>
    bool set<DataType>::search(const DataType&data)const {
        return tree.search(data) ;
    }
    //remove an element from the set
    template<typename DataType>
    bool set<DataType>::remove(const DataType&data){
        return tree.remove(data) ;
     }

    //get number of elements in the set
    template<typename DataType>
    long long set<DataType>::size(void)const{
        return tree.get_size();
    }

    //get number of elements in the set
    template<typename DataType>
    long long set<DataType>::nodes_count(void)const{
        return tree.get_nodes_count();
    }

    /*
    euler tour section
    */
    template<typename DataType>
    bool set<DataType>::fill_for_intersection(const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter, const node<DataType>**match_vec)const{
        if(other_tree.search(ptr->data)){
            match_vec[counter] = (ptr->counter<=other_tree.traverser->counter)?ptr:other_tree.traverser ;
            counter++;
            return 1 ;
        }
        return 0 ;
    }

    template<typename DataType>
    bool set<DataType>::fill_for_intersection( node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec){
        if(other_tree.search(ptr->data)){
            match_vec[counter] = (ptr->counter<=other_tree.traverser->counter)?ptr:other_tree.traverser ;
            counter++;
            return 1 ;
        }
        return 0 ;
    }

    template<typename DataType>
    bool set<DataType>::fill_for_union(const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter, const node<DataType>**match_vec)const{
        if(!other_tree.search(ptr->data)){
            match_vec[counter] = ptr;
        }
        else{
            match_vec[counter] = (ptr->counter > other_tree.traverser->counter)?ptr:other_tree.traverser;
        }
        counter++;

        return 1 ;
    }

    template<typename DataType>
    bool set<DataType>::fill_for_union( node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec){
        if(!other_tree.search(ptr->data)){
            match_vec[counter] = ptr;
        }
        else{
            match_vec[counter] = (ptr->counter>other_tree.traverser->counter)?ptr:other_tree.traverser;
        }
        counter++;

        return 1 ;
    }

    template<typename DataType>
    bool set<DataType>::fill_for_unique(const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter, const node<DataType>**match_vec)const{
        if(!other_tree.search(ptr->data)){
            match_vec[counter] = ptr;
            counter++;
            return 1 ;
        }
        return 0 ;
    }
    template<typename DataType>
    bool set<DataType>::fill_for_unique( node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec){
        if(!other_tree.search(ptr->data)){
            match_vec[counter] = ptr;
            counter++;
            return 1 ;
        }
        return 0 ;
    }


    template<typename DataType>
    bool set<DataType>::fill_for_diff(const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter, const node<DataType>**match_vec)const{
        if(!other_tree.search(ptr->data)){
            match_vec[counter]= ptr ;
            counter++ ;
            return 1 ;
        }
        else{
            //if data exists in both sets get difference from sample space
            if(ptr->counter>other_tree.traverser->counter){
                match_vec[counter] = ptr;
                counter++;
                return 1 ;
            }
        }
        return 0 ;
    }
    template<typename DataType>
    bool set<DataType>::count_for_intersection(const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter,const  node<DataType>**match_vec)const{
         if(other_tree.search(ptr->data)){
            counter +=min(other_tree.traverser->counter,ptr->counter);
            return 1;
         }
         return 0;
    }

    template<typename DataType>
    bool set<DataType>::count_for_draw_no_replace(const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter,const node<DataType>**match_vec)const{
         if(other_tree.search(ptr->data)){
            counter *= choose(other_tree.traverser->counter,ptr->counter);
            return 1;
         }
         else{
            counter =  0  ;
         }
         return 0;
    }

    template<typename DataType>
    bool set<DataType>::count_for_draw_replace(const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter,const node<DataType>**match_vec)const{
         if(other_tree.search(ptr->data)){
            counter *= pow(other_tree.traverser->counter,ptr->counter);
            return 1;
         }
         else{
            counter =  0  ;
         }
         return 0;
    }

    template<typename DataType>
    bool set<DataType>::count_for_draw_replace( node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec){
         if(other_tree.search(ptr->data)){
            counter *= pow(other_tree.traverser->counter,ptr->counter);
            return 1;
         }
         else{
            counter =  0  ;
         }
         return 0;
    }
    template<typename DataType>
    bool set<DataType>::exist(const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter,const node<DataType>**match_vec)const{
        return other_tree.search(ptr->data) ;
    }

    template<typename DataType>
    bool set<DataType>::not_exist(const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter,const node<DataType>**match_vec)const{
        return !other_tree.search(ptr->data) ;
    }

    template<typename DataType>
    bool set<DataType>::always_exist(const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter,const node<DataType>**match_vec)const{
         match_vec[counter] = ptr ;
         counter++;
         return 1 ;
    }


    template<typename DataType>
    bool set<DataType>::fill_for_diff(node<DataType>*ptr, bst<DataType>&other_tree,long long &counter,node<DataType>**match_vec){
        if(!other_tree.search(ptr->data)){
            match_vec[counter]= ptr ;
            counter++ ;
            return 1 ;
        }
        else{
            //if data exists in both sets get difference from sample space
            if(ptr->counter>other_tree.traverser->counter){
                match_vec[counter] = ptr;
                counter++;
                return 1 ;
            }
        }
        return 0 ;
    }

    template<typename DataType>
    bool set<DataType>::count_for_intersection( node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec){
         if(other_tree.search(ptr->data)){
            counter +=min(other_tree.traverser->counter,ptr->counter);
            return 1;
         }
         return 0;
    }

    template<typename DataType>
    bool set<DataType>::count_for_draw_no_replace( node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec){
         if(other_tree.search(ptr->data)){
            counter *= choose(other_tree.traverser->counter,ptr->counter);
            return 1;
         }
         else{
            counter =  0  ;
         }
         return 0;
    }


    template<typename DataType>
    bool set<DataType>::count_for_avg( const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter,const node<DataType>**match_vec)const{
         counter+=ptr->data*ptr->counter;
         return 1 ;
    }

    template<typename DataType>
    bool set<DataType>::count_for_avg( node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec){
         counter+=ptr->data*ptr->counter;
         return 1 ;
    }

    template<typename DataType>
    bool set<DataType>::count_for_var( const node<DataType>*ptr,const bst<DataType>&other_tree,long long &counter,const node<DataType>**match_vec)const{
         counter+=ptr->data*ptr->data*ptr->counter;
         return 1 ;
    }

    template<typename DataType>
    bool set<DataType>::count_for_var( node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec){
         counter+=ptr->data*ptr->data*ptr->counter;
         return 1 ;
    }



    template<typename DataType>
    bool set<DataType>::exist( node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec){
        return other_tree.search(ptr->data) ;
    }

    template<typename DataType>
    bool set<DataType>::not_exist( node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec){
        return !other_tree.search(ptr->data) ;
    }


    template<typename DataType>
    bool set<DataType>::always_exist( node<DataType>*ptr, bst<DataType>&other_tree,long long &counter, node<DataType>**match_vec){
         match_vec[counter] = ptr ;
         counter++;
         return 1 ;
    }
    /*
    this function fills vector/increase counter based on a conditino between phantom and caller
    if data in phantom exists in data in caller
    if data in phantom not exist
    etc etc
    so if we calculate intersection we push every element that's in phantom and in other_tree
    into the match_vec
    using same logic this function can be used to calculate any property needed
    */
    template<typename DataType>
    void set<DataType>::euler_tour(const node<DataType>*ptr,const bst<DataType>&other_tree,
     const node<DataType>**match_vec,long long &match_counter)const{
        if(ptr==NULL){
            ptr= tree.root ;
        }
        if(ptr){
            if(ptr->left){
                euler_tour(ptr->left,other_tree,match_vec,match_counter) ;
            }

            (this->*func_ptr_c)(ptr,other_tree,match_counter,match_vec);

            if(ptr->right){
                euler_tour(ptr->right,other_tree,match_vec,match_counter) ;
            }
        }
    }

    template<typename DataType>
    void set<DataType>::euler_tour( node<DataType>*ptr, bst<DataType>&other_tree,
      node<DataType>**match_vec,long long &match_counter){
        if(ptr==NULL){
            ptr= tree.root ;
        }
        if(ptr){
            if(ptr->left){
                euler_tour(ptr->left,other_tree,match_vec,match_counter) ;
            }

            (this->*func_ptr)(ptr,other_tree,match_counter,match_vec);

            if(ptr->right){
                euler_tour(ptr->right,other_tree,match_vec,match_counter) ;
            }
        }
    }

/*
    template<typename DataType>
    void set<DataType>::euler_tour(node<DataType>*ptr,const bst<DataType>&other_tree,
        long long& match_counter,bool (*func_ptr)(const DataType&,const bst<DataType>&))const{
        if(ptr==NULL){
            ptr= tree.root ;
        }
        if(ptr){
            if(ptr->left){
                euler_tour(ptr->left,other_tree,match_counter,func_ptr) ;
            }
            if(func_ptr(ptr->data,other_tree)){
                match_counter++ ;
            }
            if(ptr->right){
                euler_tour(ptr->right,other_tree,match_counter,func_ptr) ;
            }
        }
    }

*/
    /*
    all the following functions are applications of euler tour
    */
    //returns intersection between caller and src
    template<typename DataType>
    set<DataType> set<DataType>::intersect(const set&src)const{
        //if both aren't phi or empty sets
        if(tree.get_size()&&src.size()){
            set_function_ptr(fill_for_intersection);

            //vector to store elements in both sets
            //it has size of smaller set
            const node<DataType> **v = new const node<DataType>*[min(src.nodes_count(),nodes_count())];
            //number of elements in both sets
            long long final_size =0 ;
            //get elements that are in phantom and src and put it into v
            euler_tour(NULL,src.tree,v,final_size) ;
            //create the set
            set<DataType>s ;

            s.tree=bst<DataType>(v,final_size) ;

            //remove allocated memory
            delete[]v ;
            v = NULL;

            return s ;
        }
        //else its an empty set
        return set();
    }

    template<typename DataType>
    void merge(const vector<DataType>&left_vec,const vector<DataType>&right_vec,vector<DataType>&dest){
            long long left = 0 , right  =0 ,counter=0;

                while(left<left_vec.size()&&right<right_vec.size()){
                    if(left_vec[left]<=right_vec[right]){
                        //check that it's a new element and not repeated
                            dest[counter++] = left_vec[left] ;
                            left++;
                    }
                    else if(left_vec[left]>right_vec[right]){
                        dest[counter++] = right_vec[right] ;
                        right++;
                    }

                }
            //fill rest
            while(left<left_vec.size()){
                dest[counter++] = left_vec[left];
                left ++;
            }

            while(right<right_vec.size()){
                    dest[counter++] = right_vec[right];
                right ++;
            }

    }

    //returns union of caller and src
    template<typename DataType>
    set<DataType> set<DataType>::unite(const set&src)const{
        //if both exist
        if(tree.nodes_count()&&src.nodes_count()){
            set_function_ptr(fill_for_union);

            //assuming all elements of phantom are unique
            const node<DataType>**unique_in_phantom=new const node<DataType>*[max(src.nodes_count(),nodes_count())] ;
            //counter of uniqie elements that are in phantom and not in src
            long long  counter = 0;
            //vec is filled with data that's in phantom and not in src
            //and with data that's in both
            euler_tour(NULL,src.tree,unique_in_phantom,counter) ;
            //copy of the src set
            set<DataType> ret_set ;

            ret_set.tree=bst<DataType>(unique_in_phantom,counter) ;

            counter= 0;

            src.set_function_ptr(fill_for_union);

            src.euler_tour(NULL,tree,unique_in_phantom,counter) ;

            //in that copy insert rest of elements that are unique in the phantom
            for(long long i = 0 ; i<counter;i++){
                //if data not found in phantom
                if(!ret_set.search(unique_in_phantom[i]->data))
                    ret_set.insert(unique_in_phantom[i]->data,unique_in_phantom[i]->counter);
            }

            //delete allocated memory
            delete[]unique_in_phantom ;
            unique_in_phantom = NULL;

            return ret_set;
        }
        //if one of them is empty set return the other one
        //if both are empty same thing applies
        else if(tree.get_size()){
            return *this ;
        }
        else{
            return src ;
        }
    }

    //returns true if sample-space(phantom contains src set)
    template<typename DataType>
    bool set<DataType>::contain(const set&src)const{
        if(tree.get_size()&&src.size()){
            set_function_ptr(count_for_intersection);
            long long counter = 0 ;
            //search if every node in src is in the phantom(sample-space)
            //if exist increase the counter
            src.set_function_ptr(count_for_intersection);
            src.euler_tour(NULL,tree,NULL,counter) ;

            return counter>=src.size();
        }

        return tree.get_size()>=src.size() ;
    }
    /*
    in the sample-space (phantom ) calculate complement of src set
    */
    template<typename DataType>
    set<DataType> set<DataType>::comp(const set &src)const{
        //if sample space contains src then we get its complement
        //else result doesn't make sense
        if(contain(src)){
            if(src.size()<size()){
                set_function_ptr(fill_for_diff);
                const node<DataType>**vec = new const node<DataType>*[nodes_count()];
                long long counter  = 0 ;
                //fill with data that's in the sample space (phantom)and not in src
                euler_tour(NULL,src.tree,vec,counter) ;
                set s;
                s.tree=bst<DataType>(vec,counter);

                //delete the array
                for(long long i  = 0 ;  i<counter; i++){
                    //other_tree.traverser->counter-ptr->counter
                    if(src.search(vec[i]->data)&&s.search(vec[i]->data)){
                        s.tree.traverser->counter -=src.tree.traverser->counter;
                    }
                }
                delete[]vec;
                vec =NULL ;
                return s ;
            }
        }
        return set(NULL,0)  ;
    }

    template<typename DataType>
    bool set<DataType>::not_contain(const set&src)const{
        return !contain(src);
    }
    //retunrs true if both sets contain same elements
    template<typename DataType>
    bool set<DataType>::equal(const set &src)const{
        if(src.size()==size()){
            return contain(src);
        }
        return 0 ;
    }
    //turns a set into empty set (phi)
    template<typename DataType>
    bool set<DataType>::clear(void){
        tree.remove_tree();
        return true ;
    }

    //returns true if set is empty
    template<typename DataType>
    bool set<DataType>::empty(void)const{
        return size()==0 ;
    }

    /*
    probability of an event (src) to occur in sample space (phantom)
    */
    template<typename DataType>
    double set<DataType>::prob_draw_no_replace(const set&src)const{
        if(size()>=src.size()){
            long long counter =1;
            //count number of elements that are in both
            //set_function_ptr(count_for_prob_set);
            src.set_function_ptr(count_for_draw_no_replace);
            src.euler_tour(NULL,tree,NULL,counter);

            return static_cast<double>(counter)/static_cast<double>(choose(size(),src.size())) ;
        }
        return 0 ;
    }

    template<typename DataType>
    double set<DataType>::prob_draw_replace(const set&src)const{
        if(size()>=src.size()){
            long long counter =1;
            //count number of elements that are in both
            //set_function_ptr(count_for_prob_set);
            src.set_function_ptr(count_for_draw_replace);
            src.euler_tour(NULL,tree,NULL,counter);

            return static_cast<double>(counter)/static_cast<double>(pow(size(),src.size())) ;
        }
        return 0 ;
    }


    template<typename DataType>
    double set<DataType>::prob(const set&src)const{
        if(contain(src)){
            return static_cast<double>(src.size())/static_cast<double>(size()) ;
        }
        return 0 ;
    }

    /*
    probability of an event (src) to occur in sample space (phantom)
    knowing that event condition occurred
    */
    template<typename DataType>
    double set<DataType>::prob_cond(const set&src,const set&condition)const{
        if(contain(src)){
            double p_cond = prob(condition) ;
            if(p_cond>0){
                return prob(condition.intersect(src))/p_cond;
           }
            cout<<"\nConditioning event can't be drawn from the sample-space\n" ;
        }
        return 0 ;
    }
    /*
        p(src|condition) = p(src intersect condition) /p(condition)
        p(condition|src) = p(src intersect condition) /p(src)
        p(src intersect condition) =p(src|condition) *p(condition) = p(condition|src)*p(src)
        p(condition|src) = p(src|condition)*p(condition)/p(src)
    */
    template<typename DataType>
    double set<DataType>::bayes(const set&src,const set&condition)const{

        return (prob_cond(src,condition)*prob(condition)) /prob(src)  ;

    }

    /*
    in sample space (phantom ) check independence between s1 and s2
    */
    template<typename DataType>
    bool set<DataType>::independence(const set&s1,const set&s2)const{
        return prob(s1)*prob(s2)==prob(s1.intersect(s2));
    }

    /*
    in sample space(phantom ) check independence of events s1,s2,......sn
    */
    template<typename DataType>
    bool set<DataType>::independence(const set*set_arr,int n)const{
        double res =1;
        for(int i =0 ; i<n;i++){
            res *=prob(set_arr[i]) ;
        }
        return res==prob_intersect(set_arr,n) ;

    }
        /*
    in sample space(phantom ) check independence of events s1,s2,......sn
    */
    template<typename DataType>
    bool set<DataType>::independence(const vector<set<DataType>>&set_arr)const{
        double res =1;
        for(int i =0 ; i<set_arr.size();i++){
            res *=prob(set_arr[i]) ;
        }
        return res==prob_intersect(set_arr) ;
    }
    //returns set of elements that are in phantom and not in src
    //different than comp that phantom doesn't have to contain src set
    //same when phantom is the sample space containing src
    template<typename DataType>
    set<DataType> set<DataType>::diff(const set&src)const {
        if(src.size()&&size()){
            set_function_ptr(fill_for_diff);
            const node<DataType>**vec = new const node<DataType>*[nodes_count()];
            long long counter  = 0 ;
            //fill with data that's in the sample space (phantom)and not in src
            euler_tour(NULL,src.tree,vec,counter) ;
            set s;
            s.tree=bst<DataType>(vec,counter);

            //delete the array
            for(long long i  = 0 ;  i<counter; i++){
                //other_tree.traverser->counter-ptr->counter
                if(src.search(vec[i]->data)&&s.search(vec[i]->data)){
                    s.tree.traverser->counter -=src.tree.traverser->counter;
                }
            }
            delete[]vec;
            vec =NULL ;
            return s ;
        }
        if(size()){
            return *this  ;
        }
        return set(NULL,0)  ;
    }
    /*
    retunrs p(s1 U s2 U s3 ........U sN)
    in the sample space (phantom)
    */
    template<typename DataType>
    double set<DataType>::prob_unite(const set*set_arr,int n)const{
        set s =set_arr[0];
        for(int i =1; i<n; i++){
            s= s.unite(set_arr[i]);
        }
        return prob(s);
    }
    /*
    retunrs p(s1 intersects s2 intersects s3 ........intersects sN)
    in the sample space (phantom)
    */
    template<typename DataType>
    double  set<DataType>::prob_intersect(const set*set_arr,int n)const{
        set s =set_arr[0];
        for(int i =1; i<n; i++){
            s= s.intersect(set_arr[i]);
        }
        return prob(s);
    }
    /*
    retunrs p(s1 intersects s2 intersects s3 ........intersects sN)
    in the sample space (phantom)
    */
    template<typename DataType>
    double  set<DataType>::prob_intersect(const vector<set<DataType>>&set_arr)const{
        set s =set_arr[0];
        for(int i =1; i<set_arr.size(); i++){
            s= s.intersect(set_arr[i]);
        }
        return prob(s);
    }
    /*
    replaces an element with a new element
    */
    template<typename DataType>
    bool set<DataType>::replace(const DataType&old_data,const DataType&new_data){
        if(tree.search(old_data)){
            int count = tree.traverser->counter ;
            tree.remove(old_data) ;
            return tree.insert(new_data,count);
        }
        return false ;
    }
    /*
    update the count of an element or an instance with a new count
    if zero element is deleted
    */
    template<typename DataType>
    bool set<DataType>::update_count(const DataType&data,const int &count){
        if(count>=0){
            if(count==0){
                return tree.remove(data) ;
            }
            else{
                if(tree.search(data)){
                    int old_count=  tree.traverser->counter;
                    tree.size-=old_count ;
                    tree.size+=count  ;
                    tree.traverser->counter = count ;
                    return 1;
                }
            }
        }
        return 0 ;
    }

    //removes duplicates of an element
    template<typename DataType>
    bool set<DataType>::remove_duplicates(const DataType&data){
         if(tree.search(data)){
            if(tree.traverser->counter>1){
                tree.size -=tree.traverser->counter ;
                tree.size++ ;
                tree.traverser->counter =1 ;
            }
            return  1;
         }
         return 0 ;
    }

    //remove all duplicates of every element
    template<typename DataType>
    bool set<DataType>::remove_duplicates(void){
        if(size()){
            set_function_ptr(always_exist);
            node<DataType>**arr =new  node<DataType>*[nodes_count()];
            long long counter=0;
            //for each element in phantom push it into the array
            //don't search = always_exist
            euler_tour(NULL,tree,arr,counter);
            for(long long  i = 0 ; i<counter; i++){
                tree.size-=arr[i]->counter ;
                tree.size++;
                arr[i]->counter=1;
            }
            delete[]arr;
            arr= NULL;
            return 1;
        }
        return 0  ;
    }

    template<typename DataType>
    double set<DataType>::average(void)const {
        long long counter= 0 ;
        if(size()){
            set_function_ptr(count_for_avg);
            euler_tour(NULL,tree,NULL,counter) ;
            return static_cast<double>(counter)/static_cast<double>(size());
        }
        return 0  ;
    }


    template<typename DataType>
    double set<DataType>::variance(void)const {
        long long counter= 0 ;
        if(size()){
            set_function_ptr(count_for_var);
            euler_tour(NULL,tree,NULL,counter) ;
            return static_cast<double>(counter)/static_cast<double>(size())-pow(average(),2);
        }
        return 0  ;
    }

    template<typename DataType>
    double set<DataType>::standard_deviation(void)const {
        long long counter= 0 ;
        if(size()){
            return sqrt(variance())  ;
        }
        return 0  ;
    }
    template<typename DataType>
    DataType set<DataType>::range(void)const {
        if(size()){
            return tree.get_max(tree.root)->data-tree.get_min(tree.root)->data ;
        }
        cout<<"can't have range for an empty set(Garbage value)" ;
        DataType garbage_value ;
        return garbage_value ;
    }

    template<typename DataType>
    double set<DataType>::average(const double*weights,const int &weights_size)const {

        if(size()&&weights_size>=nodes_count()){
            const node<DataType>**arr =new const node<DataType>*[nodes_count()];
            long long counter=0;
            //collect the tree then do the calculations
            set_function_ptr(always_exist);
            euler_tour(NULL,tree,arr,counter) ;
            double avg = 0 ;
            double total_weight = 0;
            for(long long i=0;i<counter;i++){
                avg+= static_cast<double>(arr[i]->data)*static_cast<double>(arr[i]->counter)*weights[i]  ;
                total_weight +=weights[i]*arr[i]->counter;
            }
            delete[] arr ;
            arr =NULL ;

            return avg/total_weight ;
        }
        return 0  ;
    }

    template<typename DataType>
    double set<DataType>::median(void)const{
        if(size()){

            const node<DataType>**arr =new  const node<DataType>*[nodes_count()];
            long long counter=0;
            //collect the tree then do the calculations
            set_function_ptr(always_exist);
            euler_tour(NULL,tree,arr,counter) ;

            double ret_med  ;

            long long i = 0  ;

            long long beg_window = 0;
            long long end_window = arr[0]->counter;

            while(i<counter){

                if(size()/2>=beg_window&&size()/2<=end_window){
                    if(size()&1==1){
                        if(end_window==size()/2){
                            ret_med = static_cast<double>(arr[i+1]->data) ;
                        }
                        else{
                           ret_med = static_cast<double>(arr[i]->data) ;
                        }
                    }
                    else{
                        ret_med =static_cast<double>(arr[i]->data);
                        if(end_window==size()/2){
                            ret_med+=static_cast<double>(arr[i+1]->data)  ;
                        }
                        else{
                            ret_med +=static_cast<double>(arr[i]->data) ;
                        }
                        ret_med =ret_med/2 ;
                    }
                    break ;
                }
                else{
                    i++;
                    beg_window+=arr[i-1]->counter;
                    end_window+=arr[i]->counter ;
                }
            }

            delete[]arr ; arr=NULL ;
            return ret_med;

        }
        DataType garbage_value ;
        cout<<"\ncan't have a median in an empty set (Garbage value)\n" ;
        return garbage_value ;
    }

    template<typename DataType>
    vector<double> set<DataType>::pmf(void)const{
        if(size()){
            const node<DataType>**arr =new  const node<DataType>*[nodes_count()];
            long long counter=0;
            //collect the tree then do the calculations
            set_function_ptr(always_exist);
            euler_tour(NULL,tree,arr,counter) ;

            vector<double>ret_vec(nodes_count()) ;

            for(long long i = 0 ; i <counter;i++){
                ret_vec[i]=(static_cast<double>(arr[i]->counter)/static_cast<double>(size())) ;
            }

            delete[]arr ; arr=NULL ;
            return ret_vec ;
        }
        return vector<double>(0)  ;
    }

    template<typename DataType>
    vector<double> set<DataType>::cmf(void)const{
        if(size()){
            vector<double>pmfvec = pmf() ;
            for(int i =1 ;i<pmfvec.size() ;i++){
                pmfvec[i] +=pmfvec[i-1] ;
            }
            return pmfvec ;
        }
        return vector<double>(0)   ;
    }

    //probability tree section

    template <typename DataType>
    p_node<DataType>::p_node(void) {
        set_ptr = NULL;
        sample_space_ptr = NULL;
    }

    template <typename DataType>
    p_node<DataType>::p_node(set<DataType>*&sample_space, const set<DataType>& _set) {
        sample_space_ptr=NULL;
        set_ptr=NULL ;
        set_ptr = new set<DataType>;
        *set_ptr = _set;
        sample_space_ptr = sample_space;
    }

    template <typename DataType>
    p_node<DataType>::p_node(const p_node<DataType>& src) {
        set_ptr = NULL;
        sample_space_ptr = NULL;
        if(src.set_ptr){
            set_ptr= new set<DataType>;
            *set_ptr= *src.set_ptr;
        }
        if(src.sample_space_ptr){
            sample_space_ptr = src.sample_space_ptr;
        }
    }

    template <typename DataType>
    p_node<DataType>::~p_node() {
        if(set_ptr){
            delete set_ptr;
            set_ptr=NULL;
        }
        //sample_space_ptr=NULL ;
    }

    template <typename DataType>
    void p_node<DataType>::operator=(const p_node<DataType>&src) {
        //if not same sample space there will be memory leaks
        //weird seg-faults
        if(sample_space_ptr==NULL&&src.sample_space_ptr!=NULL){
            sample_space_ptr = src.sample_space_ptr;
        }
        if(sample_space_ptr==src.sample_space_ptr){
            if(set_ptr){
                delete set_ptr;
                set_ptr=NULL;
            }
            if(src.set_ptr){
                set_ptr= new set<DataType>;
                *set_ptr= *src.set_ptr;
            }
        }

    }

    template <typename DataType>
    bool p_node<DataType>::operator< (const p_node<DataType>& src) const {
         if(set_ptr&&sample_space_ptr&&src.set_ptr&&src.sample_space_ptr){
            return sample_space_ptr->prob(*set_ptr)<src.sample_space_ptr->prob(*src.set_ptr) ;
         }
         return 0 ;
    }

    template <typename DataType>
    bool p_node<DataType>::operator> (const p_node<DataType>&src) const {
        if(set_ptr&&sample_space_ptr&&src.set_ptr&&src.sample_space_ptr){
            return sample_space_ptr->prob(*set_ptr)>src.sample_space_ptr->prob(*src.set_ptr) ;
        }
        return 0 ;
    }

    template <typename DataType>
    bool p_node<DataType>::operator<=(const p_node<DataType>&src) const {
        if(set_ptr&&sample_space_ptr&&src.set_ptr&&src.sample_space_ptr){
            return sample_space_ptr->prob(*set_ptr)<src.sample_space_ptr->prob(*src.set_ptr) ;
        }
        return(set_ptr==NULL&&src.set_ptr==NULL);
    }

    template <typename DataType>
    bool p_node<DataType>::operator>=(const p_node<DataType>&src) const {
        if(set_ptr&&sample_space_ptr&&src.set_ptr&&src.sample_space_ptr){
            return (*sample_space_ptr)->prob(*set_ptr)>(*src.sample_space_ptr)->prob(*src.set_ptr) ;
        }
        return(set_ptr==NULL&&src.set_ptr==NULL);
     }

    template <typename DataType>
    bool p_node<DataType>::operator==(const p_node<DataType>&src) const {
        if(set_ptr&&sample_space_ptr&&src.set_ptr&&src.sample_space_ptr){
            return sample_space_ptr->prob(*set_ptr)==src.sample_space_ptr->prob(*src.set_ptr) ;
        }
        return(set_ptr==NULL&&src.set_ptr==NULL);
    }

    template <typename DataType>
    bool p_node<DataType>::operator!=(const p_node<DataType>&src) const {
        return !(*this==src);
    }


    //say we insert or search or delete target_set
    template<typename DataType>
    void prob_tree<DataType>::euler_tour(node<set<DataType>>*ptr,bool (*func_ptr)(node<set<DataType>>*,const set<DataType>&)
        ,const set<DataType>&target_set,bool&search_response){
        if(ptr==NULL){
            ptr= tree.root ;
        }
        if(ptr){
            if(ptr->left){
                euler_tour(ptr->left,func_ptr,target_set,search_response) ;
            }
            //do what you want with ptr
            if(func_ptr(ptr,target_set)){
                search_response =true ;
            }
            if(ptr->right){
                euler_tour(ptr->right,func_ptr,target_set,search_response) ;
            }
        }
    }

    template<typename DataType>
    bool is_leaf(const node<set<DataType>>*ptr)      {
        return ptr->left==ptr->right&&ptr->left==NULL;
    }

    template<typename DataType>
    bool is_not_leaf(const node<set<DataType>>*ptr)  {
        return !is_leaf(ptr) ;
    }

    template<typename DataType>
    bool insert_node(node<set<DataType>>*ptr,const set<DataType>&target_set)  {
        //if leaf at right we insert intersection with event
        //at left we insert intersection with event'
        if(is_leaf(ptr)){
            set<DataType> temp =ptr->data.intersect(target_set) ;
            if(temp.size())
            {
                ptr->left= get_node(temp);
                ptr->left->parent=ptr;
            }

            temp = ptr->data.intersect(ptr->data.comp(target_set)) ;
            if(temp.size()){
                ptr->right= get_node(temp);
                ptr->right->parent= ptr ;
            }
            return 1 ;
        }
        return 0 ;
    }

    template<typename DataType>
    bool search_node(node<set<DataType>>*ptr,const set<DataType>&src)  {
         return ptr->data.equal(src) ;
    }
    template<typename DataType>
    prob_tree<DataType>::prob_tree(void)  {
        sample_space_ptr =NULL;
        tree =bst<set<DataType>>() ;
    }

    template<typename DataType>
    prob_tree<DataType>::prob_tree(const set<DataType>&sample_space)  {
        sample_space_ptr =NULL;
        sample_space_ptr=new set<DataType>;
        *sample_space_ptr =sample_space ;
        tree.root=get_node(sample_space) ;
        tree.size++;
    }

    template<typename DataType>
    prob_tree<DataType>::~prob_tree(void) {
        if(sample_space_ptr){
            delete sample_space_ptr;
            sample_space_ptr=NULL ;
        }
        tree.remove_tree() ;
    }

    //if the set has no intersection with original sample space
    //its not inserted same for the set_arr aswell
    template<typename DataType>
    prob_tree<DataType>::prob_tree(const set<DataType>&sample_space,const set<DataType>*set_arr,int size){
        sample_space_ptr =NULL;
        sample_space_ptr=new set<DataType>;
        *sample_space_ptr =sample_space ;

        p_node<DataType>* arr = new p_node<DataType>[size];

        for(int i = 0; i < size; i++){
            arr[i] = p_node<DataType>(sample_space_ptr, set_arr[i]);
        }

        std::sort(arr, (arr + size));

        tree= bst<set<DataType>>();
        tree.root=get_node(sample_space) ;

        std::queue<node<set<DataType>>*> queue;
        queue.push(tree.root);

        for (int i = size -1; i >= 0; --i) {
            node< set<DataType> >* current = queue.front();
            queue.pop();
            // Insert the next element from arr into the right and left children of current
            if (is_leaf(current)) {
                set<DataType>temp = current->data.intersect(*(arr[i].set_ptr)) ;
                if(!temp.empty()){
                    current->right =  get_node(temp);
                    current->right->parent= current;
                }
                temp=current->data.intersect(sample_space.comp(*(arr[i].set_ptr))) ;
                if(!temp.empty()){
                    current->left = get_node(temp);
                    current->left->parent= current;
                }
            }
            // Add the children to the queue for the next level
            if (current->left != NULL) {
                queue.push(current->left);
            }
            if (current->right != NULL) {
                queue.push(current->right);
            }
        }
        delete []arr;
        arr=NULL;
    }

    template<typename DataType>
    bool prob_tree<DataType>::insert(const set<DataType>&target_set){
        if(sample_space_ptr->contain(target_set)){
           bool ret_logic =false ;
            euler_tour(NULL,insert_node,target_set,ret_logic) ;
            return ret_logic;
        }
        return 0 ;
    }

    template<typename DataType>
    bool prob_tree<DataType>::search(const set<DataType>&target_set) {
        if(sample_space_ptr->contain(target_set)){
           bool ret_logic =false ;
            euler_tour(NULL,search_node,target_set,ret_logic) ;
            return ret_logic;
        }
        return 0 ;
    }

    template<typename DataType>
    void prob_tree<DataType>::print(void) const {
        tree.breadth_first() ;
    }

    template<typename DataType>
    void prob_tree<DataType>::move(void)const{
        tree.move() ;
    }

#include <chrono>

int main(){

    string space[4] ={"hh","ht","th","tt"};
    string aev[2] ={"hh","ht"};
    string bev[2] ={"hh","th"};
    string cev[2] ={"hh","tt"};
    set<string>sample_space(space,4);
    set<string>a(aev,2);
    set<string>b(bev,2);
    set<string>c(cev,2);
    vector<set<string>>v1;
    v1.push_back(a);
    v1.push_back(b);
    v1.push_back(c);

    cout<<sample_space.independence(v1);
    system("pause");

/*
    int space[] ={1,1,1,2,5,8} ;

    int arr[] =  {1,4,78} ;

    int arr2[] = {1,1,4,5,5,6} ;

    set<int>s1(space,sizeof(space)/sizeof(int));

    set<int>s2(arr,sizeof(arr)/sizeof(int));

    set<int>s3(arr2,sizeof(arr2)/sizeof(int));

    cout<<endl<<s1;

    cout<<endl<<s2;

    cout<<endl<<s3;

    s1.update_count(2,0) ;

    s1.update_count(2,5) ;

    s1.update_count(1,2) ;
    cout<<endl<<s1;
    cout<<s1.size() ;

    //s1.remove_duplicates();
    //cout<<s1;


    // Define a sample space (set of integers)
    // Define a sample space (set of integers)
    int arr[] = {1, 2, 3, 4, 5,6,7,8,9,10,11,12};
    set<int> sample_space(arr,sizeof(arr)/sizeof(int)) ;

    // Create an array of sets to insert into the prob_tree
    set<int>sets[4] ;
    for(int i = 1 ;i<4;i++){
        sets[0].insert(i) ;
        sets[1].insert(i+3) ;
        sets[2].insert(i+6) ;
        sets[3].insert(i+9) ;
    }



    //int num_sets = sizeof(sets) / sizeof(sets[0]);

    // Create a prob_tree instance with the sample space and sets array
    prob_tree<int> my_tree(sample_space, sets, 4);

    // Print the tree contents (for debugging purposes)
    cout << "Tree contents:" << endl;


    my_tree.print() ;
    my_tree.move() ;

    sets[0].clear() ;
    sets[1].clear() ;
    sets[2].clear() ;
    sets[3].clear() ;

    for(int i = 1 ;i<=2;i++){
        sets[0].insert(i) ;
        sets[1].insert(i+3) ;
        sets[2].insert(i+6) ;
        sets[3].insert(i+9) ;
    }



my_tree.insert(sets[0]);
my_tree.insert(sets[1]);
my_tree.insert(sets[2]);
my_tree.insert(sets[3]);



    sets[0].clear() ;
    sets[1].clear() ;
    sets[2].clear() ;
    sets[3].clear() ;


for(int i = 1 ;i<=2;i++){
    sets[0].insert(i+2) ;
    sets[1].insert(i+3+2) ;
    sets[2].insert(i+6+2) ;
    sets[3].insert(i+9+2) ;
}

    sets[0].clear() ;
    sets[1].clear() ;
    sets[2].clear() ;
    sets[3].clear() ;


for(int i = 1 ;i<=2;i++){
    sets[0].insert(i+2) ;
    sets[1].insert(i+3+1) ;
    sets[2].insert(i+6+1) ;
    sets[3].insert(i+9+1) ;
}
    sets[0].clear() ;
    sets[1].clear() ;
    sets[2].clear() ;
    sets[3].clear() ;


for(int i = 1 ;i<=2;i++){
    sets[0].insert(i+2+3) ;
    sets[1].insert(i+3+3) ;
    sets[2].insert(i+6+3) ;
    sets[3].insert(i+9+3) ;
}


my_tree.print() ;
my_tree.move() ;




/*
    auto start = std::chrono::high_resolution_clock::now();

    srand(time(0));
    set<int>s1, s2;
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed); // Standard mersenne_twister_engine seeded with high_resolution_clock
    std::uniform_int_distribution<> distrib(0, 100000000);
    for(int i = 0 ;i< 10000000; i++){
        int random_number = distrib(gen);
        s1.insert(random_number);

        random_number = distrib(gen);
        s2.insert(random_number);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken for insertion: " << elapsed.count() << "s\n";

    start = std::chrono::high_resolution_clock::now();
    s1.intersect(s2);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken for intersection: " << elapsed.count() << "s\n";

    start = std::chrono::high_resolution_clock::now();
    s1.unite(s2);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken for union: " << elapsed.count() << "s\n";

    start = std::chrono::high_resolution_clock::now();
    set<int>s3 = s1.unite(s2).comp(s1);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Time taken for complement: " << elapsed.count() << "s\n";

    //std::cout << s1.unite(s2).size() << "," << s1.size() << "," << s2.size() << "," << s3.size() << "\n";
     return 0;
*/
}
