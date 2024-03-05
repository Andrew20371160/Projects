#include <iostream>
#include <random>
#include <time.h>
using namespace std ;

//this function returns a random sequence of 26 characters each time
char * get_key(void){
char *key = new char[26];
//first initialize the key with zeroes
for(int i = 0 ; i <26;i++){
key[i] = 0 ;
}
//this is used in generating a random integer
srand(time(0)) ;

//put characters from a to z in random indecies
for(int i = 0 ; i <26;i++){
    //get a random index from 0 to 25 (notice the modulus)
    int rand_index = rand()%26;
    //check if the index is not taken
    if(key[rand_index]==0){
        key[rand_index] = 'a' +i ;
    }
    else{
        //find first index that's empty and put the character in
        //to avoid an open loop (or something)
        for(int j = 0 ; j<26;j++){
            if(key[j]==0){
                key[j] = 'a'+i ;
                break ;
            }
        }
    }
}
return key  ;
}

//encryption function
void encrypt(char*str , char *key){
//counter that counts through the string of characters
int counter = 0;
while(str[counter]!='\0'){
    //say we have a key {'d' ,'g' ,'i' ,'j', 'a' ,'s' ,'c', ...etc}
    //the English character a is the first character of the alphabet
    //so the first character of this key which is 'd' is mapped to a
    //the 2nd character of this key which is 'g' is mapped to b
    //so we treat normal alphabet characters of the text as indecies so
    //if u find a its zero if b its 1 if c its 2 and so on this is done
    //using the hashing down below
    if(str[counter]>='a'&&str[counter]<='z'){
    int mapping_index = str[counter] - 'a' ;
    //now mapping index contains the index of corresponding character in the key
    //replace the character with its key
    str[counter] = key[mapping_index] ;
}
    counter++;
}
}
void decrypt(char*str,char *key){
//crack the key
    char crack_key[26] ;
    for(int i = 0;i<26;i++){
        //mapping the key to its original character
        //for example if key is 'm' ,'n', 'g' ,'o' ,'p','s'....etc
                            //  'a' is mapped to 'm' then
        //again using characters as indices
        //if we find an 'm' in text then it will be mapped to 'a'
        crack_key[key[i]-'a'] = 'a'+i;
    }
    int counter = 0;
    while(str[counter]!='\0'){
        if(str[counter]>='a'&&str[counter]<='z'){
            int mapping_index = str[counter] - 'a' ;
            str[counter] = crack_key[mapping_index];
        }
            counter++;
    }
}

int main(){
//main for testing different inputs
char str[1000] ;
for(int i =  0 ; i<1000;i++){
    str[i] = '\0' ;
}
cout<<"enter text :" ;
cin.get(str,1000);

cout<<endl;
char *key = get_key() ;
cout<<"\nGenerated key : "<<key ;
cout<<"\nBefore encryption : "<<str ;
encrypt(str,key) ;
cout<<"\nAfter encryption : "<<str;
decrypt(str,key);
cout<<"\nAfter decryption : "<<str;

delete key; key = NULL ;
cout<<'\n';
system("pause") ;
    return 0;
}
