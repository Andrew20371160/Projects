#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED
#include <iostream>
#include <math.h>
#include <string.h>
using namespace std ;
//feel free to edit this value the way you want
const float tolerance = 0.0000001 ;
const float M_PI= 3.14159;
string shape_error ="\nmatrices aren't the same shape default garbage value is -1\n";
string square_error= "\nmatrix must be square to perform this operation default garbage value is -1\n";
string uninit_error = "\nmatrix isn't initialized yet\n";
//write efficient matrix multiplication algos aka diagonal ,upper_tri ,lower_tri  ,
//add some variables to matrices to indicate its properties
//write a function to test or use is_diag ,is_suare etc etc use them in one big function called
//extract specifications of matrix for ex and this writes it into the matrix class so that
//we won't have to do that again
class matrix{
private :
float  **vec ;
int rows , cols;

float**get_vec(int r ,int c){
    if(r>0&&c>0){
        float**ret_vec =new float*[r];
        for(int i= 0  ; i <r ;i++){
            ret_vec[i] = new float[c] ;
        }
        return ret_vec ;
    }
    return NULL ;
}
public:
    //empty matrix
    matrix();//tested
    //by default initializes the matrix with zeroes
    matrix(int,int,float);//tested
    //deallocate the memory allocated by the matrix
    ~matrix();//tested
    //copy constructor
    matrix(const matrix&);//tested 

    //allows for overwritting in matrices and resizing it 
    //reusability of same matrix for expressions like mat = mat*2 
    void operator=(const matrix&) ;//tested
    int get_rows()const;//tested

    int get_cols()const;//tested
    //returns an element at a specified index
    float& at(int r_ind,int c_ind);//tested
    //fills a matrix with a certain value
    bool fill(int r ,int c,float value);//tested
    //sets current matrix as identity
    void identity(void);//tested

    bool same_shape(const matrix&)const ;//tested

    void show(void)const;//tested
    // Add a matrix to this matrix
    matrix operator+(matrix&)const;//tested

    // Subtract a matrix from this matrix
    matrix operator-(matrix&)const;//tested

    float dot(matrix&)const;

    float axpy(float,matrix&)const;

    // Multiply this matrix by another matrix
    matrix operator*(matrix&)const;//tested
    //returns caller/ sent matrix
    matrix operator/(matrix&)const;//tested
    // Multiply this matrix by a scalar
    matrix operator*(float)const;

    // Transpose this matrix
    matrix transpose(void)const;//tested

    // Check if this matrix is square
    bool is_square(void)const;//tested

    // Calculate the determinant of this matrix
    // (only for square matrices)
    float det(void);//tested

    // Calculate the inverse of this matrix
    // (only for square matrices)
    matrix inverse(void);//tested

    // Calculate the trace of this matrix
    // (only for square matrices)
    float trace(void)const;//tested

    // Calculate the rank of this matrix
    int rank(void)const;

    // Check if this matrix is symmetric
    bool is_symmetric(void)const;

    // Check if this matrix is skew-symmetric
    bool is_skew_symmetric(void)const;

    // Check if this matrix is orthogonal
    bool is_orthogonal(void)const;

    float norm2(void) ;

    float length(void) ;

    float theta(matrix&) ;

    bool is_perp(matrix&) ;

    bool is_parallel(matrix&) ;

    bool operator==(matrix&) const;

    // Check if this matrix is idempotent
    bool is_idempotent(void)const;

    // Check if this matrix is nilpotent
    bool is_nilpotent(void)const;

    // Check if this matrix is involutory
    bool is_involutory(void)const;

    // Check if this matrix is diagonal
    bool is_diagonal(void)const;

    // Check if this matrix is scalar
    bool is_scalar(void)const;

    // Check if this matrix is identity
    bool is_identity(void)const;

    // Check if this matrix is upper triangular
    bool is_upper_triangular(void)const;

    // Check if this matrix is lower triangular
    bool is_lower_triangular(void)const;

    matrix solve(void);

    void row_axpy(float,int,int) ;

    matrix utri(void) ;//tested

    matrix ltri(void) ;

    float back_substitution(int,matrix&);
    float forward_substitution(int ,matrix&) ;
    bool switch_rows(int,int);//tested

    void lu_fact(matrix**,matrix**) ;

    string mat_to_string(void) const;//tested

    matrix operator/(matrix& m);//tested

};

#endif // VEC_H_INCLUDED
