#include <iostream>
#include<cstring>
#include<iomanip>
#include<conio.h>
#define max_count 100

using namespace std;
struct node {
int ch_num ;
char *ch_name ;
node * prev ;
node * next  ;
};
class receiver{
node * tail ;
public:
    receiver(){
    tail = NULL;

    }
    ~ receiver (){
    delete[]tail ;
    }
    node * add_at_empty(int d ,char * name );
    void add_at_end(int d , char * name );
    void add_at_beg(int d ,char * name ) ;
    void show() ;
    void add_at_position(int pos , char * name   ) ;
    void del_first_node() ;
    void del_last_node() ;
    void del_at_pos(int pos ) ;
    void del_all_nodes() ;
    void sort_by_name() ;
    node* get_node_by_ch_num(int n) ;
    void switch_nodes(node * ptr1 ,node * ptr2) ;
    node * return_tail(){
    return tail ;
    }
    int chcount() ;
    void interface() ;



};
node * receiver ::add_at_empty(int d ,char * name ){
node * temp = new node ;
temp ->ch_num = d ;
temp->ch_name = new char[strlen(name)+1] ;
strcpy(temp->ch_name,name) ;
temp->next = temp ;
temp->prev = temp  ;
return temp ;
}
void receiver ::add_at_end(int d ,char *name){
if(tail ==NULL){
    tail = add_at_empty(d,name) ;
    return ;
}
else if (chcount()>=max_count ){
    cout<<"\n too man channels in receiver delete a channel to add a new one ";
    return ;
}

else {
node * temp =add_at_empty(d,name) ;
temp->prev = tail ;
temp->next = tail->next ;
tail->next->prev = temp ;
tail->next = temp ;
tail = temp ;
}
}
void receiver :: add_at_beg(int d ,char * name){
if(tail ==NULL){
    tail = add_at_empty(d,name) ;
    return;
}
else if (chcount()>=max_count ){
    cout<<"\n too man channels in receiver delete a channel to add a new one ";
    return ;
}

else {
   node * temp = add_at_empty(d,name) ;
   temp->next = tail ->next ;
   temp->prev = tail->prev ;
   tail->next->prev = temp ;
   tail->next = temp ;
}
}

void receiver :: show(){
cout<<endl ;
if(tail ==NULL){
    cout<<"\n empty receiver " ;
    return ;
}
node * ptr = tail->next ;
do{
cout<<"Channel : "<<ptr->ch_num<<" " <<ptr->ch_name<<endl;
ptr =ptr->next ;

}while(ptr !=tail->next ) ;
}
int receiver ::chcount(){

if(tail ==NULL){
    return 0 ;
}
int s = 0 ;
node * ptr = tail->next ;
do{
s++ ;
ptr = ptr->next ;
}while(ptr !=tail ->next ) ;
return s ;
}
void receiver ::add_at_position(int pos,char * name ){
if(tail ==NULL &&pos !=1){
    cout<<endl<<"receiver has no channels " ;
    return  ;
}
else if(pos<=0 || pos >max_count||pos >chcount()+1){
    cout<<endl<<"denied ";
    return ;
}
else if (chcount()>=max_count ){
    cout<<"\n too man channels in receiver delete a channel to add a new one ";
    return ;
}
else if(pos ==1){
    add_at_beg(pos,name) ;
    node * ptr = tail->next->next ;
    while(ptr !=tail->next){
        ptr->ch_num++;
        ptr =ptr->next ;
    }
    return ;
}
else if (pos ==chcount()+1){
    add_at_end(pos,name) ;
}
else {
int d = pos ;
pos-- ;
node * ptr = tail->next ;
while(pos !=1){
ptr = ptr->next ;
pos-- ;
}

node *temp = add_at_empty(d,name) ;
temp->next = ptr->next ;
temp->prev = ptr ;
ptr->next ->prev = temp ;
ptr->next = temp ;
  ptr = temp->next ;
    while(ptr !=tail->next){
        ptr->ch_num++;
        ptr =ptr->next ;
    }

}


}
void receiver ::del_first_node(){
if(tail ==NULL){
    cout<<"\n receiver is empty " ;
    return  ;
}
else if(tail->next==tail){
    delete[]tail ;
    tail = NULL ;
}
else {
node * temp  = tail->next ;
temp->next ->prev = tail ;
tail->next = temp->next ;
delete[] temp ;
temp = NULL ;
}

}
void receiver ::del_last_node(){
if(tail ==NULL){
    cout<<"\n receiver is empty " ;
    return  ;
}
else if(tail->next==tail){
    delete[]tail ;
    tail = NULL ;
    return ;
}
else {
node * temp = tail ;
tail = tail ->prev ;
tail->next = temp->next ;
temp->next ->prev = tail ;
delete[]temp ;
temp = NULL ;
}
}
void receiver ::del_at_pos(int pos ){

if(tail ==NULL){
    cout<<endl<<"receiver has no channels " ;
    return  ;
}
else if(pos<=0 || pos >max_count||pos >chcount()+1){
    cout<<endl<<"denied ";
    return ;
}

else if(pos ==1){
   del_first_node() ;
    node * ptr = tail->next ;
   do{
        ptr->ch_num-- ;
        ptr= ptr->next ;

   }while(ptr !=tail->next) ;
    return ;
}
else if (pos ==chcount()){
del_last_node() ;
}
else {
pos-- ;
node * ptr = tail->next ;
while(pos !=1){
ptr = ptr->next ;
pos-- ;
}
node * temp = ptr ->next ;
temp->next ->prev = ptr ;
ptr->next =temp->next ;
delete[]temp ;

  ptr = ptr->next ;
    while(ptr !=tail->next){
        ptr->ch_num--;
        ptr =ptr->next ;
    }

}

}
void receiver::del_all_nodes(){
while(tail!=NULL){
    del_first_node() ;
}

}
void receiver :: switch_nodes(node * ptr1 , node * ptr2 ){
swap(ptr1->ch_name,ptr2->ch_name) ;
swap(ptr1->ch_num,ptr2->ch_num) ;
}
void receiver ::sort_by_name() {
if(tail ==NULL||tail->next ==tail ){
    cout<<"not enough channels to sort " ;
    return ;
}
node * ptr1 = tail ;
node*ptr2 = tail->next ;

do{
    while(ptr2!=tail->next){
        if(strcmp(ptr1->ch_name,ptr2->ch_name)>0){
                swap(ptr1->ch_name,ptr2->ch_name) ;

    }

    ptr2 = ptr2->next ;
}
ptr1= ptr1->next;
ptr2= ptr1->next ;


}while(ptr1!=tail);

}
node * receiver ::get_node_by_ch_num(int n ){
if(n<1||n>chcount()){
    cout<<"\n denied ";
    return NULL;
}
node  * ptr = tail;
while(ptr->ch_num!=n){
    ptr= ptr->next ;
 }
 return ptr ;

}
void receiver ::interface(){
cout<<setw(300)<<"TOSHIPA";
cout<<endl;
system("pause") ;
node * ptr = tail ;
char ch ;
cout<<"\n press 'h' for help" ;
while(1){
        if(tail==NULL){
            cout<<"please add a channel ";
     char *name = new char[30] ;
      cout<<"\n enter the channel name ";
     cin>>name ;
        tail = add_at_empty(1,name) ;
        ptr =tail ;

        }

cout<<"channel number : "<<ptr->ch_num<<setw(280)<<ptr->ch_name <<endl;
ch= getch() ;
    switch(ch){
    case 'w' :    ptr=ptr->next ;break ;

    case  's' : ptr = ptr->prev; break  ;
    case 'c':{show() ;
    int n1 ,n2 ;
    node *c1 ,*c2 ;
    cout<<"\n enter channel number " ; cin>>n1 ;
    cout<<"\n enter the other channel number ";cin>>n2;
    if(n1==n2){
        cout<<"\n denied"; break ;
    }
    c1= get_node_by_ch_num(n1) ;
    c2= get_node_by_ch_num(n2) ;
    int temp = c1->ch_num ;
    c1->ch_num = c2->ch_num ;
    c2->ch_num = temp ;
    switch_nodes(c1,c2) ;
    }break ;



    case 'g':show() ;break  ;

    case  'd':{

        if(tail->next==tail){
        del_first_node() ;
        char name[30] ;
        cout<<"\n receiver is empty please add a channel "<<endl;
        cin>>name;
        add_at_beg(1,name) ;
        ptr = tail ;

        }


        else {

        cout<<"\n deleted channel "<<ptr->ch_name<<endl ;
        system("pause") ;
        del_at_pos(ptr->ch_num) ;
        ptr = tail ;
        }
         } break ;
    case 'x' :   {del_all_nodes() ;show() ;
    ptr = NULL ;
      }break;
      case 'h': {
      cout<<"\n a--add a channel \n ";
      cout<<"(w/s)--to transfer \n ";
      cout<<"d--delete the current channel ";
      cout<<"\n c--change channel location \n";
      cout<<"n--transfer to a channel through integers \n ";
      cout<<"x--delete all channels ";
      cout<<"\n r--sort channels by alphabetical order\n ";
      cout<<"g--show all channels \n ";
      cout<<"q--quit";
      cout<<"\n                             Software made by : Andrew Karam \n";


      }
     break ;
    case 'r' : sort_by_name(); show() ; break ;
    case 'a' : {char *name = new char[30] ; cout<<"\n enter the channel name "; cin>>name ; add_at_position(chcount()+1,name) ;}break ;
    case 'q' : cout<<"\n                                   Software made by : Andrew karam \n";
    system("pause");cout<<endl<<setw(300)<<"TOSHIPA";    exit(0) ;
    case 'n' :{int n ; cout<<"\n enter channel's number ";
    cin>>n ;
    if(n<=0 ||n>chcount()){
            cout<<"denied " ; break;
    }
      ptr =get_node_by_ch_num(n);}
      break;


    }

    }
}


int main()
{
receiver r1 ;

r1.add_at_end(1,"mbc") ;
r1.add_at_end(2,"mbc2") ;
r1.add_at_end(3,"mbc3") ;
r1.add_at_end(4,"mbc4") ;
r1.add_at_end(5,"cpc") ;

r1.interface() ;

return 0;
}
