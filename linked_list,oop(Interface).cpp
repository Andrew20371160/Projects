#include <iostream>

using namespace std;
struct node {
int data  ;
node * next ;
};
class linked_list{
private:
    node * head ;
public :
    linked_list(){
    head = NULL ;
    }
    ~linked_list(){
    delete []head ;
    cout<<"deleted "<<endl ;
    }

    node *add_at_empty(int d );
    void add_at_end(int d ) ;
    void add_at_beg(int d ) ;
    void show() ;
    void add_at_pos(int pos , int d ) ;
    int list_size() ;
    void del_at_beg();
    void del_last_node() ;
    void del_at_pos(int pos );
    void del_list() ;
    void adjust_node(int pos ,int newd) ;
    void bsort() ;
    void swap_nodes(node * head1 , node * head2){
        int temp = head1->data ;
        head1 ->data = head2->data ;
        head2 ->data = temp ;
    }
    void add_via_user() ;
    void delete_via_user() ;
    void interface() ;
    void adjust_node_via_user() ;
};
void linked_list ::adjust_node_via_user(){
int pos , d ;
cout<<"enter the node's position ";
cin>>pos  ;
cout<<"\n enter the new data " ;
cin>>d ;
adjust_node(pos,d ) ;

interface() ;
}
void linked_list :: bsort(){
node * head1  = head  ;
node*head2 = head ->next ;
while(head1->next!=NULL){
        head2= head1->next ;
        while(head2!=NULL){
            if(head1->data >head2->data){
                swap_nodes(head1,head2) ;
            }
            head2 = head2 ->next ;
        }
head1 = head1->next  ;

}
interface() ;
}
void linked_list ::del_list(){
if(head ==NULL){
    cout<<"\n list is empty ";
    return  ;
}
else if (head ->next ==NULL){
    delete[] head ;
    head = NULL ;
}
else {
node *  ptr = head ;
while(head !=NULL){
    ptr = head ;
    head = head ->next ;
    delete[] ptr ;
}

}
interface();
}
void linked_list ::del_last_node(){
if(head ==NULL){
    cout<<"\n list is empty ";
    return  ;
}
else if (head ->next ==NULL){
    delete[] head ;
    head = NULL ;
}
else {
  node * ptr  = head ;
  while(ptr ->next ->next !=NULL){
    ptr = ptr->next ;
  }
  free(ptr->next) ;
  ptr ->next = NULL ;
}
}
void linked_list :: del_at_beg(){
if(head ==NULL){
    cout<<"\n list is empty " ;
    return ;
}
else if (head ->next ==NULL){
    delete[]head ;
    head = NULL ;
}
else {
    node * temp  = head ;
    head = head->next ;
    delete[] temp ;
    temp = NULL ;
 }
}
void linked_list :: add_at_pos(int pos , int d ){
 if(head ==NULL && pos !=1){
    cout<<"denied (List is empty )"<<endl;
    return ;
 }
 else if(pos <0 || pos > list_size()+1){
    cout<<"denied \n ";
    return ;
}
else if (pos ==1|| pos ==0 ){
    add_at_beg(d) ;
    return ;
}

else if(pos== list_size()+1){
    add_at_end(d) ;
return ;

}
else {
    pos --;
    node * ptr = head ;
    while(pos != 1){
        ptr = ptr->next ;
        pos-- ;
    }
    node * temp =add_at_empty(d) ;
    temp->next = ptr->next ;
    ptr ->next= temp ;

}
}
void linked_list ::adjust_node(int pos , int newd ){
 if(head ==NULL && pos !=1){
    cout<<"denied (List is empty )"<<endl;
    return ;
 }
 else if(pos <0 || pos > list_size()+1){
    cout<<"denied \n ";
    return ;
}
else if (pos ==1|| pos ==0 ){

    head->data =newd ;
    return ;
}

else if(pos== list_size()+1){
node* ptr  =head;
while(ptr ->next !=NULL){
    ptr = ptr->next ;
}
ptr ->data =newd ;
return ;

}
else {
    pos --;
    node * ptr = head ;
    while(pos != 1){
        ptr = ptr->next ;
        pos-- ;
    }
    ptr->next->data = newd ;
}
}
void linked_list :: del_at_pos(int pos ){
 if(head ==NULL && pos !=1){
    cout<<"denied (List is empty )"<<endl;
    return ;
 }
 else if(pos <0 || pos > list_size()+1){
    cout<<"denied \n ";
    return ;
}
else if (pos ==1|| pos ==0 ){
    del_at_beg() ;
    return ;
}

else if(pos== list_size()+1){
del_last_node() ;
return ;

}
else {
    pos --;
    node * ptr = head ;
    while(pos != 1){
        ptr = ptr->next ;
        pos-- ;
    }
    node * temp = ptr ->next ;
    ptr->next = ptr->next ->next ;
    free(temp) ;
    temp = NULL ;

}
}
node * linked_list ::add_at_empty(int d ){
node * temp = new node ;
temp->next = NULL ;
temp->data = d ;
return temp ;
}
void linked_list::add_at_beg(int d ){
if(head ==NULL){
    head = add_at_empty(d)  ;
    return  ;
}
else if (head ->next == NULL){
    node *temp = add_at_empty(d);
    temp->next = head ;
    head = temp ;

}
else {
    node * temp = add_at_empty(d) ;
    temp->next = head ;
    head = temp ;
}
}
int linked_list :: list_size() {
         int s = 0 ;
    if(head ==NULL){
        return 0 ;
    }
    node * ptr = head ;
    while(ptr !=NULL){
        ptr = ptr->next ;
    s++ ;
    }
    return s ;

};
void linked_list ::add_at_end(int d){

    if(head ==NULL ){
        head = add_at_empty(d) ;
    }
    else if (head->next ==NULL){
        node* temp = add_at_empty(d) ;
        temp->next = NULL ;
        temp->data =  d  ;
        head ->next =  temp ;
    }
    else {
        node * ptr  = head ;
        while(ptr->next != NULL){
            ptr = ptr->next ;
        }
        node * temp = add_at_empty(d) ;
        temp->next = NULL ;
        ptr->next = temp ;
    }
}

void linked_list :: show(){
cout<<endl ;
if(head ==NULL){
    cout<<"\n list is empty ";
    return ;
}
node * ptr = head ;
while(ptr !=NULL){
    cout<<ptr->data<<" " ;
    ptr = ptr->next ;
}
interface() ;
}
void linked_list::add_via_user(){
int pos ,data ;

cout<<"\n enter the position " <<endl;
cin>>pos ;
cout<<"\n enter the data "<<endl ;
cin>>data ;
add_at_pos(pos,data) ;
interface() ;
}
void linked_list :: delete_via_user(){
int pos ;
cout<<"\n enter the position " ;
cin>>pos ;
del_at_pos(pos) ;
interface() ;
}
void linked_list :: interface() {
int n  ;
while(1){
cout<<"\n 1- add a node \n 2- delete a node \n 3- delete the list \n 4- sort the list \n 5-show the list \n 6-adjust a node \n 7- quit " ;
cin>>n ;
switch (n)
{
case 1 : add_via_user() ;
    break;
case 2 : delete_via_user() ; break ;
case 3 : del_list() ;break ;
case 4 : bsort() ;break ;
case 5 : show() ;break ;
case 6 :adjust_node_via_user() ;break ;
case 7: exit(0) ;

default:
    cout<<"\n wrong choice ";
    interface() ;
    break;
}

}


}

int main()
{
linked_list l1 ;
l1.interface() ;

    return 0;
}
