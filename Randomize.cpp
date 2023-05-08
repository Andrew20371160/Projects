#include <iostream>
#include<random>

using namespace std;
//The purpose is to randomize a list elements into another list
//Node structure
struct node {
int data ;
node * next ;
};

class linkedlist{
private :
    node * head ;
public:
    linkedlist(){
    head =NULL ;
    };
    linkedlist(int d){
    head = get_node(d) ;
    }
    node * get_node(int d);
    //The next function is used in randomize() Function (To access the head of a list outside the class functions)
    node * return_head(){
    return head ;
    }
    void add_at_beg(int d );
    void add_at_end(int d );
    void add_at_pos(int pos,int data);
    int list_size();
    void showdata() ;
    void del_first() ;
    void randomize(linkedlist * );
    void del_all() ;
    void copy_list(linkedlist src);

};
//get memory for a new node (used only within class function)
node * linkedlist::get_node(int d){
node * newnode = new node;
newnode->data = d ;
newnode->next = NULL ;
return newnode ;
}
//Add an element at 1st position
void linkedlist::add_at_beg(int d ){
if(head==NULL){
    head = get_node(d);
}
else {
node * newnode = get_node(d);
newnode->next= head;
head = newnode ;
}
}
//Add an element at last position
void linkedlist::add_at_end(int d){
if(head==NULL){
    head = get_node(d) ;
}
else {
    node * newnode = get_node(d);
    node * ptr = head ;
    while(ptr->next!=NULL){
        ptr = ptr->next;
    }
    ptr->next= newnode ;
    newnode->next = NULL ;
}
}
//Add at a position from 1 till list_size()+1
void linkedlist :: add_at_pos(int pos , int data){
if(pos<1||pos>list_size()+1){
    cout<<endl<<"Invalid position";
    return ;
}
else if(pos==1){
   add_at_beg(data);
}
else if(pos ==list_size()+1){
    add_at_end(data) ;
}
else {
    node * ptr = head ;
    node * newnode = get_node(data);
    while((pos--)>1){
        pos--;
        ptr = ptr->next ;
    }
    newnode->next = ptr ->next ;
    ptr->next = newnode ;
}
}
//Get size of a list
int linkedlist::list_size(){
int i  = 0 ;
node * ptr = head ;
while(ptr!=NULL){
    i++;
    ptr = ptr->next;
}
return i ;
}
//Prints all data of a list
void linkedlist::showdata(){
node * ptr = head ;
cout<<endl;
while(ptr!=NULL){
    cout<<ptr->data<<" ";
    ptr = ptr->next ;
}
}
//delete 1st element in a list
void linkedlist ::del_first(){
if(head->next==NULL){
    free(head) ;
    head=NULL ;
}
else {
node * temp = head ;
head = head->next ;
free(temp) ;
temp = NULL  ;
}
}
//Delete every element in a list using previous function
void linkedlist::del_all(){
    node * ptr = head ;
    while(ptr!=NULL){
        ptr = ptr->next;
        del_first();
    }
}
//Randomization function
void linkedlist ::randomize(linkedlist * oldlist){
//Access 1st element of the old list
node *ptr = (*oldlist).return_head();
if(ptr==NULL){
    return;
}
//Next line is mandatory (The new list is empty at first)
add_at_beg(ptr->data) ;
ptr = ptr->next ;
while(ptr!=NULL){
    //Position variable in add_at_pos(int pos,int data)
    //is randomized within the size of a new list (new list size increases every time during the loop execution)
    add_at_pos(1+rand()%list_size(),ptr->data);
    ptr = ptr->next ;
}
(*oldlist).del_all();
}
//Copy list Fucntion
void linkedlist::copy_list(linkedlist src) {
node * ptr = src.return_head() ;
while(ptr !=NULL){
    add_at_end(ptr->data);
    ptr = ptr->next;
}
}
int main()
{
//lrand1 is for randomizing loriginal only
//lrand2 is for randomizing lrand1 only
//lcopy is for not losing original dara
linkedlist loriginal ,lrand1,lrand2,lcopy;
for(int i = 0 ; i <10;i++){
    loriginal.add_at_end(i+1);
}
while(1){
cout<<"\nRandomize\n";
int choice;
cout<<endl<<"1---Show original data"<<endl<<"2---Randomize original data"<<endl<<"3---Randomize the randomized";
cout<<endl<<"4---delete all data"<<endl<<"5---Insert new data"<<endl<<"6---Exit\nChoice : ";
cin>>choice;
switch(choice){
case 1:{
loriginal.showdata() ;
}break ;
case 2 :{
    lrand1.del_all();
    lcopy.copy_list(loriginal) ;
    lrand1.randomize(&lcopy);
    lrand1.showdata();

}break ;
case 3 :{
lrand2.del_all();
lcopy.copy_list(lrand1);
lrand2.randomize(&lcopy);
lrand2.showdata();
}break ;
case 4 :{
loriginal.del_all() ;
lcopy.del_all()  ;
lrand1.del_all() ;
lrand2.del_all() ;

}break;
case 5:{
int data ,  pos ;
cout<<"\nEnter the data";
cin>>data ;
cout<<"\nEnter the position";
cin>>pos ;
loriginal.add_at_pos(pos,data) ;
}break ;
case 6:{
loriginal.del_all();
lrand1.del_all();
lrand2.del_all();
lcopy.del_all();
cout<<"I've had a brain lag doing this randomization (hope you had fun (Andrew :) )\n";
system("pause");
exit(0) ;
}
}
}
    return 0;
}
