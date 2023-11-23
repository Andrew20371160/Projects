#include <stdio.h>
#include <stdlib.h>
//node structure
typedef struct node {
int data ;
struct node * next ;
}node ;
//get memory for new node
node * get_node(int d ){
node * new_node = malloc(sizeof(node)) ;
new_node->data = d ;
new_node->next = NULL ;
return new_node ;
}
//insertion function
node *insert(int d , node * head){
if(head==NULL){
    head=get_node(d);
return head ;
}
else{
    node*new_node = get_node(d) ;
    if(head->next==NULL){
        new_node->next=NULL ;
        head->next=  new_node;

    }
    else{
        node*ptr = head ;
         while(ptr->next!=NULL){
            ptr=ptr->next;
         }
         new_node->next= NULL ;
         ptr->next = new_node;

    }
}
return head ;
}
//display function
void display(node*head){
puts("");
if(head==NULL){
    printf("\nList is empty");
    return ;
}
while(head!=NULL){
    printf("%d ",head->data);
    head= head->next;
}
}
//reverse nodes function using recursion
void rev_list(node * head,node**rev){
if(head->next==NULL){
//the following line for inserting last node
    *rev= insert(head->data,*rev);
    return ;
}
rev_list(head->next,rev);
*rev=insert(head->data,*rev);

}
int main()
{
node * head =NULL,*rev=NULL ;
for(int i =0 ; i <5 ; i++){
    head=insert(i,head);
}
display(head);
rev_list(head,&rev);
display(rev);
system("pause");
    return 0;
}
