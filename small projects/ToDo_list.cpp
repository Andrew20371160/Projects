#include <iostream>
#include<cstring>
using namespace std ;

struct node {
char * activity  ;
struct node * next ;

};

class todo{
node * head ;

public :
todo(){
head =NULL ;
}

node * add_at_empty(char * str){
node *act = new node  ;
act ->next = NULL ;
act->activity = (char*)malloc((strlen(str)+1)*sizeof(char)) ;
strcpy(act->activity,str) ;
return act ;
};
void enqueue (){
char str[100] ;
cout<<"\n  enter activity :"<<endl ;
cin.getline(str,100,'&') ;

if(head ==NULL){

    head = add_at_empty(str) ;

}
else if (head->next ==NULL){
     node* temp = add_at_empty(str) ;
    temp ->next = NULL ;
    (head)->next = temp ;

}
else {
 node * ptr = (head) ;
while(ptr->next !=NULL){
    ptr = ptr->next ;
}
node * temp = add_at_empty(str) ;
temp->next= NULL ;
ptr->next  = temp  ;

}

}
char * dequeue(){
if(head ==NULL){
    cout<<"\n TO DO list is empty" ;
    return "x" ;
}
else if((head)->next ==NULL){
    char * str  =  new char[(strlen(head->activity)+1)]  ;
    strcpy(str,head->activity);
    free(head)  ;
    head = NULL ;
return str ;
}
else {
    char * str =  new char[(strlen(head->activity)+1)] ;
    strcpy(str,(head)->activity);
     node  *temp = head ;
    (head) = head->next ;
    free(temp) ;
    temp  = NULL ;
     return str ;
}
}


void show_todo(){
if(head == NULL){
    cout<<"\n list is empty" ;
    return ;
}
int i = 0 ;
node * ptr = head ;
while(ptr !=NULL){
i++ ;
cout<<i<<" - "<<ptr->activity <<endl;
ptr = ptr->next  ;
if(ptr==NULL){
    break ;
}

}
}

void del_list(){
if(head == NULL){
    cout<<"\n list is empty" ;
    return ;
}
node * ptr = head ;
while(ptr !=NULL){
ptr = ptr->next  ;
free(head) ;
head = ptr ;
}
}


};




int main()
{
todo head ;
while(1){
int choice ;
cout<<"\n 1-add activity";
cout<<"\n 2-show activities" ;
cout<<"\n 3-remove 1st activity" ;
cout<<"\n 4-delete to-do list " ;
cout<<"\n 5-quit" ;
cin>>choice ;
switch (choice){

case 1 : {
head.enqueue() ;
}break  ;
case 2 : head.show_todo()  ;break ;
case 3: {char *str ;  str = head.dequeue() ; cout<<endl<<str ;

}break ;
case 4 : head.del_list() ;break ;
case 5 :exit(0)  ;
}
}





    return 0;
}
