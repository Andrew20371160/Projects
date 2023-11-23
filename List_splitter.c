#include <stdio.h>
#include <stdlib.h>
//Divide a linked list into 2 sublists
//node structure
typedef struct {
int data ;
struct node * next ;
}node;
//get memory for new node function
node * get_node(int d){
node * new_node = malloc(sizeof(node)) ;
new_node->next = NULL;
new_node->data=  d ;
return new_node ;
}
//insertion function
node * insert(int d , node * head){
if(head==NULL){
    head= get_node(d) ;
}
else {
    node*ptr = head ;
    while(ptr->next!=NULL){
        ptr = ptr->next ;
    }
    node *new_node = get_node(d);
    ptr->next = new_node;
}
return head ;
}
//display elements of a list
void show(node*head){
printf("\n");
while(head!=NULL){
    printf("%d ",head->data);
    head = head->next;
}
}
//get size of a linked list
int listsize(node *head){
int size = 0 ;
while(head!=NULL){
    head = head->next;
    size++;
}
return size ;
}
//body of the function
void divide(node *head , node**left ,node**right){
if(listsize(head)==0){
    return ;
}

else{
    node * ptr = head ;
    int size = listsize(head);
    for (int i = 0 ; i <size/2;i++){
        *left = insert(ptr->data,*left);
        ptr = ptr->next ;
    }
        for (int i = size/2 ; i <size;i++){
        *right = insert(ptr->data,*right);
        ptr = ptr->next ;
    }
}
}
int main()
{
node *head  = NULL;
for(int i =0  ; i <15;i++){
    head= insert(i+1,head) ;
}
node *left =NULL,*right = NULL  ;
divide(head,&left,&right);
show(head);
show(left) ;
show(right);
    return 0;
}
