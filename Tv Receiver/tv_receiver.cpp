#include "tv_receiver.h"

// Default constructor
doubly_list ::doubly_list(){
    tail = NULL; // Initialize tail to NULL
    ch_count = 0; // Initialize channel count to 0
}

// Constructor with parameters
doubly_list ::doubly_list(node*data_set,unsigned int size){
    tail=NULL; // Initialize tail to NULL
    if(data_set){
        ch_count=  size; // Set channel count to size
        for(unsigned int i =0 ; i<size; i++){
            add_at_end(data_set[i].ch_name); // Add each channel to the end of the list
        }
    }
}

// Destructor
doubly_list ::~ doubly_list (){
    while(tail){
        del_at_beg(); // Delete each channel from the beginning of the list
    }
}

// Function to get the tail of the list
node* doubly_list::get_tail(void){
    return tail;
}

// Function to get the count of channels
unsigned int doubly_list::get_count(){
    return ch_count;
}

// Function to allocate memory for a new node (channel)
node * doubly_list ::get_node(unsigned int ch_number ,string & name ){
    node * new_node = new node;
    new_node->ch_num = ch_number;
    new_node->ch_name =name;
    new_node->next = new_node;
    new_node->prev = new_node;
    ch_count++;
    return new_node;
}

// Function to add a node at the end of the list
void doubly_list ::add_at_end(string&name){
    if(tail ==NULL){
        tail = get_node(ch_count+1,name);
    }
    else {
        node * new_node =get_node(ch_count+1,name);
        new_node->prev = tail;
        new_node->next = tail->next;
        tail->next->prev = new_node;
        tail->next = new_node;
        tail = new_node;
    }
}
// Function to add a node at the beginning of the list
void doubly_list :: add_at_beg(string& name){
    if(tail ==NULL){
        tail = get_node(1,name); // If the list is empty, create a new node
    }
    else {
       node * new_node = get_node(1,name); // Create a new node
       new_node->next = tail->next; // Set the next of new node as the next of tail
       new_node->prev = tail; // Set the previous of new node as tail
       tail->next->prev = new_node; // Set the previous of the next of tail as new node
       tail->next = new_node; // Set the next of tail as new node
       inc_from(new_node->next,0); // Increment the channel number from the next of new node
    }
}

// Function to increment or decrement the channel number from a starting pointer
void doubly_list ::inc_from(node*starting_ptr,bool decrement =false){
    if(starting_ptr){
        node*ptr = starting_ptr;
        if(decrement){
            do{
                ptr->ch_num--; // Decrement the channel number
                ptr=ptr->next; // Move to the next node
            }while(ptr!=tail->next); // Repeat until we reach the starting pointer
        }
        else{
            do{
                ptr->ch_num++; // Increment the channel number
                ptr=ptr->next; // Move to the next node
            }while(ptr!=tail->next); // Repeat until we reach the starting pointer
        }
    }
}
// Function to search for a node
node * doubly_list ::search(unsigned int ch_num ){
    if(ch_num<1||ch_num>ch_count){
        cout<<"\n denied ";
        return NULL; // Return NULL if the channel number is out of range
    }
    node  * ptr = tail->next;
    do{
        if(ptr->ch_num==ch_num){
            return ptr ; // Return the node if the channel number matches
        }
        ptr= ptr->next ;
     }while(ptr!=tail->next) ;

    return NULL ; // Return NULL if no matching node is found
}

// Function to display the list
void doubly_list :: show(){
    cout<<endl ;
    if(tail){
        node * ptr = tail->next ;
        do{
            cout<<"Channel : "<<ptr->ch_num<<" "<<ptr->ch_name<<endl; // Print the channel number and name
            ptr =ptr->next ;
        }while(ptr !=tail->next ) ;
    }
}

// Function to add a node at a specific position
void doubly_list ::add_at_pos(unsigned int pos,string&name){

    if(pos<=0 || pos>ch_count+1){
        cout<<endl<<"denied "; // Deny if the position is out of range
    }
    else if(pos ==1){
        add_at_beg(name) ; // Add at the beginning if the position is 1
    }
    else if (pos ==ch_count+1){
        add_at_end(name) ; // Add at the end if the position is the last
    }
    else {
       node *new_node = get_node(pos,name) ; // Create a new node
       node*ptr = tail->next;
       while(ptr->ch_num!=pos){
            ptr=ptr->next; // Find the node at the position
       }
       new_node->next=ptr; // Set the next of new node as ptr
       new_node->prev=ptr->prev ; // Set the previous of new node as the previous of ptr
       ptr->prev->next= new_node; // Set the next of the previous of ptr as new node
       ptr->prev= new_node; // Set the previous of ptr as new node
    }

}
// Function to delete a node at the beginning of the list
void doubly_list ::del_at_beg(){
    if(tail){
        if(tail->next==tail){
            delete tail; // Delete the node if it's the only node in the list
            tail = NULL;
        }
        else {
            node * temp  = tail->next;
            tail->next = temp->next; // Set the next of tail as the next of temp
            temp->next->prev = tail; // Set the previous of the next of temp as tail
            delete temp; // Delete temp
            temp = NULL;
            inc_from(tail->next,1); // Decrement the channel number from the next of tail
        }
        ch_count--;
    }
}

// Function to delete a node at the end of the list
void doubly_list ::del_at_end(){
    if(tail){
        if(tail->next==tail){
            delete tail; // Delete the node if it's the only node in the list
            tail = NULL;
        }
        else {
            node * temp = tail;
            tail = tail ->prev; // Set tail as the previous of tail
            tail->next = temp->next; // Set the next of tail as the next of temp
            temp->next->prev = tail; // Set the previous of the next of temp as tail
            delete temp; // Delete temp
            temp = NULL;
        }
        ch_count--;
    }
}

// Function to delete a node at a specific position
void doubly_list ::del_at_pos(unsigned int pos ){
    if(pos<=0 || pos >ch_count){
        cout<<endl<<"denied "; // Deny if the position is out of range
    }
    else if(pos ==1){
       del_at_beg(); // Delete at the beginning if the position is 1
    }
    else if (pos ==ch_count+1){
        del_at_end(); // Delete at the end if the position is the last
    }
    else {
        node*ptr = tail->next;
        while(ptr->ch_num!=pos){
            ptr=ptr->next; // Find the node at the position
        }
        ptr->prev->next= ptr->next; // Set the next of the previous of ptr as the next of ptr
        ptr->next->prev = ptr->prev; // Set the previous of the next of ptr as the previous of ptr
        inc_from(ptr->next,1); // Decrement the channel number from the next of ptr
        delete ptr; // Delete ptr
        ptr = NULL;
        ch_count--;
    }
}
// Function to delete all nodes in the list
void doubly_list::del_all(){
    while(tail!=NULL){
        del_at_beg(); // Delete the node at the beginning until the list is empty
    }
}

// Function to sort the list by channel name
void doubly_list ::sort() {
    if(tail ==NULL||tail->next ==tail ){
        cout<<"not enough channels to sort "; // Print a message if there are not enough channels to sort
    }
    else{
        node * ptr1 = tail->next;
        node * ptr2 = ptr1->next;
        do{
            do{
                if(ptr1->ch_name>ptr2->ch_name){
                    swap(ptr1->ch_name,ptr2->ch_name); // Swap the channel names if they are in the wrong order
                }
                ptr2 = ptr2->next; // Move to the next node
            }while(ptr2!=tail->next);

            ptr1= ptr1->next; // Move to the next node
            ptr2= ptr1->next; // Move to the next node
        }while(ptr1!=tail);
    }
}
void doubly_list :: switch_nodes(node * ptr1 , node * ptr2 ){
    if(ptr1&&ptr2){
        if(ptr1==tail){
            tail = ptr2 ;
        }
        if(ptr2==tail){
            tail= ptr1 ;
        }
        //adjust nodes links before and after ptr1
        ptr1->prev->next = ptr2 ;
        ptr1->next->prev = ptr2;
        //adjust nodes links before and after ptr2
        ptr2->prev->next= ptr1 ;
        ptr2->next->prev= ptr1 ;
        //save location of ptr1->next and ptr1->next

        node*pn = ptr1->next ;
        node*pp = ptr1->prev;
        //adjust ptr1 links
        ptr1->next = ptr2->next ;
        ptr1->prev = ptr2->prev ;
        //adjust ptr2 links using previous locations of links
        ptr2->next = pn ;
        ptr2->prev = pp ;
    }
}
// Function to delete all nodes in the list
void doubly_list::del_all(){
    while(tail!=NULL){
        del_at_beg(); // Delete the node at the beginning until the list is empty
    }
}

// Function to sort the list by channel name
void doubly_list ::sort() {
    if(tail ==NULL||tail->next ==tail ){
        cout<<"not enough channels to sort "; // Print a message if there are not enough channels to sort
    }
    else{
        node * ptr1 = tail->next;
        node * ptr2 = ptr1->next;
        do{
            do{
                if(ptr1->ch_name>ptr2->ch_name){
                    swap(ptr1->ch_name,ptr2->ch_name); // Swap the channel names if they are in the wrong order
                }
                ptr2 = ptr2->next; // Move to the next node
            }while(ptr2!=tail->next);

            ptr1= ptr1->next; // Move to the next node
            ptr2= ptr1->next; // Move to the next node
        }while(ptr1!=tail);
    }
}

// Default constructor
receiver::receiver():doubly_list(){
    string empty_ch="Empty receiver";
    doubly_list::add_at_beg(empty_ch); // Add an empty channel at the beginning
    channel_ptr = tail; // Set the channel pointer to the tail
    empty_receiver =true ; // Set the receiver as empty
}

// Constructor with parameters
receiver ::receiver(node*data_set,unsigned int size):doubly_list(data_set,size){
    channel_ptr = tail->next ; // Set the channel pointer to the next of tail
    empty_receiver =false; // Set the receiver as not empty
}

// Destructor
receiver ::~receiver(void){
    doubly_list::del_all(); // Delete all nodes in the list
}

// Overloaded prefix increment operator
void receiver ::operator++(void){
    channel_ptr=channel_ptr->next ; // Move the channel pointer to the next node
}

// Overloaded prefix decrement operator
void receiver ::operator--(void){
    channel_ptr=channel_ptr->prev ; // Move the channel pointer to the previous node
}
    // Function to display the current channel
void receiver::show_cur(void){
    cout<<"channel number : "<<channel_ptr->ch_num<<setw(280)<<channel_ptr->ch_name <<endl;
}

// Function to change the location of channels
void receiver ::change_location(void){
    if(!is_empty()){
        unsigned int n1 ,n2 ;
        node *c1 ,*c2 ;
        cout<<"\n enter channel number " ; cin>>n1 ;
        cout<<"\n enter the other channel number ";cin>>n2;
        if(n1==n2){
            cout<<"\n denied";
        }
        else{
            c1= search(n1) ; // Search for the first channel
            c2= search(n2) ; // Search for the second channel
            swap(c1->ch_name,c2->ch_name) ; // Swap the names of the two channels
        }
    }
}

// Function to check if the receiver is empty
bool receiver ::is_empty(void){
    return empty_receiver==true ;
}

// Function to display the help menu
void receiver ::helper(void){
    cout<<"\n a--add a channel \n ";
    cout<<"(w/s)--to transfer \n ";
    cout<<"d--delete the current channel ";
    cout<<"\n c--change channel location \n";
    cout<<"n--transfer to a channel through unsigned integers \n ";
    cout<<"x--delete all channels ";
    cout<<"\n r--sort channels by alphabetical order\n ";
    cout<<"g--show all channels \n ";
    cout<<"q--quit";
}

// Function to go to a specific channel
void receiver ::get_to(void){
    if(!is_empty()){
        unsigned int n ;
        cout<<"\n enter channel's number ";
        cin>>n ;
        node*ptr =search(n); // Search for the channel
        if(ptr){
            channel_ptr =ptr ; // Set the channel pointer to the found channel
        }
        else{
            cout<<"Not found";
        }
    }
}
// Function to delete the current channel
void receiver ::del_cur(void){
    if(!is_empty()){
        if(ch_count==1){
            channel_ptr->ch_name = "\nEmpty receiver"; // Set the channel name as "Empty receiver" if it's the only channel
            empty_receiver=true ;
        }
        else{
            if(channel_ptr==tail->next){
                del_at_beg(); // Delete at the beginning if the channel pointer is at the next of tail
            }
            else if(channel_ptr==tail){
                del_at_end(); // Delete at the end if the channel pointer is at the tail
            }
            else{
                channel_ptr->prev->next = channel_ptr->next; // Set the next of the previous of the channel pointer as the next of the channel pointer
                channel_ptr->next->prev = channel_ptr->prev; // Set the previous of the next of the channel pointer as the previous of the channel pointer
                delete channel_ptr; // Delete the channel pointer
            }
            channel_ptr = tail->next; // Set the channel pointer to the next of tail
        }
    }
}

// Function to delete all channels
void receiver ::del_all(void){
    doubly_list::del_all(); // Delete all nodes in the list
    string empty_str ="\nEmpty receiver";
    add_at_beg(empty_str); // Add an empty channel at the beginning
    channel_ptr = tail; // Set the channel pointer to the tail
    empty_receiver =true ; // Set the receiver as empty
}
// Function to sort the channels
void receiver ::sort(void){
    doubly_list::sort(); // Call the sort function of the doubly_list class
}

// Function to display the channels
void receiver ::show(void){
    doubly_list::show(); // Call the show function of the doubly_list class
}

// Function to add a channel
void receiver::add(){
    if(is_empty()){
        cout<<"\n enter the channel name ";
        cin>>channel_ptr->ch_name ; // Set the channel name if the receiver is empty
        empty_receiver = false ;
    }
    else{
        string name ="";
        cout<<"\n enter the channel name ";
        cin>>name;
        add_at_end(name); // Add a channel at the end if the receiver is not empty
    }
}

// Function to delete a channel at a specific position
void receiver:: del_at_pos(void){
    if(!is_empty()){
        if(ch_count>1){
            unsigned int ch_n ;
            cout<<"\nEnter the channel's number";
            cin>>ch_n ;
            if(ch_n==channel_ptr->ch_num){
                channel_ptr=tail->next; // Set the channel pointer to the next of tail if the channel number is the same as the channel pointer's channel number
            }
            doubly_list::del_at_pos(ch_n); // Delete the channel at the given position
        }
        else{
            channel_ptr ->ch_name = "Empty receiver" ; // Set the channel name as "Empty receiver" if there's only one channel
            empty_receiver=true ;
        }
    }
}

int main()
{
    receiver rec ; // Create a receiver object
    cout<<setw(300)<<"Loading";
    cout<<endl;
    system("pause") ; // Pause the system
    char ch ;
    cout<<"\n press 'h' for help" ;
    while(1){
        rec.show_cur(); // Show the current channel
        ch= getch() ; // Get a character from the user
        switch(ch){
        case  'w' :  ++rec; break ; // Move to the next channel
        case  's':  --rec; break  ; // Move to the previous channel
        case  'c':{
            rec.change_location() ; // Change the location of channels
        }break ;
        case 'g': rec.show() ;break  ; // Show all channels
        case 'd': rec.del_cur() ;break ; // Delete the current channel
        case 'x' : rec.del_all();break; // Delete all channels
        case 'h': rec.helper();break ; // Show the help menu
        case 'r' : rec.sort(); break ; // Sort the channels
        case 'a' : rec.add();break ; // Add a channel
        case 'q' : cout<<"\n                                   Software made by : Andrew karam \n";
        system("pause");cout<<endl<<setw(300)<<"Loading";    exit(0) ; // Exit the program
        case 'n' :rec.get_to();break; // Go to a specific channel
        default:{
            rec.show_cur(); // Show the current channel if the input is not recognized
        }

        }

    }
return 0;
}
