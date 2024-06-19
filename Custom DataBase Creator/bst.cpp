
#include "bst.h"

//used as a filling slot when using breadth first save/load
string filling_string = "NULL" ;




    //helper functions to take right input
    //if user enters a character while expecting an integer or vice versa it doesn't cause issues
    bool getInput(char& choice) {
        cin>>choice;
        if(cin.fail()) {
            cin.clear(); // clear the error state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the bad input
            return false;
        }
        return true;
    }

    bool getInput(int& choice) {
        cin>>choice;
        if(cin.fail()) {
            cin.clear(); // clear the error state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the bad input
            return false;
        }
        return true;
    }


    // Function to open a file for writing
    bool openFileForWriting(const string& filePath) {
        ofstream file(filePath);
        if (!file) {
            return false;  // Failed to open the file
        }
        // File is now open for writing
        return true;
    }

    // Function to open a file for reading
    bool openFileForReading(const string& filePath) {
        std::ifstream file(filePath);
        if (!file) {
            return false;  // Failed to open the file
        }
        // File is now open for reading
        return true;
    }



    //turns a tree bst into a string and returns it
    //used in cout
    template<typename DataType>
    string to_string(const bst<DataType>&tree){
        string str;
        tree.to_string(str) ;
        return str ;
    }

    string to_string(const int &data){
        return std::to_string(data);
    }
    string to_string(const unsigned int&data){
        return std::to_string(static_cast<int>(data));
    }


    string to_string(const float &data){
        return std::to_string(data);
    }

    string to_string(const double &data){
        return std::to_string(data);
    }

    string to_string(const char &data){
        return std::string(1,data);
    }


    string to_string(const long &data){
        return std::to_string(static_cast<int>(data));
    }


    string to_string(const bool &data){
        return data ? "1" : "0";
    }

    string to_string(const string&data){
        return data;
    }


    template<typename DataType>
    string to_string(const vector<DataType>&vec){
        string str= "" ;
        for(int i = 0 ; i<vec.size();i++){
            str.append(::to_string(vec[i])+' ');
        }
        return str ;
    }

    template<typename unique_data_type>
    string to_string(const custom_data<unique_data_type>&p){
        return p.to_string() ;
    }
    //recursively add data in-order to a string str
    template <typename DataType>
    void bst<DataType>::to_string(string& str, node<DataType>* ptr) const {
        if (!ptr) {
            ptr = root ;
        }
        if(ptr){
            if (ptr->left) {
                to_string(str, ptr->left);
            }
            //this '\0' is actually important when saving the bst
            //data in file might seem weird but it loads correctly
            str.append(::to_string(ptr->data)+'\0');
            if (ptr->right) {
                to_string(str, ptr->right);
            }
        }
    }

    //helper function to allocate memory for a new node
    template <typename DataType>
    node<DataType>*bst<DataType>::get_node(const DataType & _data){

        node<DataType>*new_node=new node<DataType> ;

        new_node->data =_data ;

        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = NULL;

        return new_node;
    }

    //empty tree
    template<typename DataType>
    bst<DataType>::bst(void){
        root = NULL ;
        traverser= NULL ;
        size=0;
    }
    //tree filled from an array
    //if data is sorted its filled in O(N) else O(Nlog2N)
    //note if data is sorted and there are duplicates they aren't deleted
    template <typename DataType>
    bst<DataType>::bst(const DataType* arr, const long long _size) {
        size = 0;
        root = NULL ;
        traverser=NULL;

        if (is_sorted(arr,_size)) {
            size =_size;
            root = fill_sorted(arr, 0, size-1,root);
            root->parent = NULL;
        }
        else {
            for (long long i = 0; i <_size; i++) {
               insert(arr[i]);
            }
            traverser= root;
            root->parent = NULL;
        }
    }


    template <typename DataType>
    bst<DataType>::bst(const bst<DataType>& src) {
        root = copy_bst(src.root);
        size = src.size;
    }

    template <typename DataType>
     void bst<DataType>::operator=(const bst<DataType>&src) {
        if(this!=&src&&src.root){
            if(root){
                del_tree(root) ;
                root=NULL;
            }
            root=copy_bst(src.root) ;
            size= src.size;
        }
        else{
            del_tree(root) ;
            root =NULL;
        }
     }

    //tree filled from an array
    //if data is sorted its filled in O(N) else O(Nlog2N)
    template<typename DataType>
    bst<DataType>::bst(const vector<DataType>&arr) {
        size = 0;
        root = NULL ;
        traverser=NULL;
        if (is_sorted(arr)){
            size =arr.size();
            root = fill_sorted(arr, 0, size-1,root);
            root->parent = NULL;
        }
        else {
            for (long long i = 0; i <arr.size(); i++) {
               insert(arr[i]);
            }
            traverser= root;
            root->parent = NULL;
        }
    }

    //destructor
   template <typename DataType>
    bst<DataType>::~bst() {
        del_tree(root);
        root = NULL;
        traverser=NULL;
        size = 0;
    }
    //functions that remove the whole tree or a subtree
   template <typename DataType>//removes the whole bst
    bool bst<DataType>:: remove_tree(void){
         if(root){
           del_tree(root) ;
            root =NULL;
            traverser=NULL;
            size = 0 ;

        return 1;
     }
     return 0;
    }
    //remove the subtree beneath root containing data
    template <typename DataType>
    bool bst<DataType>:: remove_subtree(const DataType&data){
         if(search(data)){
            fix_parent(traverser,NULL) ;
            del_tree(traverser);
            traverser= root ;
            return 1 ;
         }
         return 0 ;
    }
    //checks if data in an array is sorted
    template <typename DataType>
    bool bst<DataType>::is_sorted(const DataType*arr,long long _size){
        for(long long i = 0  ; i <_size-1;i++){
            if(arr[i]>arr[i+1]){
                return 0;
            }
        }
        return 1 ;
    }

    //checks if vector of datatype is sorted
        template<typename DataType>

    bool bst<DataType>::is_sorted(const vector<DataType>&arr){
            for(long long i = 0  ; i <arr.size()-1;i++){
                if(arr[i]>arr[i+1]){
                    return 0;
                }
            }
            return 1 ;
        }

    //checks if data in a file is sorted
     template<typename DataType>
        bool bst<DataType>::is_sorted(ifstream& file){
            if (!file) return false; // Check if the file is open

            DataType d1, d2;
            char ch;
            while (file.get(ch)) {
                if (ch == '\0') continue; // Skip null characters
                file.putback(ch); // Put the character back into the stream
                if (!(file >> d1)) return true; // If the file is empty, it's considered sorted

                while (file.get(ch)) {
                    if (ch == '\0') continue; // Skip null characters
                    file.putback(ch); // Put the character back into the stream
                    if (!(file >> d2)) return true; // If there are no more elements, it's considered sorted
                    if (d1 > d2) {
                        return false;
                    }
                    d1 = d2; // Update d1 to be the current element for the next comparison
                }
            }
            return true;
        }
        template <typename DataType>
    node<DataType>*bst<DataType>::fill_sorted(const vector<DataType>&arr,long long beg,long long end,node<DataType>*ptr){
        if(ptr==NULL){
           if(beg<=end){
                long long mid =(end-beg)/2+beg;

                ptr = get_node(arr[mid]) ;

                ptr->left = fill_sorted(arr,beg,mid-1,ptr->left) ;

                if(ptr->left){
                    ptr->left->parent=ptr;
                }
                ptr->right=fill_sorted(arr,mid+1,end,ptr->right);
                if(ptr->right){
                    ptr->right->parent=ptr;
                }
                return ptr ;
            }
            else{
                return NULL;
            }
        }
        return NULL ;

    }//passed


    /*
    these functions fill a bst from sorted data in linear time (O(N))
    and returns the root of the tree
    one from an array and the other one from a file but the indexing file must exist(used in load)
    if indexing file doesn't exist and data is sorted it loads the data in a vector of the same data type
    and then puts it in linear time in the bst
    */
    template <typename DataType>
    node<DataType>* bst<DataType>:: fill_sorted(const DataType*arr,long long beg ,long long end ,node<DataType>*ptr){
        if(ptr==NULL){
           if(beg<=end){
                long long mid =(end-beg)/2+beg;

                ptr = get_node(arr[mid]) ;

                ptr->left = fill_sorted(arr,beg,mid-1,ptr->left) ;

                if(ptr->left){
                    ptr->left->parent=ptr;
                }
                ptr->right=fill_sorted(arr,mid+1,end,ptr->right);
                if(ptr->right){
                    ptr->right->parent=ptr;
                }
                return ptr ;
            }
            else{
                return NULL;
            }
        }
        return NULL ;
    }

    template<typename DataType>
    node<DataType>* bst<DataType>::fill_sorted(ifstream& file, ifstream& index_file, long long beg, long long end, node<DataType>* ptr) {
        if (ptr == NULL) {
            if (beg <= end) {
            // Calculate the middle line number
                long long mid = (end - beg) / 2 + beg;
                // Calculate the position to seek to in the index_file
                std::streamoff index_pos = mid * sizeof(std::streampos);

                // Seek to the position in index_file
                index_file.clear(); // Clear the EOF flag
                index_file.seekg(index_pos, std::ios::beg);

                // Read the position from the index_file
                std::streampos mid_pos;
                index_file.read(reinterpret_cast<char*>(&mid_pos), sizeof(mid_pos));

                // Seek to the position in file_path
                file.seekg(mid_pos);

                // Read the data from file_path
                DataType data;
                file >> data;
                // Create a new node with the data
                ptr = get_node(data);


                ptr->left = fill_sorted(file, index_file, beg, mid - 1, ptr->left);
                if (ptr->left) {
                    ptr->left->parent = ptr;
                }

                ptr->right = fill_sorted(file, index_file, mid + 1, end, ptr->right);
                if (ptr->right) {
                    ptr->right->parent = ptr;
                }

                return ptr;
                }
            else {
                return NULL;
            }
        }
        return NULL;
    }


    //deletes a binary tree where root is ptr
    template <typename DataType>//no recusion
     void bst<DataType>:: del_tree(node<DataType>*ptr){
        if(ptr){
            queue<node<DataType>*>q ;
            q.push(ptr) ;

            if(ptr->parent){
                fix_parent(ptr,NULL);
            }

            long long counter =1 ;
            while(!q.empty()){
                node<DataType>*temp= q.front() ;
                q.pop() ;
                if(temp->left){
                    q.push(temp->left);
                    counter++;
                }

                if(temp->right){
                    q.push(temp->right);
                    counter++ ;
                }

                if(temp){
                    delete temp;
                    temp=NULL;
                }
            }
            if(ptr==root){
               root=NULL;
            }
            ptr=NULL;
            size-=counter;
        }
    }



    //data inserted must have the id or the feature of comparison not repeated
    //ex: id of a person...etc
    //no recursion
    template <typename DataType>
    bool bst<DataType>::insert(const DataType&_data){
        node<DataType>*ptr= root;
        if(root==NULL){
            root=get_node(_data);
            size=1;
            return 1 ;
        }
        else{
            size++;
            while(1){
                if(_data==ptr->data){
                    size--;
                    return 0  ;
                }
                else if(_data<ptr->data){
                    if(ptr->left){
                        ptr=ptr->left;
                    }
                    else{
                        ptr->left= get_node(_data) ;
                        ptr->left->parent=ptr;
                        return 1  ;
                    }
                }
                else{
                    if(ptr->right){
                        ptr=ptr->right;
                    }
                    else{
                        ptr->right= get_node(_data) ;
                        ptr->right->parent=ptr;
                        return 1  ;
                    }
                }
            }
        }
    }

    //this function puts traverser pointer on the node containing data if found
    //and returns true
    template <typename DataType>    //no recursion
    bool bst<DataType>::search(const DataType&_data)const{
         traverser=root;
         if(traverser==NULL){
             return 0 ;
         }
        else{
            while(1){
                if(_data==traverser->data){
                    return 1  ;
                }
                else if(_data<traverser->data){
                    if(traverser->left){
                        traverser=traverser->left;
                    }
                    else{
                        return 0 ;
                    }
                }
                else{
                    if(traverser->right){
                        traverser=traverser->right;
                    }
                    else{
                        return 0  ;
                    }
                }
            }
        }
    }

    /*
    next set of functions are used in deletion of a node in a bst
    */
    //returns node with max data where root is ptr
    template <typename DataType>
    node<DataType>*bst<DataType>::get_max(node<DataType>*ptr)const {
        if(ptr){
            while(ptr->right){
                ptr=ptr->right;
            }
            return ptr ;
        }
    }

    //returns node with min data where root is ptr
    template <typename DataType>
    node<DataType>* bst<DataType>::get_min(node<DataType>*ptr)const {
        if(ptr){
            while(ptr->left){
                ptr=ptr->left;
            }
            return ptr ;
        }
    }

    //checks if ptr exists and its the left child
    template <typename DataType>
    bool  bst<DataType>::is_left(node<DataType>*ptr)const{
        return(ptr&&ptr->parent&&ptr->parent->left==ptr);
    }


    //checks if ptr exists and its the right child
    template <typename DataType>
    bool  bst<DataType>::is_right(node<DataType>*ptr)const {
        return(ptr&&ptr->parent&&ptr->parent->right==ptr);
    }

    /*
    this function makes ptr's parent's link pointing at ptr point at another destiniation
    for example ptr is left child of a parent left and we want it to point to another node
    this function takes care of it
    */
    template <typename DataType>
    void bst<DataType>::fix_parent(node<DataType>*ptr,node<DataType>*dest){
        if(is_left(ptr)){
            ptr->parent->left=dest;
        }
        else if(is_right(ptr)){
            ptr->parent->right=dest ;
        }
    }
    //checks if ptr is the root
    template <typename DataType>
    bool bst<DataType>::is_root(node<DataType>*ptr)const {
          return (ptr==root) ;
    }

    //deletes a node from a bst
    template <typename DataType>//no recursion
    bool bst<DataType>::remove(const DataType&data){
        if(root){
            //if data exists traverser sits on it now
            if(search(data)){
                size--;//decrement if data is found
                //leaf node condition
                if(traverser->left==NULL&&traverser->right==NULL){
                    if(is_root(traverser)){
                        delete root ;
                        traverser=NULL;
                        root= NULL;
                    }
                    else{
                        //update paren't link to point to null
                        fix_parent(traverser,NULL) ;
                        delete traverser ;
                        traverser = NULL;
                    }

                }
                //no right child condition
                else if(traverser->right==NULL){
                     traverser->left->parent=traverser->parent;
                     if(!is_root(traverser)){
                        fix_parent(traverser,traverser->left);
                      }
                      else{
                          root =root->left ;
                      }
                      delete traverser;
                      traverser=NULL;
                    }
                //no left child condition
                else if(traverser->left==NULL){
                     traverser->right->parent=traverser->parent;
                     if(!is_root(traverser)){
                        fix_parent(traverser,traverser->right);
                      }
                      else{
                          root =root->right ;
                      }
                      delete traverser;
                      traverser=NULL;
                    }
                    //2 children condition
                else{
                    node<DataType>*temp=(traverser->left)?get_max(traverser->left):get_min(traverser->right);
                    //save data in temp_data
                    //and saves traverser location in a temp pointer
                    //so that after removing temp data
                    //the temp_ptr is assigned the value
                    DataType temp_data=temp->data;
                    node<DataType>*temp_ptr= traverser;
                    remove(temp_data);
                    temp_ptr->data=temp_data ;
                }
                traverser=root;
                return 1 ;
                }
            }
            else{
                traverser=root;
            }
            return 0;
        }

    //copies a tree where ptr is the root of that tree
    template <typename DataType>    //no recursion
    node<DataType>*bst<DataType>::copy_bst(const node<DataType>* ptr) {
        if (ptr) {
            node<DataType>* new_root = get_node(ptr->data);
            queue<const node<DataType>*> src;

            queue<node<DataType>*> dest;
            size = 1 ;
            src.push(ptr);
            dest.push(new_root);

            while (!src.empty()) {
                const node<DataType>* src_node = src.front();

                node<DataType>* dest_node = dest.front();

                src.pop();
                dest.pop();

                if (src_node->left) {
                    dest_node->left = get_node(src_node->left->data);
                    dest_node->left->parent = dest_node;
                    src.push(src_node->left);
                    dest.push(dest_node->left);
                    size++;
                }

                if (src_node->right) {
                    dest_node->right = get_node(src_node->right->data);
                    dest_node->right->parent = dest_node;
                    src.push(src_node->right);
                    dest.push(dest_node->right);
                    size++;
                    }
                }
                return new_root;
            }
            //if src is null the tree is deleted
            else{
                del_tree(root) ;
                root =  NULL;
            }
            return NULL;
        }

    //inorder print the data of the bst where root is ptr
    //by default its root of the phantom
    template <typename DataType>//recursion used
    void  bst<DataType>::inorder(node<DataType>*ptr)const {
        if(!ptr){
            ptr = root ;
        }
        if(ptr){
            if(ptr->left){
                inorder(ptr->left);
            }
            cout<<ptr->data<<" , ";
            if(ptr->right){
                inorder(ptr->right)  ;
            }
        }
    }

    template <typename DataType>//recursion used
    void  bst<DataType>::preorder(node<DataType>*ptr)const {
        if(!ptr){
            ptr = root ;
        }
        if(ptr){
            cout<<ptr->data<<" , " ;
            if(ptr->left){
                preorder(ptr->left);
            }
            if(ptr->right){
                preorder(ptr->right)  ;
            }
        }
    }
    template <typename DataType>//recursion used
    void bst<DataType>:: postorder(node<DataType>*ptr)const {
        if(!ptr){
            ptr = root ;
        }
        if(ptr){
            if(ptr->left){
                postorder(ptr->left);
            }
            if(ptr->right){
                postorder(ptr->right)  ;
            }
            cout<<ptr->data<<" , " ;
        }
    }
    //prints the tree in level order or breadth-first
    template <typename DataType>//no recursion
    void  bst<DataType>::breadth_first(node<DataType>*ptr)const{
        if(root){
            if(!ptr){
                ptr = root ;
            }
            queue<const node<DataType>*>q ;
            q.push(ptr) ;
            while(!q.empty()){
                const node<DataType>*temp= q.front() ;
                q.pop() ;
                if(temp){
                    if(temp->left){
                        q.push(temp->left);
                    }
                    if(temp->right){
                        q.push(temp->right);
                    }
                    if(temp){
                        cout<<temp->data<<" , ";
                    }
                }
            }
        }
    }


    //interface with the tree
    template <typename DataType>
    void bst<DataType>:: move(void){
        if(root){
            traverser= root;
            while(1){
                cout<<"\n(Enter->stops at current)\n(w->go up)\n(a->go left)\n(d->go right)\n(s->show the whole tree)\n(q->quit)\n>>";

                cout<<"\n\nCurrent : "<<traverser->data<<"\n\n";
                cout<<"\n>>";

                char ch = getch();
                switch(ch){
                    case 'w':{
                        if(traverser->parent)
                           traverser =traverser->parent;
                        }break;
                    case 'd':{
                        if(traverser->right)
                           traverser =traverser->right;
                        }break;

                    case 'a':{
                        if(traverser->left)
                           traverser =traverser->left;
                        }break;
                    case 's':{
                        cout<<"\n\nLevel Order\n\n";
                        breadth_first(root);
                    }break;
                    case 'r':{
                            traverser=root;
                        }break;

                    case 'q':{
                        traverser=root;
                        return ;
                        }break;
                    case '\r' :{
                        return ;
                        }

                    }
                }
            }
            else{
                cout<<"\nTree is empty\n" ;
            }
        }

        /*
        load and save from a file functions
        */

    /*
    this function saves the bst in a file with an index_file (inorder)
    index_file contains a bunch of row  where each contains the starting point of data in the saved file
    think of computer organization how stack pointer works with stack
    data is pushed and the stack pointer is pointing at the new data (or at first empty place in memory)
    so for row one it contains 0 for row 2 it contains sizeof(data1)
    for row3 it contains sizeof(data1+data2) and so on
    if index file is removed or the name is altered (the .bin file )
    data may not be loaded correctly or it would take O(NlogN)
    since it assumes that its not sorted
    if the .bin doesn't exist
    */
    template<typename DataType>
    void bst<DataType>::inorder_save(node<DataType>*ptr, ofstream& file, ofstream& index_file) const {
        // If the node pointer is null, set it to the root of the tree
        if(!ptr){
            ptr=root;
        }
        // If there is a left child, recursively call the function on the left child
        if(ptr->left){
            inorder_save(ptr->left, file, index_file);
        }

        // Get the current position in the file
        std::streampos pos = file.tellp();

        // Write the position to the index file
        index_file.write(reinterpret_cast<const char*>(&pos), sizeof(pos));

        // Write the data of the current node to the file, followed by a null character
        file<<ptr->data<<'\0';

        // If there is a right child, recursively call the function on the right child
        if(ptr->right){
            inorder_save(ptr->right, file, index_file);
        }
    }

    /*
    this function saves the bst in a file with an index_file (inorder)
    index_file contains for each row it contains the starting point of data in the saved file
    think of computer organization how stack pointer works with stack
    data is pushed and the stack pointer is pointing at the new data
    so for row one it contains 0 for row 2 it contains sizeof(data1)
    for row3 it contains sizeof(data1+data2) and so on
    if index file is removed or the name is altered (the .bin file )
    data may not be loaded correctly or it would take O(NlogN) since it assumes that its not sorted
    if the .bin doesn't exist
    */
    template<typename DataType>
    bool bst<DataType>::save(void) const {
        if (root) {
            string file_path;
            string index_path ;
            cout << "\nEnter file's path please make sure the file is created\n";
            cout << "\n>>";
            getline(cin, file_path);
            if (openFileForWriting(file_path)) {
                ofstream file(file_path, std::ios::trunc); // Open file in write mode, which clears it
                index_path.append(file_path).append(".bin");
                ofstream index_file(index_path, std::ios::binary);
                inorder_save(root, file, index_file);
                cout << "\nSaved!\n";
                file.close(); // Close the file when done
                index_file.close() ;
                return 1;
            }
            return 0;
        }
        return 0 ;
    }

    //if user wants to load from a file and bst contains data
    //it promts the user to to save the tree if needed before it gets deleted
    template<typename DataType>
    void bst<DataType>::del_to_load(void){
        if(root){
            char choice ;
            cout<<"\nCurrent tree contains data do you want to save it first?(y/n)\n";
            cin>>choice;
            if(choice!='n'){
                cin.ignore();
                save();
            }
            del_tree(root) ;
            size=0 ;
            root= NULL;
            traverser =NULL;
            cin.ignore();
        }
    }


    //load data from a file where data isn't sorted
    //either spaced by ' ' or line by line
    //if your custom >> operator works correctly this functions loads unsorted data
    //successfully
    template<typename DataType>
    bool bst<DataType>::load_unorder(ifstream& file) {
        if (file.is_open()) { //if file exists
            DataType data;
            char ch;
            while (file.get(ch)) {
                if (!file.eof()) {
                    if (ch == '\0') continue; // Skip null characters
                    file.putback(ch); // Put the character back into the stream
                }
                if (file >> data) {
                    insert(data);
                }
            }
            file.close();
            return true;
        }
        return false;
    }

    //load data that's previously!!!! saved by the bst
    //if data is sorted and the index_file is altered this function won't be used
    //correctly
    template<typename DataType>
    bool bst<DataType>::load_inorder(ifstream&file,ifstream&index_file) {
        // Get the size of the index_file
        index_file.seekg(0, std::ios::end);
        std::streamoff index_size = index_file.tellg();
        index_file.seekg(0, std::ios::beg);
        // Calculate the number of entries in the index_file
        long long count = index_size / sizeof(std::streampos);
        root = fill_sorted(file, index_file, 0, count-1, root);
        traverser = root;
        size = count ;
        file.close();
        index_file.close();
        return 1;
    }

    /*
    this function has 2 features one is loading from a sorted file which takes O(N)
    and the other is loading from unordered file which takes O(NlogN)
    if the .bin file (index_file) doesn't exist then it loads the data into a vector
    and then loads it in O(N)
    */
    template<typename DataType>
    bool bst<DataType>::load(void) {
        bool logic =0;
        del_to_load();
        string file_path;
        string index_path ;
        cout << "\nEnter file's path please make sure the file is created\n";
        cout << ">>";
        getline(cin, file_path);
        ifstream file(file_path); // Open file in read mode
        //note how index file is same name as file_path
        //with the .bin added since its a binary file
        index_path.append(file_path).append(".bin");
        ifstream index_file(index_path, std::ios::binary);
        if(file.is_open() && index_file.is_open()) {
            //if both files exist it loads in O(N)
            load_inorder(file,index_file) ;
            logic= 1;
        }
        else if(file.is_open()){
            //if no index file then this is random data or unsorted
            vector<DataType>vec;
            if(is_sorted(file)){
                DataType d ;
                file.clear();
                file.seekg(0);
            if (file.is_open()) { //if file exists
                DataType data;
                vector<DataType>vec;
                char ch;
                while (file.get(ch)) {
                    if (ch == '\0') continue; // Skip null characters
                    file.putback(ch); // Put the character back into the stream
                    if (file >> data) {
                        vec.push_back(data);
                    }
                }
                root = fill_sorted(vec,0,vec.size()-1,root);
                size =vec.size() ;
                file.close();
            }

            }
            else{
                file.clear();
                file.seekg(0);
                load_unorder(file);
            }
            logic =1;
        }
        //close the 2 files
        if(index_file.is_open()){
            index_file.close();
        }
        if(file.is_open()){
            file.close() ;
        }
        return logic ;
    }

    //used in saving the bst in breadth first fashion
    template<typename DataType>
    bool is_null_queue(queue<node<DataType>*>&q){
            bool logic=false ;
            queue<node<DataType>*> temp ;
            node<DataType>*ptr =NULL;
            while(ptr==NULL&&!q.empty()){
                ptr =q.front();
                temp.push(ptr);
                q.pop();
            }
            if(ptr==NULL&&q.empty()){
                logic=true;
            }
            while(!q.empty()){
                ptr =q.front();
                temp.push(ptr);
                q.pop();
            }
            while(!temp.empty()){
                ptr =temp.front();
                q.push(ptr);
                temp.pop();
            }
            return logic;
        }

//save a tree in a file in breadth first fashion
template<typename DataType>
void bst<DataType>::save_breadth_first(void)const{
    if(root){
        string file_path;
        cout << "\nEnter file's path please make sure the file is created\n";
        cout<<">>";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin,file_path);
        if (openFileForWriting(file_path)){ //if file exists
            std::ofstream file(file_path, std::ios::trunc); // Open file in write mode, which clears it
            queue<node<DataType>*> q;
            if (root) {
                q.push(root);
                while (!q.empty()&&!is_null_queue(q)) {
                    node<DataType>* ptr = q.front();
                    q.pop();
                    if(ptr){
                        file << ptr->data <<"\n";
                        q.push(ptr->left);
                        q.push(ptr->right);
                    }
                    else {
                        //if null then 2 children are null
                        q.push(NULL);
                        q.push(NULL);
                        file << filling_string << "\n"; // Write the filling string directly to the file
                    }
                }
            }
            file.close(); // Close the file when done
            cout<<"\nSaved!";
            }
        }
    }

    //loads a tree from a file (the tree must be in breadth first fasion)
    //for empty nodes filling_string is put in the file but it won't be put into the tree
    //when loading from the file (used from previous project)
    template<typename DataType>
    void  bst<DataType>::load_breadth_first(void) {
        if(root){
            //if current tree isn't empty delete it first
            char choice;
            cout<<"\nCurrent tree contains data do you want to save it first?(y/n)\n>>" ;
            while(!getInput(choice)){
                cout<<"\n>>";
            }
            if(choice!='n'){
                save();
            }
            del_tree(root) ;
            root= NULL;
            traverser= NULL ;
        }
        //must provide complete file path and it must exist
        string file_path;
        cout << "\nEnter file's path please make sure the file is created\n";
        cout<<">>";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin,file_path);
        std::ifstream file(file_path); // Open file in read mode
        if (file.is_open()) { //if file exists
            string str;
            getline(file, str);
            if (str.empty()) {
                cout << "\nEmpty File\n";
                file.close(); // Close the file when done
                traverser= NULL;
                root =NULL;
                return;
            }
            DataType d;
            std::istringstream iss(str);
            iss >> d;
            root = get_node(d);
            queue<node<DataType>*> q;
            q.push(root);
            while (!q.empty()) {
                node<DataType>* ptr = q.front();
                q.pop();
                //the first empty line means that tree is loaded
                if (!getline(file, str)) {
                    cout << "\nFinished loading\n";
                    file.close(); // Close the file when done
                    return;
                }
                //if its a filling string its not added into the tree
                //note that instead the queue is filled with nulls so find first non-null item
                //and then the data found in the file is its left child
                if (str != filling_string) {
                    while(ptr==NULL){
                        ptr = q.front();
                        q.pop() ;
                    }
                    std::istringstream iss(str);
                    iss >> d;
                    ptr->left = get_node(d);
                    ptr->left->parent = ptr;
                    q.push(ptr->left);
                }
                else{
                    q.push(NULL) ;
                }
                if (!getline(file, str)) {
                    cout << "\nFinished loading\n";
                    file.close(); // Close the file when done
                    return;
                }
                //same thing here but for right child
                if (str != filling_string) {
                    while(ptr==NULL){
                        ptr = q.front();
                        q.pop() ;
                    }
                    std::istringstream iss(str);
                    iss >> d;
                    ptr->right = get_node(d);
                    ptr->right->parent = ptr;
                    q.push(ptr->right);
                }
                else{
                    //push null so that logic of decisions isn't altred
                    q.push(NULL) ;
                }
            }
            file.close(); // Close the file when done
            traverser= root;
        }
        else {
            cout << "\nFile doesn't exist";
            root= NULL;
            traverser=NULL;
        }

    }



    //cout a bst
    template <typename DataType>
    ostream& operator<<(ostream& os, const bst<DataType>&obj) {
        string output= "";
        obj.to_string(output);
        os<<output ;
        return os ;
    }

    template <typename DataType>
    istream& operator>>(istream& is, bst<DataType>& obj) {
        string line;
        while (getline(is, line) &&!line.empty()) {
            std::istringstream lineStream(line);
            DataType data;
            while (lineStream >> data) {
                obj.insert(data);
            }
        }
        return is;
    }


/*
    logical operators for the bst
    if user wants to create a bst of bsts it needs more work since how do you get max element of those trees ?
*/
    //equality of 2 bst is if they have same structure and same data
    //so breadth first equality is checked via this function
    template<typename DataType>
    bool bst<DataType>::operator==(const bst&src)const{
        if(root&&src.root){
            queue<const node<DataType>*>b1,b2;
            b1.push(root) ;
            b2.push(src.root);
            bool l1=0,l2=0,r1=0,r2=0 ;
            while(!b1.empty()&&!b2.empty()){
                l1=0;l2=0;
                r1=0;r2=0;
                const node<DataType>*temp= b1.front() ;
                const node<DataType>*temp2= b2.front() ;

                    b1.pop() ;
                    b2.pop() ;

                    if(temp->left){
                        l1 =1;
                        b1.push(temp->left)  ;
                    }
                    if(temp2->left){
                        l2= 1 ;
                        b2.push(temp2->left)  ;
                    }
                    if(l1!=l2){
                        return 0 ;
                    }
                    if(temp->right){
                        r1 =1;
                        b1.push(temp->right)  ;
                    }
                    if(temp2->right){
                        r2= 1 ;
                        b2.push(temp2->right)  ;
                    }
                    if(r1!=r2){
                        return 0 ;
                    }
                    if(!(temp->data==temp2->data)){
                        return 0;
                    }
                }
                return b1.empty()&&b2.empty() ;
            }

        return (root==NULL&&src.root==NULL);
    }


    //compares max of phantom is less than max of src
     template <typename DataType>
     bool bst<DataType>::operator <(const bst&src) const {
          if(root&&src.root){
              return get_max()->data<src.get_max()->data;
          }
          return (root==NULL);
     }
    //compares if max of phantom is bigger than max of src
    template <typename DataType>
    bool bst<DataType>::operator >(const bst&src) const {
          if(root&&src.root){
              return get_max()->data>src.get_max()->data;
          }
          return (src==NULL);
    }
    //get number of elements in the tree
    template<typename DataType>
    long long  bst<DataType>::get_size(void){
        return size;
    }
    template<typename DataType>
    DataType bst<DataType>:: access_traverser(void){
        DataType data ;
        if(traverser){
            data = traverser->data ;
        }
        return data;
    }

    /*
    end of bst related functions
    */



    /*
         other_data and custom_data class related functions
         look for documentation in the header I'm not repeating how its used

    */

    //function to allocate a vector of size (size) and returns it
    //if size is less than or equal to zero it doesn't allocate memory and returns null
    template<typename vector_data_type>
    vector_data_type *get_vec(const int size){
        if(size>0){
            vector_data_type*ret_vec = new vector_data_type[size];
            return ret_vec ;
        }
        return NULL;
    }
    //copy src into dest
    //and dest_size aswell if src is empty then dest is deleted and dest_size =0
    template<typename vector_data_type>
    void copy_vec(vector_data_type*&dest,const vector_data_type*src,int&dest_size,const int src_size){
        if(dest!=src){
            if(dest){
                delete[]dest ;
                dest= NULL;
                dest_size=0 ;
            }
            if(src){
                dest = get_vec<vector_data_type>(src_size);
                for(int i =  0 ; i<src_size; i++){
                    dest[i] = src[i];
                }

                dest_size= src_size ;
            }
        }
    }

    //turn a vector of vector_data_type into a string
    //used in custom data class
    template<typename vector_data_type>
    string vec_to_string(vector_data_type*vec,int size ){
         string str = "";
         if(vec){
            for(int i = 0 ; i<size ;  i++){
                str.append(::to_string(vec[i])+' ');
            }
         }
         return str ;
    }

    //resize a vector into a wanted size and copying old data from old vector to new vector
    //according to minimum size of both vectors
    //used in custom data class
    template<typename vector_data_type>
    void resize_vec(vector_data_type*&vec,int&old_vec_size,int wanted_size){

        vector_data_type*new_vec= get_vec<vector_data_type>(wanted_size) ;
        if(vec&&new_vec){
           for(int i = 0  ; i <wanted_size&&i<old_vec_size;i++){
                new_vec[i] = vec[i]  ;
            }
            delete[]vec ; vec= NULL ;
        }
        vec =new_vec;
        old_vec_size =( wanted_size>=0)?wanted_size:0;
    }

    /*
    each vector is null and no size for each is allocated
    */
    other_data ::other_data(void){
        for(int i =  0 ;i<5 ; i++){
            data_type_count[i]  = 0 ;
        }
        longs= NULL;
        doubles= NULL;
        characters= NULL;
        strings= NULL;
        booleans= NULL;
    }
    //initialize other_data with size of each vector in the order of ldscb
    other_data ::other_data(int arr[5]) {

        longs = get_vec<long>(arr[long_count-1]);
        data_type_count[long_count-1]=arr[long_count-1]>0? arr[long_count-1]:0;

        doubles =get_vec<double>(arr[double_count-1]);
        data_type_count[double_count-1]=arr[double_count-1]>0?arr[double_count-1]:0;

        characters=get_vec<char>(arr[char_count-1]);
        data_type_count[char_count-1]=arr[char_count-1]>0?arr[char_count-1]:0;

        strings =get_vec<string>(arr[string_count-1]);
        data_type_count[string_count-1]=arr[string_count-1]>0?arr[string_count-1]:0;

        booleans=get_vec<bool>(arr[bool_count-1]);
        data_type_count[bool_count-1]=arr[bool_count-1]>0?arr[bool_count-1]:0;
    }
    other_data::other_data(int integer_array_size,int floating_point_array_size , int string_array_size,int char_array_size ,int bool_array_size) {
        longs = get_vec<long>(integer_array_size);
        data_type_count[long_count-1]=integer_array_size>0? integer_array_size:0;

        doubles =get_vec<double>(floating_point_array_size);
        data_type_count[double_count-1]=floating_point_array_size>0?floating_point_array_size:0;

        characters=get_vec<char>(char_array_size);
        data_type_count[char_count-1]= char_array_size>0?char_array_size:0;

        strings =get_vec<string>(string_array_size);
        data_type_count[string_count-1]=string_array_size>0?string_array_size:0;

        booleans=get_vec<bool>(bool_array_size);
        data_type_count[bool_count-1] = bool_array_size>0?bool_array_size:0;
    }
    /*
    delete each vector if allocated
    */
    other_data::~other_data() {
        if(longs){
            delete []longs;
        }
        if(doubles){
            delete []doubles;
        }
        if(characters){
            delete []characters;
        }
        if(strings){
            delete[]strings ;
        }
        if(booleans){
            delete []booleans;
        }
    }
    //assignment operator for other_data
    //copies each vector from other into the phantom
    //if if a vector in other is not allocated or null then same occurs in phantom
    //assignment literally
    void other_data::operator=(const other_data&other) {
        if(this!=&other){
            copy_vec<long>(longs,other.longs,data_type_count[long_count-1],other.data_type_count[long_count-1]);
            copy_vec<double>(doubles,other.doubles,data_type_count[double_count-1],other.data_type_count[double_count-1]);
            copy_vec<char>(characters,other.characters,data_type_count[char_count-1],other.data_type_count[char_count-1]);
            copy_vec<string>(strings,other.strings,data_type_count[string_count-1],other.data_type_count[string_count-1]);
            copy_vec<bool>(booleans,other.booleans,data_type_count[bool_count-1],other.data_type_count[bool_count-1]);
        }
    }
    //turns other_data into a string
    //note the size of each vector is turned into a string and then the following elements of each vector
    //no seg-fault
    string other_data::to_string(void)const {
        string ret_str ="";
             for(int i= 0 ; i<5;i++){
                ret_str.append(std::to_string(data_type_count[i])+' ');
             }
             ret_str.append(vec_to_string(longs,data_type_count[long_count-1]));
             ret_str.append(vec_to_string(doubles,data_type_count[double_count-1]));
             ret_str.append(vec_to_string(strings,data_type_count[string_count-1]));
             ret_str.append(vec_to_string(characters,data_type_count[char_count-1]));
             ret_str.append(vec_to_string(booleans,data_type_count[bool_count-1]));

        return ret_str  ;
    }

/*
    custom_class functions
*/
    //empty custom_data
    //note that unique parameter isn't initialized
    template<typename unique_data_type>
    custom_data<unique_data_type>::custom_data(void){
        int arr[5] ;
        for(int i = 0 ; i<5 ; i++){
            arr[i] = 0;
        }
        other=other_data(arr) ;
    }

    //copy constructor
    //first copy other_data and then the unique parameters
    //vectors of other_data are resized according to src vectors and then assigned the values
    template<typename unique_data_type>
    custom_data<unique_data_type>::custom_data(const custom_data& src){
        other=src.other;
        unique_parameter = src.unique_parameter ;
    }
    //assignment operator
    template<typename unique_data_type>
    void custom_data<unique_data_type>::operator=(const custom_data &src)  {
            other = src.other;
            unique_parameter = src.unique_parameter ;
    }

    //initialize other_data vectors (size parameter doesn't matter really )
    //what matter is the array must be 5 element if more its fine if less well its seg-fault
    //use set_data_type
    template<typename unique_data_type>
    custom_data<unique_data_type>::custom_data(int *arr, int size){
        other =other_data(arr);
    }

    template<typename unique_data_type>
    custom_data<unique_data_type>::custom_data(int integer_array_size,int floating_point_array_size , int string_array_size,int char_array_size,int bool_array_size){
        other =other_data(integer_array_size,floating_point_array_size,string_array_size,char_array_size,bool_array_size);
    }

    template<typename unique_data_type>
    custom_data<unique_data_type>::~custom_data(){
        //empty since other_data constructor is implemented already
        //if unique_parameter is a complex data structure then you must implement its destructor
    }


    /*
    logical operators where unique_parameter is the one used in comparisons only
    */
    template<typename unique_data_type>
    bool custom_data<unique_data_type>::operator<(const custom_data &src) const {
        return unique_parameter < src.unique_parameter;
    }

    template<typename unique_data_type>
    bool custom_data<unique_data_type>::operator>(const custom_data &src) const {
        return unique_parameter > src.unique_parameter;
    }

    template<typename unique_data_type>
    bool custom_data<unique_data_type>::operator<=(const custom_data &src) const {
        return unique_parameter <= src.unique_parameter;
    }

    template<typename unique_data_type>
    bool custom_data<unique_data_type>::operator>=(const custom_data &src) const {
        return unique_parameter >= src.unique_parameter;
    }

    template<typename unique_data_type>
    bool custom_data<unique_data_type>::operator==(const custom_data &src) const {
        return unique_parameter == src.unique_parameter;
    }

    template<typename unique_data_type>
    bool custom_data<unique_data_type>::operator!=(const custom_data &src) const {
        return unique_parameter != src.unique_parameter;
    }

    template<typename unique_data_type>
    string custom_data<unique_data_type>::to_string(void)const{
        /*
        unique parameter->size of each vector ->content of each vector
        */
        return std::to_string(unique_parameter).append(' '+other.to_string());
    }

    /*
        accessors of each element of the custom_data class
    */

        template<typename unique_data_type>
        unique_data_type& custom_data<unique_data_type>::at_unique(void){
            return unique_parameter;
        }

        template<typename unique_data_type>
        const unique_data_type& custom_data<unique_data_type>::at_unique(void) const{
            return unique_parameter;
        }

        template<typename unique_data_type>
        long& custom_data<unique_data_type>::at_longs(int index){
            if(index>=0&&index<other.data_type_count[long_count-1]){
                return other.longs[index];
            }

        }
            template<typename unique_data_type>

        const long&custom_data<unique_data_type>:: at_longs(int index) const{
            if(index>=0&&index<other.data_type_count[long_count-1]){
                return other.longs[index];
            }
        }
        template<typename unique_data_type>

        double& custom_data<unique_data_type>::at_doubles(int index){
            if(index>=0&&index<other.data_type_count[double_count-1])
                    return other.doubles[index] ;

        }

        template<typename unique_data_type>
        const double& custom_data<unique_data_type>::at_doubles(int index) const{
            if(index>=0&&index<other.data_type_count[double_count-1])
                return other.doubles[index] ;
        }

        template<typename unique_data_type>
        char& custom_data<unique_data_type>::at_chars(int index){
            if(index>=0&&index<other.data_type_count[char_count-1])
                return other.characters[index] ;
        }

        template<typename unique_data_type>
        const char&custom_data<unique_data_type>:: at_chars(int index) const{
            if(index>=0&&index<other.data_type_count[char_count-1])
                return other.characters[index] ;
        }

        template<typename unique_data_type>
        string&custom_data<unique_data_type>:: at_strings(int index){
            if(index>=0&&index<other.data_type_count[string_count-1])
                return other.strings[index] ;
        }

        template<typename unique_data_type>
        const string& custom_data<unique_data_type>::at_strings(int index) const{
            if(index>=0&&index<other.data_type_count[string_count-1])
                return other.strings[index] ;
        }


        template<typename unique_data_type>
        bool& custom_data<unique_data_type>::at_bools(int index){
            if(index>=0&&index<other.data_type_count[bool_count-1])
                return other.booleans[index] ;

        }

        template<typename unique_data_type>
        const bool& custom_data<unique_data_type>::at_bools(int index) const{
            if(index>=0&&index<other.data_type_count[bool_count-1])
                return other.booleans[index] ;
        }




    //you can cout an object of custom_data (used in save and load )
    //you can use it aswell
    template<typename unique_data_type>
    ostream& operator<<(ostream& os, const custom_data<unique_data_type>& obj) {
        string output= "";
        output = obj.to_string();
        os<<output ;
        return os ;
    }
    //get size of the vector of data type dt
    //use enumerator values
    template<typename unique_data_type>
    int custom_data<unique_data_type>::get_data_type_count(int dt)const{
       if(dt>=1&&dt<=5)
            return other.data_type_count[dt-1] ;
        return -1 ;
    }
    //here is how to cin into an object of custom_data
    /*
    unique parameter ->size of long array ->size of double array->size of string array->size of char array ->size of bools
    ->contents of each array in same order previously mentioned
    (used in save and loading from a file ) can be improved to store the array of 5 integers in the bst and
    save the 20 or 10 bytes for each custom_data
    */
    template<typename unique_data_type>
    istream& operator>>(istream& is, custom_data<unique_data_type>& obj){
            is>>obj.at_unique();
            int n;
            is>>n;
            obj.set_data_type_size(long_count,n);
            is>>n;
            obj.set_data_type_size(double_count,n);
            is>>n;
            obj.set_data_type_size(string_count,n);
            is>>n;
            obj.set_data_type_size(char_count,n);
            is>>n;
            obj.set_data_type_size(bool_count,n);
            /*
            after size is taken and size is allocated for each array you input the content of each
            doesn't cause segmentation fault since size of each array is allocated according to your input
            */
            for(int j= 0 ;j<obj.get_data_type_count(long_count);j++){
                is>>obj.at_longs(j);
            }
            for(int j= 0 ;j<obj.get_data_type_count(double_count);j++){
                is>>obj.at_doubles(j);
            }
            for(int j= 0 ;j<obj.get_data_type_count(string_count);j++){
                is>>obj.at_strings(j);
            }
            for(int j= 0 ;j<obj.get_data_type_count(char_count);j++){
                is>>obj.at_chars(j);
            }
            for(int j= 0 ;j<obj.get_data_type_count(bool_count);j++){
                is>>obj.at_bools(j);
            }
        return is ;
    }
    /*
    set or resize a vector of data type dt where dt is the enumerator values
    don't worry about indexing its handled in the classs
    */
    template<typename unique_data_type>
    void custom_data<unique_data_type>::set_data_type_size(int dt,int count) {
        if(dt>=1&&dt<=5){
            if(count>=0){
                switch(dt){
                    case long_count:{
                        resize_vec<long>(other.longs,other.data_type_count[dt-1] ,count);
                    }break;
                    case double_count:{
                        resize_vec<double>(other.doubles,other.data_type_count[dt-1] ,count);

                    }break;
                    case string_count:{
                        resize_vec<string>(other.strings,other.data_type_count[dt-1] ,count);

                    }break;
                    case char_count:{
                        resize_vec<char>(other.characters,other.data_type_count[dt-1] ,count);
                    }break;

                    case bool_count:{
                        resize_vec<bool>(other.booleans,other.data_type_count[dt-1] ,count);

                    }break;
                }
            }
        }
    }



    //used in testing
    //fun fact i found out there is a saturation that occurs in random numbers generation
    //used this initially to generate new seed for srand each half a second but didn't work :)
    void delay(int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }




    /*
    the following class is an example of how to use the code
    */

        //ldscb->long or integers ,floating point values->strings->characters->booleans

        //say we store age ,height ,life_status first name ,last name ,city of residance
        //date of birth , say a character indicating hair color or some thing similar
        civil_record::civil_record(){
            //define number of parameters for ldscb here
            person =custom_data<int>(1,1,4,1,1);
        }

        civil_record::~civil_record() {

            cout<<"\n"<<data_base.get_size();
            system("pause");
        }
        void civil_record::insert_person(void){

            do{
                cout<<"\nEnter The ID\n";
                cin>>person.at_unique();
                //while that id exists keep taking input
                //note that the object we use as an input is person not at_unique
            }while(data_base.search(person));

            cin.ignore() ;
            cout<<"\nEnter first name\n";
            cin>>person.at_strings(first_name) ;
            cin.ignore() ;
            cout<<"\nEnter last name\n";
            cin>>person.at_strings(last_name) ;
            cin.ignore() ;
            cout<<"\nEnter Birth date->(y/m/d)\n";
            cin>>person.at_strings(birth_date) ;
            cin.ignore() ;
            cout<<"\nEnter The Age\n";
            cin>>person.at_longs(0) ;
            cin.ignore() ;
            cout<<"\nEnter the city\n" ;
            cin>>person.at_strings(city) ;
            cin.ignore() ;
            cout<<"\nEnter height\n";
            cin>>person.at_doubles(0) ;
            cout<<"\nEnter Hair color->(b,w,g,y,w)\n";
            cin>>person.at_chars(0) ;

            cin.ignore() ;
            cout<<"\nEnter Life status\n";
            cin>>person.at_bools(0) ;
            cin.ignore() ;

            if(data_base.insert(person)){
                cout<<"\nSuccess!" ;
            }
            else{
                cout<<"\nSomething went wrong please try again\n" ;
            }
        }
        void civil_record::civil_record::delete_person(void) {

            cout<<"\nEnter the ID";
            cin>>person.at_unique() ;
            if(data_base.remove(person)){
                cout<<"\nSuccess!" ;
            }
            else{
                cout<<"\nNot found!\n" ;
            }
        }
        void civil_record::search_person(void){
            cin.ignore();
            cout<<"\nEnter the ID";
            cin>>person.at_unique() ;
            if(data_base.search(person)){
                person= data_base.access_traverser() ; //access content of traverser
                cout<<"\nFound!" ;
                cout<<"\nID : "<<person.at_unique() ;
                cout<<"\nFirst Name : "<<person.at_strings(first_name) ;
                cout<<"\nLast Name : "<<person.at_strings(last_name) ;
                cout<<"\nCity  : "<<person.at_strings(city) ;
                cout<<"\nBirth date: "<<person.at_strings(birth_date) ;
                cout<<"\nHair color: "<<person.at_chars(0) ;
                cout<<"\nLife status: ";
                if(person.at_bools(0)){
                    cout<<"Alive";
                }
                else{
                    cout<<"Dead";
                }
            }
            else{
                cout<<"\nNot found!\n" ;
            }
        }
        void civil_record::save_data_base(void){
            cin.ignore();
            if(data_base.save()){
                cout<<"\nSaved!";
            }
            else{
                cout<<"\nSomething went wrong!";
            }

        }
        void civil_record::load_data_base(void) {
            cin.ignore();
            cout<<"\nNote :the file to load from must have same parameters of the person data";
            cout<<"\nor the data base may not behave correctly!";
            if(data_base.load()){
                cout<<"\nLoaded successfully!";
            }
            else{
                cout<<"\nSomething went wrong!";
            }
        }

        void civil_record::delete_data_base(void){
            char choice;
            cout<<"\nDo you want to save it first?(y/n)";
            cin>>choice;
            if(choice!='n'){
                save_data_base();
            }
            data_base.remove_tree();
        }
        void civil_record::show_data_base(void){
             data_base.inorder();
        }



    int main(){
        /*
        Simple interface with the example person class
        */
        civil_record record;
        int choice ;

        while(choice!=8){
            cout<<"\n1---Insert a new person\n";
            cout<<"\n2---Search for a person\n";
            cout<<"\n3---show all the entries of the data base\n";
            cout<<"\n4---Delete a person\n";
            cout<<"\n5---Save current data base\n";
            cout<<"\n6---Load a data base\n";
            cout<<"\n7---Remove current data base\n";
            cout<<"\n8---Exit";
            cout<<"\nchoice: ";
            cin>>choice;
            cin.ignore();
            switch(choice){
                case 1:record.insert_person();break;
                case 2:record.search_person();break;
                case 3:record.show_data_base();break;
                case 4:record.delete_person();break;
                case 5:record.save_data_base();break;
                case 6:record.load_data_base();break;
                case 7:record.delete_data_base();break ;
                case 8:return 0 ;

            }

        }


        return 0 ;
    }
