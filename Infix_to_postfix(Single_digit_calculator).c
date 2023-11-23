#include <stdio.h>
#include<stdlib.h>
char postfix[40];
typedef struct node{
char ch ;
struct node *next ;
}node ;
//get memory for a new node
node *get_node(char ch){
node*newp= malloc(sizeof(node))  ;
newp->ch = ch ;
newp->next = NULL ;
return newp;
}
//push func
void push(char ch , node**head){
if(*head ==NULL){
    *head = get_node(ch)  ;
}
else{
    node*newp = get_node(ch) ;
    newp->next = *head ;
    *head = newp;
}
}
//pop func
char pop(node**head){
if(*head ==NULL){
printf("\nUnderflow");
return 'x';
 }
else{
char ch = (*head)->ch ;
if ((*head)->next==NULL){
    free(*head) ; *head = NULL;
}
else{
    node *temp = *head;
    (*head)=(*head)->next ;
    free(temp) ;temp = NULL;
}
return ch ;
}
}
//power of number function
int power(int x,int pow){
int sum =  1;
for(int i=0;i<pow;i++){
    sum*=x;
}
return sum ;
}
//operations function
int operate(int v1,int v2 , char op){
switch(op){
case '^' :return power(v1,v2) ;break;
case '*' :return v1*v2 ; break;
case '/' : return v1/v2 ; break ;
case '+' :return v1+v2 ; break ;
case '-' : return v1-v2; break;
default : {printf("error"); exit(1);}
}
}
//the higher the precedence the higher is the returned value
int pre_op(char ch){
switch(ch){
case '^' :return 3;break;
case '*' :return 2;break;
case '/' :return 2;break;
case '+' :return 1;break;
case '-': return 1;break;
default :{
return 0 ;
}
}
}
//Evaluates the value of the postfix expression
void value(char *str){
node *val = NULL ;
int i = 0 ;
while(*(str+i)!='\0'){
    if(*(str+i)>='0'&&*(str+i)<='9'){
       push(*(str+i),&val) ;
        }
    else{
    push(operate(pop(&val)-'0',pop(&val)-'0',*(str+i))+'0',&val) ;
    }
i++;
}
printf("%d\n",pop(&val)-'0');
}

//Infix to postfix conversion function
void in_posfix(char * str){
int i =0 ,j=0;
node * op = NULL ;
while(*(str+i)!='\0'){
if(*(str+i)>='0'&&*(str+i)<='9'){
   *(postfix+j)=*(str+i);
   j++;
}
else if(*(str+i)=='('){
    push(*(str+i),&op);
}
else if(*(str+i)==')'){
    char ch ;
    while((ch = pop(&op))!='('){
        *(postfix+j)=ch;
        j++;
    }
}
else {
//until precedence of the operator in the stack is less than the precedence of the new operator
//we keep popping the stack elements into the postfix string
    while(op&&(pre_op(op->ch)>=pre_op(*(str+i)))){
         *(postfix+j)=pop(&op);
          j++;
    }
    push(*(str+i),&op);
}
i++;
}
//for lower priority operators or left ones
while(op){
    *(postfix+j)=pop(&op);
    j++;
}
value(postfix);
}






int main()
{
char infix[40] ;
scanf("%s",infix) ;
in_posfix(infix);
system("\npause");
    return 0;
}
