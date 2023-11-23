#include <stdio.h>
#include <stdlib.h>
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
//MergeSort function
void merge(node*left , node*right ,node**head){
node*pl = left ;
node*pr = right ;
node*ptr = *head ;
while(pl!=NULL&&pr!=NULL){
    if(pl->data<=pr->data){
        ptr->data = pl ->data ;
        ptr = ptr->next ;
        pl = pl->next;
    }
    else{
        ptr->data =  pr->data ;
        ptr = ptr->next ;
        pr=pr->next ;
    }
}
while(pl!=NULL){
    ptr->data = pl->data ;
    ptr = ptr->next ;
    pl = pl->next;
}
while(pr!=NULL){
    ptr->data = pr->data ;
    ptr = ptr->next ;
    pr = pr->next;
}
}

void mergesort(node**head){
int size = listsize(*head);
if(size<2){
    return ;
}
node *left = NULL ;
node *right = NULL ;
node*ptr = *head ;
for(int i =0 ; i<size/2;i++ ){
    left = insert(ptr->data,left) ;
    ptr = ptr->next ;
}
for(int i =size/2 ; i<size;i++ ){
    right = insert(ptr->data,right) ;
    ptr = ptr->next ;
}
mergesort(&left);
mergesort(&right);
merge(left,right,head);
}
int main()
{
node *head = NULL;
for(int i = 10 ; i >0 ; i--){
    head=insert(i,head) ;
}
mergesort(&head);
show(head);
    return 0;
}
