#include <iostream>
#include<cstring>
using namespace std;
#define MAX 100
struct node{
int digit;
node * next ;
};
//get memory for a new digit
node * get_dig(int d ){
node * newp= new node ;
newp->digit = d ;
newp->next = NULL ;
return newp ;
}
//Least significant digit at the head
void add_at_beg(int d , node **head){
if(*head==NULL){
    *head= get_dig(d) ;
}
else{
    node * dig= get_dig(d);
    dig->next =*head ;
    *head = dig ;
}
}
//Convert a string of numbers to a list of digits
void str2num(char * str , node **head,int s  ){
int i = 0   ;
while(i<s){
    add_at_beg(*(str+i)-'0',head );
    i++  ;
}
}
//display the list of digits in reverse
//since we are working with the number in reversed order
void show(node * head){
if(head ==NULL){
    return  ;
}
else{
    show(head->next) ;
    cout<<head->digit;

}
}
//We have to take care of memory aswell
void del_num(node **head){
if(*head==NULL){
    return ;
}
else{
while(*head){
    node *temp= *head ;
    (*head)=(*head)->next ;
    free(temp); temp  = NULL;
}
}
}
//Number of digits of a number
int num_size(node*head){
int i = 0 ;
while(head){
    head = head->next ;
    i++ ;
}
return i  ;
}
//this function is used in add_num(node * n1,node*n2,node**sum)
void rev_num(node **head){
int n = num_size(*head) ;
if(n<2){
    return ;
}
else{
    node * prev = (*head)->next ;
    node * second = prev->next ;
    (*head)->next=NULL ;
    prev->next= (*head) ;
    while(second){
        (*head) = prev;
        prev= second ;
        second= second->next ;
        prev->next= (*head) ;
    }
(*head) = prev ;
}
}
//in this function we check the list of digit from lower order to higher order
void fix_num(node **head){
if(*head){
node * ptr = *head ;
while(ptr->next!=NULL){
//if a digit in a node is bigger or equal to 10 we subtract 10 from the digit
//and then add a 1 to the next digit (like normal maths)
    if(ptr->digit>=10){
        ptr->digit-=10 ;
        ptr->next->digit++ ;
    }
    ptr = ptr->next ;
}
//last loop was until last digit so if last digit is >=10
//we add a new node at the end of the list(Most significant bit or digit)
if(ptr->digit>=10){
    ptr->digit-=10 ;
    node *newp = get_dig(1) ;
    ptr->next=  newp ;
}
}
}
//Here we add the 2 lists of digits and every sum is put in a separate node
//Doesn't matter if sum >=10 as we have a fixing function for that
void add_num(node * n1 , node * n2 , node **sum){
while(n1&&n2){
    add_at_beg(n1->digit+n2->digit,sum) ;
    n1=n1->next ;    n2=n2->next ;
}
while(n1){
    add_at_beg(n1->digit,sum) ;
    n1 = n1->next;
}

while(n2){
    add_at_beg(n2->digit,sum) ;
    n2 = n2->next;
}
//Here we reversed the number to its normal order of digits
//so we have to reverse it again as fix_num(node**head)
//fixes each digit from lower order to higher order
rev_num(sum);
fix_num(sum) ;
}

int main(){
node * n1 = NULL;
node * n2 = NULL;
node *sum = NULL;
char str1[MAX] ;
char str2[MAX] ;
cout<<"Enter the first number : ";
cin>>str1 ; 
cout<<"Enter the second number : ";
cin>>str2 ; 
str2num(str1,&n1,strlen(str1)) ;
str2num(str2,&n2,strlen(str2)) ;
add_num(n1,n2,&sum) ;
show(n1) ;cout<<" + ";show(n2) ;
cout<<" = ";show(sum);
del_num(&n1);
del_num(&n2);
del_num(&sum);
system("pause");
return 0;
}
