#include<iostream>
using namespace std ;
struct cusdata{
char firstname [10] ;
char lastname [10] ;
int accountnumber ;
int totalbalance ;

};
struct link {
cusdata customer;
link* next ;
};
class bank_system {
private:
    link *first ;
public:
bank_system (){
first = NULL ;}
void additem_first() {
    link *put = new link ;
    cout<<" \n enter first name :" ;
    cin>> put->customer.firstname;
    cout<<" \n enter last name ";
    cin>>put->customer.lastname ;
    cout<<"\n enter the account number ";
    cin>>put->customer.accountnumber ;
    cout<<"\n enter total balance ";
    cin>>put->customer.totalbalance ;
    put->next = first ;
    first = put ;
}
void del_link (int  x ){
link*del ;
del = first ;
if (del == NULL){
    cout<<"the list is empty ";
    return ;}
if (del ->customer.accountnumber==x ){
    first  = del->next ;
    return ;}
if (del ->next == NULL){
    cout<<"not deleted ";
    return ;

}
while (del ->next!= NULL ){
    if(del->next->customer.accountnumber== x ){
        del->next = del->next->next ;
        return ;
        }
del = del->next ;



}
cout<<"not deleted \n  ";


}

void update_rec( ){
link * update = new link ;
update = first ;
int x ;
cout<<"enter the account number \n  ";
cin>>x ;
if(update==NULL ){
cout<<"the bank is empty ";
return ;

}
if(update->customer.accountnumber ==x ){
cout<<" \n enter your new record ";
cin>>update->customer.totalbalance ;
return ;
}

while(update->next!= NULL){
if(update->next->customer.accountnumber ==x ){
cout<<" \n enter your new record ";
cin>>update->next->customer.totalbalance ;
return ;
}
update = update->next ;
}
cout<<"the account does't exist ";
}
void search_acc(){
int n ;
link *current = new link ;
current = first ;
cout<<"\n enter the account number ";
cin>>n ;
if(current == NULL){
    cout<<"the list is empty \n ";
    return ;
}
if(current->customer.accountnumber == n){
    cout<<current->customer.firstname<<endl ;
    cout<<current->customer.lastname <<endl ;
    cout<<current->customer.accountnumber <<endl ;
    cout<<current->customer.totalbalance <<endl ;
    return ;


}
while(current->next!= NULL){
        if(current->next->customer.accountnumber == n ){
    cout<<current->next->customer.firstname<<endl ;
    cout<<current->next->customer.lastname <<endl ;
    cout<<current->next->customer.accountnumber <<endl ;
    cout<<current->next->customer.totalbalance <<endl ;
    return ;
}
    current = current->next ;

}
cout<<"The account doesn't exist or deleted ";

}
void exitst_or(){
    int n ;
link *current = new link ;
current = first ;
cout<<"\n enter the account number ";
cin>>n ;
if(current ==NULL){
    cout<<"the list is empty ";
    return ;

}
if(current->customer.accountnumber == n){
cout<<"\n the account exist ";
return ;
}
while(current->next!= NULL){
        if(current->next->customer.accountnumber == n ){
                cout<<"\n The account exist ";
                return;
        }
         current = current->next ;


}

cout<<"the account doesn't exist ";
}
};

int main (){
bank_system b1 ;
int n ;
char ch ;
cout<<"***Acount Information System***"<<endl;
cout<<"Select one option below"<<endl;
cout<<"1-->Add record to the system"<<endl;
cout<<"2-->Show record from the system"<<endl;
cout<<"3-->Search record from the system"<<endl;
cout<<"4-->Update record from the system"<<endl;
cout<<"5-->Delete record from the system"<<endl;
cout<<"6-->Quit the system"<<endl;
do{
cout<<"Enter your choice:\n";
cin>>n ;
switch(n){
case 1 : b1.additem_first(); break ;
case 2 : b1.search_acc(); break ;
case 3 : b1.exitst_or(); break ;
case 4 : b1.update_rec() ; break ;
case 5 : int x ; cout<<"enter the acc num you want to del \n ";cin>>x ;b1.del_link(x); break;
case 6 : exit(0);
default : cout<<"wrong inputs "; exit(0);

}
cout<<"\n do you want another service (y /n ) ";
cin>>ch ;

}while(ch != 'n'  );

    return 0 ;
}

