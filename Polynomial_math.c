#include <stdio.h>
#include <stdlib.h>
//Term or node structure of a polynomial
typedef struct node{
int exp ;
float coef;
struct node *next ;
}node ;
//Get memory for a new node
node * get_node(int exp,float coef ){
node * p = malloc(sizeof(node));
p->exp= exp ;
p->coef= coef ;
p->next = NULL ;
return p ;
}
//This function sorts the terms while you enter them
//from high order exponent to low order one for ex(2X^2+3X^2 +2X1)
//Yes X^2 is repeated this case is handled by next function
void get_poly(node ** head ,int exp , float coef){
if(*head==NULL){
    *head = get_node(exp,coef);
    return ;
}
node * newnode = get_node(exp,coef) ;
if(exp>=(*head)->exp){
    newnode->next= *head  ;
    (*head) = newnode ;
}
else{
    if((*head)->next==NULL){
        (*head)->next = newnode;
    }
    else{
        node * ptr =(*head) ;
        do{
        if(exp>=ptr->next->exp){
            break ;
        }
        ptr =ptr->next;
        }while(ptr->next!=NULL) ;
        if(ptr->next==NULL){
            ptr->next= newnode ;
        }
        else{
            newnode->next =ptr->next ;
            ptr->next = newnode;
        }
    }
}
}
//This function solves the problem of repeated terms with same exponent by adding the coef
//of same exp (elementary math) & old polynomial is deleted during the process so memory isn't wasted
void fix_poly(node * oldp,node**newp){
node * ptr = oldp;
node*temp = oldp ;
while(ptr!=NULL){
int exp = ptr->exp ;
float coef = 0 ;
//Important node : check first if ptr !=NULL
//so no errors happen when you try to access the exp of a NULL pointer(open circuit process)
while(ptr&&exp==ptr->exp){
    coef+=ptr->coef;
    ptr = ptr->next;
    free(temp) ; temp = ptr ;
}
get_poly(newp,exp,coef) ;
}
}
//A simple printing function the tricky part was not to print "+" at the end of a polynomial
void show_poly(node * head) {
if(head==NULL){
    return ;
}
puts("");
node * ptr = head ;
while(ptr!=NULL){
    printf("(%.2f)X^%d ",ptr->coef,ptr->exp);
ptr =ptr->next;
if(ptr==NULL){
    printf(" ");
}
}
}
//Adds 2 polynomials into a new polynomial while keeping the 2 polynomials
//in case you want to perform another operation
node*add_poly(node*p1,node*p2){
node *psum =NULL;
while(p1!=NULL&&p2!=NULL){
if(p1->exp==p2->exp){
    get_poly(&psum,p1->exp,p1->coef+p2->coef) ;
    p1=p1->next ; p2= p2->next ;
}
else if(p1->exp>p2->exp){
    get_poly(&psum,p1->exp,p1->coef) ;
    p1=p1->next ;
}
else{
    get_poly(&psum,p2->exp,p2->coef);
    p2=p2->next;
}
}
//Next lines if one of the 2 polynomials has more terms than the other
while(p1!=NULL){
get_poly(&psum,p1->exp,p1->coef) ;
p1=p1->next ;
}
while(p2!=NULL){
    get_poly(&psum,p2->exp,p2->coef);
    p2=p2->next;
}
return psum;
}
//multiply 2 polynomials into a new one and fixing the polynomial in the process with (poly_fix)function
node * multy_poly(node *p1 ,node *p2){
//unfixed poly
node *pmulty1 =NULL ;
//final polynomial
node *fpoly = NULL ;
node *ptr2 = p2 ;
while(p1!=NULL){
    ptr2 = p2 ;
    while(ptr2!=NULL){
      get_poly(&pmulty1,p1->exp+ptr2->exp,p1->coef*p2->coef);
      ptr2 = ptr2->next ;
    }
    p1 =p1->next ;
}
fix_poly(pmulty1,&fpoly);
return fpoly ;
}
//Deleting every element of a polynomial
node *del_poly(node*head){
if(head==NULL){
    return head ;
}
else {
    node *temp = head ;
    while(head!=NULL){
        head = head->next ;
        free(temp); temp= NULL ;
        temp = head ;
    }
}
return head ;
}

void get_poly_from_user(node **poly){
int num ,coef,exp;
printf("\nEnter number of terms of the polynomial : ") ;
scanf("%d",&num) ;
for(int i =0 ; i <num; i++){
    printf("\nEnter the coef for term number %d : ",i+1) ;
    scanf("%d",&coef) ;
    printf("\nEnter the exponent for term number %d : ",i+1);
    scanf("%d",&exp) ;
    get_poly(poly,exp,coef) ;
}
}
//Checks if user Entered polynomials or not
void check_poly(node**p1,node **p2){

if(*p1==NULL&&*p2==NULL){
node *newp1 =NULL ;
node *newp2 =NULL ;
printf("You need to Enter polynomials first");
get_poly_from_user(p1);
get_poly_from_user(p2);
fix_poly(*p1,&newp1) ;
fix_poly(*p2,&newp2) ;
show_poly(newp1) ;
show_poly(newp2) ;
*p1 = newp1 ;
*p2 = newp2 ;
}
}


int main()
{
node*p1 =NULL;
node*p2 =NULL;
node*newp1 =NULL;
node*newp2 =NULL;
while(1){
int choice ;
printf("\n1---Enter new polynomials.");
printf("\n2---Add the polynomials.");
printf("\n3---Multiply the polynomials.");
printf("\n4---Exit.\nChoice : ");
scanf("%d",&choice);
switch(choice){
case 1:{
newp1 = del_poly(newp1) ;
newp2 = del_poly(newp2) ;
p1= NULL ;
p2= NULL ;
get_poly_from_user(&p1) ;
get_poly_from_user(&p2) ;
fix_poly(p1,&newp1) ;
fix_poly(p2,&newp2) ;
show_poly(newp1);
show_poly(newp2);
}break ;
case 2:{
check_poly(&newp1,&newp2);
node*psum = NULL ;
psum = add_poly(newp1,newp2);
show_poly(psum) ;
psum =del_poly(psum);
}break ;
case 3:{
check_poly(&newp1,&newp2);
node*pmulty = NULL ;
pmulty = multy_poly(newp1,newp2);
show_poly(pmulty) ;
pmulty =del_poly(pmulty);
}break ;
case 4:{
printf("Thanks for using :)\n");
system("pause");
exit(0);
}break ;
default:{
printf("\nWrong input\n") ;
}
}
}


    return 0;
}
