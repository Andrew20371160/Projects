// Include the header file for the civil record
#include "civil_record.h"

// Function to create a new node with the given data
node *bst::get_node(node&data){
    // Allocate memory for the new node
    node*new_node= new node ;

    // Copy the data from the given node to the new node
    new_node->id = data.id ;
    new_node->name = data.name ;
    new_node->bdate.day = data.bdate.day ;
    new_node->bdate.month = data.bdate.month ;
    new_node->bdate.year = data.bdate.year ;
    new_node->mother_name = data.mother_name ;
    new_node->address = data.address;

    // Set the life status to alive
    new_node->life_status = alive ;

    // Initialize the parent, left, and right pointers to NULL
    new_node->parent =NULL ;
    new_node->left  = NULL ;
    new_node->right = NULL ;

    // Return the new node
    return new_node;
}

// Default constructor for the bst class
bst ::bst(){
    // Initialize the root pointer to NULL and the count to 0
    root= NULL ;
    count  =0;
}

// Constructor for the bst class that takes a node pointer
bst ::bst(node*data){
    // Create a new node with the given data and set it as the root
    root = get_node(*data) ;

    // Set the count to 1
    count= 1;
}

// Constructor for the bst class that takes a data set and its size
bst ::bst(node *data_set,unsigned int size){

    for( unsigned int i = 0 ;i<size;i++){
        // Try to insert the data item into the tree
        if(insert(data_set[i])) {
            // If the insertion was successful, increment the count
            cout<<"\ninserted";
            count++;
        }
        else{
            // If the insertion was not successful, print a message
            cout<<"\nNot inserted";
        }
    }
}

// Destructor for the bst class
bst ::~bst(){
    // Delete all nodes in the tree and set the count to 0
    del_tree(root) ;
    count=0;
}
// Function to insert a node into the bst
bool bst:: insert(node&data){
    // If the tree is empty
    if(root==NULL){
        // Create a new node with the given data and set it as the root
        root=get_node(data) ;
    }
    else{
        // Start from the root
        node*bst_traverse =root;

        // Keep going until we find the right place to insert the new node
        while(1){
            // If the data is already in the tree, return false
            if(data.id==bst_traverse->id){
                return false;
            }
            // If the data is less than the current node's data
            else if(data.id<bst_traverse->id){
                // If the current node does not have a left child
                if(bst_traverse->left==NULL){
                    // Create a new node with the given data and set it as the left child
                    bst_traverse->left= get_node(data);
                    // Set the parent of the new node to the current node
                    bst_traverse->left->parent = bst_traverse;
                    // Increment the count of nodes
                    count++;
                    // Return true to indicate that the insertion was successful
                    return true ;
                }
                else{
                    // Move to the left child
                    bst_traverse=bst_traverse->left;
                }
            }
            else{
                // If the current node does not have a right child
                if(bst_traverse->right==NULL){
                    // Create a new node with the given data and set it as the right child
                    bst_traverse->right= get_node(data);
                    // Set the parent of the new node to the current node
                    bst_traverse->right->parent = bst_traverse;
                    // Increment the count of nodes
                    count++;
                    // Return true to indicate that the insertion was successful
                    return true ;
                }
                else{
                    // Move to the right child
                    bst_traverse=bst_traverse->right;
                }
            }
        }
    }
    // Return false to indicate that the insertion was not successful
    return false ;
}
// Function to search for a node in the bst by its id
node *bst:: search(unsigned int id) {
    // If the tree is empty, return NULL
    if(root==NULL){
        return NULL;
    }
    else{
        // Start from the root
        node*bst_traverse = root;

        // Keep going until we find the node with the given id or reach a leaf node
        while(1){
            // If the current node's id is the given id, return the current node
            if(id==bst_traverse->id){
                return bst_traverse;
            }
            // If the given id is less than the current node's id
            else if(id<bst_traverse->id){
                // If the current node does not have a left child, return NULL
                if(bst_traverse->left==NULL){
                    return NULL;
                }
                else{
                    // Move to the left child
                    bst_traverse=bst_traverse->left;
                }
            }
            else{
                // If the current node does not have a right child, return NULL
                if(bst_traverse->right==NULL){
                    return NULL;
                }
                else{
                    // Move to the right child
                    bst_traverse=bst_traverse->right;
                }
            }
        }
    }
}
// Function to fix the parent pointer of a node after a deletion or rotation
void bst::fix_parent(node*src,node*dest){
    // If the source node is not the root
    if(!is_root(src)){
        // If the source node is the left child of its parent
        if(is_left(src)){
            // Set the left child of the parent to the destination node
            src->parent->left=dest;
        }
        else{
            // Set the right child of the parent to the destination node
            src->parent->right =dest;
        }
    }
}
    // The function takes an unsigned integer 'id' as an argument, which is the id of the node to be deleted.
    // The function returns a boolean value indicating whether the deletion was successful or not.
bool bst::del(unsigned int id) {

    // If the tree is not empty
    if(root){
        // Search for the node with the given id
        node*ptr = search(id) ;

        // If the node is found
        if(ptr){
            // If the node is a leaf node (has no children)
            if(ptr->left==NULL&&ptr->right==NULL){
                // If the node is not the root
                if(!is_root(ptr)){
                    // Fix the parent pointer of the node
                    fix_parent(ptr,NULL);
                    // Delete the node
                    delete ptr ;
                    ptr =NULL ;
                }
                else{
                    // If the node is the root, delete the root
                    delete root ;
                    root =NULL;
                }
            }
            else{
            // Create a temporary pointer to the node to be deleted
                node*temp = ptr ;

                // If the node has only a right child
                if(temp->left==NULL){
                    // Set the parent of the right child to the parent of the node
                    temp->right->parent = temp->parent ;
                    // Fix the parent pointer of the node
                    fix_parent(temp,temp->right) ;
                    // Move the pointer to the right child
                    ptr = ptr->right;
                    // If the node is the root, update the root
                    root =(root==temp)?ptr:root ;
                }
                // If the node has only a left child
                else if(ptr->right==NULL){
                    // Set the parent of the left child to the parent of the node
                    temp->left->parent = temp->parent ;
                    // Fix the parent pointer of the node
                    fix_parent(temp,temp->left);
                    // Move the pointer to the left child
                    ptr = ptr->left;
                    // If the node is the root, update the root
                   root= (root==temp)?ptr:root ;
                }
                else{
                    // If the node has both children
                    if(ptr->left){
                        // Find the maximum node in the left subtree
                        temp = max(ptr->left) ;
                        if(temp->left){
                            // Set the parent of the left child of the maximum node to the parent of the maximum node
                            temp->left->parent=temp->parent;
                        }
                        // Fix the parent pointer of the maximum node
                        fix_parent(temp,temp->left);
                    }
                    else{
                        // Find the minimum node in the right subtree
                        temp = min(ptr->right) ;
                        if(temp->right){
                            // Set the parent of the right child of the minimum node to the parent of the minimum node
                            temp->right->parent=temp->parent;
                        }
                        // Fix the parent pointer of the minimum node
                        fix_parent(temp,temp->right);
                    }
                    // Replace the data of the node with the data of the maximum or minimum node
                    ptr->id = temp->id ;
                    ptr->name = temp->name ;
                    ptr->bdate.day = temp->bdate.day ;
                    ptr->bdate.month = temp->bdate.month ;
                    ptr->bdate.year = temp->bdate.year ;
                    ptr->mother_name = temp->mother_name ;
                    ptr->address = temp->address;
                    ptr->life_status = temp->life_status ;
                }
                    // Delete the node
                    delete temp ;
                    temp =NULL;
                    // Decrement the count of nodes
                    count--;
                }
                // Return true to indicate that the deletion was successful
                return true;
                }

        }// If the tree is empty or the node with the given id is not found, return false
    return false;
    }
    // Function to find the node with the maximum value in the subtree rooted at 'ptr'
node * bst::max(node*ptr) {
    // If the subtree is not empty
    if(ptr){
        // Traverse to the rightmost node
        while(ptr->right){
            ptr=ptr->right ;
        }
    }
    // Return the rightmost node which has the maximum value
    return ptr ;
}

// Function to find the node with the minimum value in the subtree rooted at 'ptr'
node* bst ::min(node*ptr){
    // If the subtree is not empty
    if(ptr){
        // Traverse to the leftmost node
        while(ptr->left){
            ptr=ptr->left ;
        }
    }
    // Return the leftmost node which has the minimum value
    return ptr ;
}
// Function to check if a node is the root of the tree
bool bst::is_root(node *ptr){
    // If the node is not null
    if(ptr){
        // Return true if the parent of the node is null, meaning the node is the root
        return ptr->parent==NULL ;
    }
    // If the node is null, return false
    return false ;
}

// Function to check if a node is the left child of its parent
bool bst:: is_left(node*ptr){
    // If the node and its parent are not null
    if(ptr&&ptr->parent){
        // Return true if the id of the node is less than the id of its parent, meaning the node is the left child
        return ptr->id<ptr->parent->id ;
    }
    // If the node or its parent is null, return false
    return false ;
}
enum{change_id,change_name,change_mother_name,change_date,change_address,change_ls};
// Function to update a node with a specific id in the tree
bool bst:: update(unsigned int id ,unsigned int change_parameter){
    // Search for the node with the given id
    node *ptr = search(id) ;
    // If the node is found
    if(ptr){
        // Switch on the change_parameter to determine what to update
        switch(change_parameter){
        case change_ls :{
           // If the change_parameter is change_ls, toggle the life_status of the node
           ptr->life_status=(ptr->life_status==alive)?dead:alive;
        }break;
        case change_name:{
            // If the change_parameter is change_name, update the name of the node
            cout<<endl<<"\nEnter the new name" ;
            ptr->name=""  ;
            cin>>ptr->name;
        }break;
        case change_mother_name:{
            // If the change_parameter is change_mother_name, update the mother_name of the node
            cout<<endl<<"\nEnter the new name" ;
            ptr->mother_name=""  ;
            cin>>ptr->mother_name;
        }break;
        case change_address:{
            // If the change_parameter is change_address, update the address of the node
            cout<<endl<<"\nEnter the new address" ;
            ptr->address=""  ;
            cin>>ptr->address;
        }break;
        case change_id :{
            // If the change_parameter is change_id, update the id of the node
            node *node_cpy =get_node(*ptr);
            do{
                cout<<endl<<"\nEnter the new ID" ;
                cin>>node_cpy->id ;
            }while(insert(*node_cpy)==false) ;
            del(ptr->id) ;
            delete node_cpy ;
            node_cpy =NULL;
        }break ;
    case change_date:{
        cout<<endl<<"\nEnter the date (year,month,day)";
        cin>>ptr->bdate.year>>ptr->bdate.month>>ptr->bdate.day;
    }break;
       default:return false ;
        }
        // Return true to indicate that the update was successful
        return true;
    }
    // If the node with the given id is not found, return false
    return false;
}
// Function to delete the entire tree
node* bst ::del_tree(node*ptr) {
    // If the tree is empty, return null
    if(ptr==NULL){
        return NULL ;
    }
    // If the node has a left child, delete the left subtree
    if(ptr->left){
        ptr->left =del_tree(ptr->left)  ;
    }
    // If the node has a right child, delete the right subtree
    if(ptr->right){
        ptr->right =del_tree(ptr->right) ;
    }
    // If the node is not the root
    if(!is_root(ptr)){
        // Fix the parent pointer of the node
        fix_parent(ptr,NULL);
        // Set the parent of the node to null
        ptr->parent=NULL ;
        // Delete the node
        delete ptr ;
        // Set the pointer to the node to null
        ptr = NULL ;
    }
    // If the node is the root
    else if(root){
        // Delete the root
        delete root ;
        // Set the root to null
        root =NULL ;
    }
    // Return null
    return NULL;
}
// Function to print the details of a node
void bst ::show_node(node*ptr){
    // If the node is not null
    if(ptr){
        // Print the id, name, mother's name, date of birth, address, and life status of the node
        cout<<endl<<"\nSocial security number : "<<ptr->id;
       cout<<endl<<"\nFull Name : "<<ptr->name;
        cout<<endl<<"\nMother's name : "<<ptr->mother_name ;
        cout<<endl<<"\nDate of birth : "<<ptr->bdate.month<<"/"<<ptr->bdate.day<<"/"<<ptr->bdate.year;
        cout<<endl<<"Address : "<<ptr->address;
        cout<<endl<<"Life status : ";
        string str =(ptr->life_status==alive)?"\nAlive":"\nDead" ;
        cout<<str;
    }
}

// Function to print the nodes of the tree in inorder traversal
void bst ::inorder(node*ptr){
    // If the tree is empty, return
    if(ptr==NULL){
        return ;
    }
    // If the node has a left child, print the left subtree
    if(ptr->left){
        inorder(ptr->left);
    }
    // Print the node
    if(ptr){
        show_node(ptr) ;
    }
    // If the node has a right child, print the right subtree
    if(ptr->right){
        inorder(ptr->right);
    }
}


    void civil_rec::insert_person(void){
        node ptr;
        do{
        cout<<"\nSocial security number : ";
        cin>>ptr.id;
        }while(tree.search(ptr.id)!=NULL);
        cout<<"\nFull Name : ";
        cin>>ptr.name;
        cout<<"\nMother's name : ";
        cin>>ptr.mother_name ;
        cout<<"\nDate of birth (month/day/year): ";
        cin>>ptr.bdate.month>>ptr.bdate.day>>ptr.bdate.year;
        cout<<"Address : ";
        cin>>ptr.address;
        cout<<"Life status :{1:alive}{0:dead}"<<endl;
        cin>>ptr.life_status ;
        tree.insert(ptr) ;
    }
    void civil_rec::search_for(void) {
        unsigned int id  ;
        cout<<endl<<"Enter the ID" ;
        cin>>id ;
        node*ptr = tree.search(id) ;
        if(ptr){
            tree.show_node(ptr) ;
        }
        else{
            cout<<"\nNot found!";
        }
    }
    void civil_rec::del_person(void) {
        unsigned int id  ;
        cout<<"\nEnter the ID" ;
        cin>>id ;
        bool logic= tree.del(id) ;
        if(logic){
            cout<<endl<<"\nDeleted" ;
        }
        else{
            cout<<endl<<"\nNot found!";
        }
    }
    void civil_rec::update_person(void){
        unsigned int id ,ch_p  ;
        cout<<endl<<"\nEnter the ID" ;
        cin>>id ;
        cout<<endl<<"\nEnter change parameter";
        cout<<endl<<"\n{0:id},{1:change_name},{2:change mother name}\n,{3:change_date},{4:change_address},{5:change ls}";
        cin>>ch_p;
        bool logic= tree.update(id,ch_p) ;
        if(logic){
            cout<<endl<<"Success!";
        }
        else{
            cout<<endl<<"\nNot found!";
        }
    }
    void civil_rec::show_rec(void) {
        tree.inorder(tree.get_root());
    }
    void civil_rec::del_rec(void) {
       tree.del_tree(tree.get_root()) ;
    }
int main(){
    civil_rec cr ;
    int choice;
while(1){
    cout<<"\nCivil Record Simulation";
    cout<<endl<<"\n1---Insert a person"
    "\n2---Search for a person\n3---update a person's data"
    "\n4---delete a person\n5---show the whole record\n"
    "6---delete the whole record\n7---exit\nChoice : ";
    cin>>choice ;
    switch(choice){
        case 1:{
            cr.insert_person() ;
        }break;
        case 2:{
            cr.search_for() ;
        }break;
        case 3:{
            cr.update_person() ;
        }break;
        case 4:{
            cr.del_person() ;
        }break;
        case 5:{
            cr.show_rec() ;
        }break;
        case 6:{
            cr.del_rec() ;
        }break;
        case 7:{
            cout<<endl<<"Thanks for using the software :)\n" ;
            system("pause");
            exit(0) ;
        }break;
        default:{
        cout<<endl<<"\nWrong input";
        }
    }
}

}
