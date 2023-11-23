#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define max 40
int top = -1 ;
int stack_arr[max] ;
void push(int d ){
if(top==max-1){
    printf("\nOverflow") ;
}
else{
    stack_arr[++top] = d ;
}
}
int pop(){
if(top==-1){
    printf("\nUnderflow");
}
else{
    return stack_arr[top--] ;
}
}
//return nearest prime number of the sent value
int near_prime(int limit){
for(int i = limit;i>=2;i--){
int flag = 0;
    for(int j = 2;j<=sqrt(i);j++){
        if(i%j==0){
            flag = 1  ;
        }
    }
if(flag==0){
return i;
}
}
}
//to make sure the sent value is prime
int is_prime(int d ){
for(int i = 2;i<=sqrt(d);i++){
    if(d%i==0){
        return 0 ;
    }
}
return 1 ;
}
//prints elements of a stack
void show(){
puts("");
for(int i = top  ;i>=0;i--){
    printf("%d ",stack_arr[i]);
}
}


void prime_fact(int d){
//if d is prime the program takes a constant time O(1)
if(is_prime(d)){
push(d) ;
return ;
}
//if the sent value isn't prime then we search for the nearest prime number 
//next to the square root of the sent value (O(sqrt(n))) (note : not sure if it's the right time complexity correct me please if i'm wrong) 
int prime = near_prime(sqrt(d));
while(d>1){
    if((d%prime)==0){
        push(prime);
        d/=prime;
    }
    else{
        prime =near_prime(prime-1);
        }
}
}


int main()
{
prime_fact(12121212);
show();

    return 0;
}
