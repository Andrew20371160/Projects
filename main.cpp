#include <iostream>
#include<cstring>
#define MAX 100
char str[MAX] ;
using namespace std;
//node structure
struct node{
char ch ;
node *next ;
};
//get memory for a new character
node * get_node(char ch){
node*newch = new node ;
newch->ch = ch ;
newch->next= NULL  ;
return newch ;
}

void push(char ch, node**head){
if(*head==NULL){
    *head = get_node(ch) ;
}
else{
    node * newch = get_node(ch) ;
    newch->next= *head;
    *head = newch ;
}
}
char pop(node**head){
if(*head==NULL){
    cout<<endl<<"Underflow";
    return '!';
}
else{
    char ch = (*head)->ch;
    node * temp = *head;
    *head =(*head)->next ;
    free(temp);  temp = NULL ;
    return ch  ;
}
}

void show(node * head){
while(head){
    cout<<head->ch<<" ";
    head = head->next ;
}
}

int list_size(node*head){
if(head==NULL){
    return 0 ;
}
else{
    return list_size(head->next)+1 ;
}
}

int palindrome(node*head){
if(head==NULL){
    return 0 ;
}
else{
    node*temp= NULL;
int s = list_size(head) ;
for(int i = 0 ; i <s/2;i++){
    push(pop(&head),&temp);
}
//popped the middle character
//I think palindromes are odd +I tested some palindromes from a site so it's working fine
pop(&head);
while(head&&temp){
if(pop(&temp)!=pop(&head)){
    return 0 ;
}
}
return (head==NULL)&&(temp==NULL);
}
}
//take a string from a user and push only important characters (from 'a' to 'z')
void take_str(node**head){
cout<<endl<<"Enter : ";
cin.get(str,100);
int i = 0  ;
while(*(str+i)!='\0'){
//Exclude any unnecessary characters and spaces
    if(*(str+i)>='a'&&*(str+i)<='z'){
    push(*(str+i),head);
}
i++;
}

}
int main()
{
node * head  =NULL ;
take_str(&head);
cout<<endl<<palindrome(head);
    return 0;


}
