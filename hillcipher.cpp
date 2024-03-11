#include <iostream>
#include <random>
#include <time.h>
#include <string.h>
using namespace std ;


// Function to calculate the modular multiplicative inverse(ai)
int modInverse(int num, int mod_sys) {
    num%=mod_sys;
    for (int i = 1; i < mod_sys; i++) {
        if ((i* num) % mod_sys == 1) {
            return i;
        }
    }
    return -1;  // Return -1 if the modular inverse does not exist
}

int fix_num(int unfixed){
    unfixed%=26 ;
        if(unfixed<0){
           unfixed+=26 ;
        }
        return unfixed ;
}

class matrix{
public:

int rows ,cols ;
int **mat ;

matrix(){
    mat= NULL ;
    rows= 0 ; cols = 0;
}

matrix(int r , int c  ){
        rows = r ;
        cols = c ;
        //allocate memory for 2d matrix
        //allocate array of pointers
        mat = new int*[rows] ;
        //for each pointer in the array allocate an array[cols]
        for(int i = 0 ; i <rows;i++){
            mat[i] = new int[cols] ;
        }
        //initialize allocated matrix with zeroes
            for(int i = 0 ; i<rows;i++){
                for(int j = 0  ; j<cols ; j++){
                    mat[i][j] = 0;
                }
            }

}

~matrix(){
    //first delete each entry of the 2d array (matrix)
    for(int i = 0 ; i <rows;i++){
       delete []mat[i] ;
    }
    //then delete the array of pointers
    delete mat ;
 }


//this function initializes the matrix with  sequence of 9 numbers
//this note that the returned matrix has specifications for hillcipher
//det(matrix)!=13 and det(mat)!=0 and det(mat) is odd
void get_key(void);
//checks if current matrix is identity matrix
bool identity(void);
//multiply 2 matrices and put the result in the caller
void mat_mult(matrix&,matrix&);
//returns determanint of the matrix
int det(void) ;

void inverse(matrix &) ;
bool is_identity(void) ;
void fix_mat(void) ;

void scale(int val){
    for(int i =0 ; i<rows  ;i++  ){
        for(int j = 0 ; j<cols ;j++){
            mat[i][j]*=val ;
        }
    }
}

void operator = (matrix&src_mat);
//displays elements of the matrix
void show(void) ;
};
void matrix::get_key(void) {
    int det_val = 0;
    srand(time(0));
    matrix product(3,3) ;

    // Keep generating random keys until their determinant is coprime with 26
   do{
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Get a random number from 1 to 25
                mat[i][j] = rand() % 25 + 1;
            }
        }
        // Get determinant of generated key
    det_val = det();
    matrix inv(3, 3);
    inv.inverse(*this);
    product.mat_mult(*this,inv);
    product.fix_mat();
    }while (!(product.is_identity()&&(det_val != 0) && (det_val % 2 != 0) && (det_val != 13))) ;
}

int matrix ::det(void){
if(rows==cols){
matrix mat_cpy(rows,cols) ;
mat_cpy=*this;
int det = 1 ;
for(int up_r = 0;up_r<rows-1; up_r++){
    for(int low_r = up_r+1; low_r<rows; low_r++){
        //check first if upper element is not zero
        if(mat_cpy.mat[up_r][up_r]==0){
            //switch the rows
            det*=-1 ;
            for(int i = 0 ;  i<cols;i++){
                int temp = mat_cpy.mat[up_r][i]  ;
                mat_cpy.mat[up_r][i] = mat_cpy.mat[low_r][i] ;
                mat_cpy.mat[low_r][i]= temp;
            }
        }
        else{
            int c = -1*(mat_cpy.mat[low_r][up_r]*modInverse(mat_cpy.mat[up_r][up_r],26));
            for(int i =0 ; i<cols;i++){
                mat_cpy.mat[low_r][i]+=c*mat_cpy.mat[up_r][i] ;
            }
        }
    }
}
for(int i =0 ; i <rows; i++){
    det*=mat_cpy.mat[i][i]  ;
}
return fix_num(det) ;
}
return -1 ;
}

void matrix ::mat_mult(matrix &mat1,matrix &mat2){
if(mat1.cols==mat2.rows){
    for(int row_c =0 ; row_c <mat1.rows;row_c++){
        for(int col_c= 0 ; col_c<mat2.cols ; col_c++){
            mat[row_c][col_c] = 0;
            for(int ele_c = 0 ; ele_c <3 ;ele_c++){
                mat[row_c][col_c]+=(mat1.mat[row_c][ele_c]*
                        mat2.mat[ele_c][col_c]);
            }
            mat[row_c][col_c] = fix_num(mat[row_c][col_c]) ;
        }
    }
}
}


bool matrix:: is_identity(void){
  for(int i = 0 ; i<rows;i++){
        for(int j= 0 ; j<cols; j++){
            if(i==j){
                if(mat[i][j]!=1) {
                    return false ;
                }
            }
            else{
                if(mat[i][j]!=0){
                    return false ;
                }
            }

}
}
return true ;
}
void matrix::show(void){

    for(int i = 0 ; i <rows ; i++){
        for(int j=  0 ;  j<cols ; j++){
            cout<<mat[i][j]<<" " ;
        }
        cout<<endl ;
    }
}


void matrix ::operator=(matrix&src_mat){
    for(int  i = 0 ; i <rows;i++){
        for(int j = 0 ; j<cols;j++){
            mat[i][j] = src_mat.mat[i][j];
        }
    }
}

void matrix::inverse(matrix & mat1){
matrix mat_cpy(5,5) ;
for(int i  = 0 ; i <mat1.rows;i++){
    for(int j= 0 ; j<mat1.cols ;j++){
        mat_cpy.mat[i][j] = mat1.mat[i][j] ;
        if(j<mat1.cols-1){
        //repeat first 2 cols in the big matrix
            mat_cpy.mat[i][3+j] = mat1.mat[i][j] ;
        }
    }
}
//repeat 1st 2 rows in the big matrix
for(int i  = 0 ; i <mat1.rows-1;i++){
    for(int j= 0 ; j<5 ;j++){
        mat_cpy.mat[i+3][j] =mat_cpy.mat[i][j] ;
}
}
int det_val = mat1.det() ;
det_val = modInverse(det_val,26) ;
for(int i =1 ; i <4;i++){
    for(int j= 1 ; j<4 ;j++){
        mat[i-1][j-1] =mat_cpy.mat[j][i]*mat_cpy.mat[j+1][i+1]
                      -mat_cpy.mat[j+1][i] *mat_cpy.mat[j][i+1]  ;
             mat[i-1][j-1]*=det_val ;
             mat[i-1][j-1] = fix_num( mat[i-1][j-1]) ;
    }
}

}

void encrypt(matrix &key, string &text) {
    int counter = 0;
    matrix text_mat(3, 1);
    matrix cipher_mat(3, 1);
    while (counter <text.length()) {
        for (int i = 0; i < 3; i++) {
            if (text[counter + i] != '\0') {
                text_mat.mat[i][0] = text[counter + i] - 'a';
            }
            else {
                text_mat.mat[i][0] = 0;
            }
        }
        cipher_mat.mat_mult(key, text_mat);
        for (int i = 0; i < 3; i++) {
            if (text[counter + i] != '\0') {
                text[counter + i] = 'a' + cipher_mat.mat[i][0];
            }
        }
        counter += 3;
    }
}

void decrypt(matrix& key, string & text) {
    matrix inv_key(3, 3);
    matrix mul(3,3) ;
    inv_key.inverse(key);
    inv_key.fix_mat();
    encrypt(inv_key , text) ;
}

void matrix ::fix_mat(void) {
    for(int i= 0 ; i <rows  ; i++){
        for(int j =0 ; j<cols; j++){
            mat[i][j] =fix_num(mat[i][j]);
        }
    }
}

int main(){
matrix key(3,3) ;
key.get_key() ;

string text = "abcdefghijklmnopqrstp" ;
encrypt(key,text) ;
cout<<'\n'<<text<<'\n';
decrypt(key,text) ;
cout<<text<<endl  ;

    return  0;
}


