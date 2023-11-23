#include <stdio.h>
#include <stdlib.h>
#define max 100
char str[max]  ;
typedef struct node {
char ch  ;
struct node * next  ;
}node ;
node * get_node(char ch ){
node *newp = malloc(sizeof(node));
newp->ch = ch ;
newp->next = NULL ;
return newp ;
}
void push(char ch , node**head){
if(*head==NULL){
    *head = get_node(ch)  ;
}
else {
    node*newp = get_node(ch);
    newp->next = *head ;
    *head = newp ;
}
}
char pop(node**head){
if(*head==NULL){
    return 'x' ;
}
else{
    char ch= (*head)->ch ;
    node *temp = *head;
    *head = (*head)->next ;
    free(temp) ; temp = NULL;
    return ch ;
}
}

int closing_brac(char lch,char rch ){
switch(lch){
case '(':{
    return(rch==')');
}break ;
case '[':{
    return(rch==']');
}break ;
case '{':{
    return(rch=='}');
}break ;
case '<':{
    return (rch=='>');
    }break;
default :return 0 ;
}
}
int is_brac(char ch){
return(ch=='('||ch==')'||ch=='['||ch==']'||ch=='{'||ch=='}'||ch=='<'||ch=='>');
}
int nested_brackets(char *str ){
int i = 0  ;
node *head = NULL ;
while(*(str+i)){
if(is_brac(*(str+i))){
if(*(str+i)=='('||*(str+i)=='{'||*(str+i)=='['||*(str+i)=='<'){
        push(*(str+i),&head) ;
       }
    else{
        if(closing_brac(pop(&head),*(str+i))==0){
           printf("Invalid expression");
            return 0 ;
        }

}
}
i++;
}
if(head!=NULL){
printf("Right brackets are more than left brackets");
return 0 ;
}
printf("Valid");
return 1  ;
}


int main()
{
printf("Enter the expression : ") ;
scanf("%s",str);
nested_brackets(str);

     return 0;
}
