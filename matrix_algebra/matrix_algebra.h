#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED
#include <iostream>
#include <math.h>
#include <string.h>
using namespace std ;
//this enum is used as output for functions using @is_pivot
//its usefull when using the @det function since if you exchange a row
//the det is muliplied by -1 and so on
//feel free to edit this value the way you want
const float tolerance = 0.000001 ;
const float M_PI= 3.14159;
//error messages
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
//2d array for holding data
float  **vec ;
//dimensions of matrix
int rows , cols;
//helper function for allocating memory for a 2d array
float**get_vec(int r ,int c){
    //check for passed parameters
    if(r>0&&c>0){
        //memory allocation
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
    matrix(int rows ,int cols ,float initialization_value);//tested
        //initializes a matrix with specified 1d array data
    matrix(int rows ,int cols ,float* initialization_array,int size_of_array) ;

    //deallocate the memory allocated by the matrix
    ~matrix();//tested
    //copy constructor 
    matrix(const matrix&);//tested
    //get rows value
    int get_rows()const;//tested
    //get cols value
    int get_cols()const;//tested
    //accessing element at a specified index
    float& at(int r_ind,int c_ind);//tested
    //fills a matrix with a certain value
    bool fill(int r ,int c,float value);//tested
    //sets current matrix as identity
    void identity(void);//tested
    //check for same dimensions for 2 matrices
    bool same_shape(const matrix&)const ;//tested
    //display functionality 
    void show(void)const;//tested
    // Add a matrix to the caller matrix and returns it as a new matrix
    matrix operator+(matrix&)const;//tested
    // subtracts a matrix from the caller matrix and returns it as a new matrix
    matrix operator-(matrix&)const;//tested
    // Multiply caller matrix by another matrix
    matrix operator*(matrix&)const;//tested
    //returns caller/ sent matrix uses @inverse
    matrix operator/(matrix&)const;//tested
    // Multiply this matrix by a scalar
    matrix operator*(float)const;//tested
    //turns a matrix into a string for printing
    string mat_to_string(void) const;//tested
    //performs dot product of 2 matrices and returns the value
    float dot(matrix&)const;//tested
    //performs alpha*x+y and returns the value 
    float axpy(float,matrix&)const;//tested
    // Transpose caller matrix and returns it as a new matrix
    matrix transpose(void)const;//tested
    // Check if this matrix is square
    bool is_square(void)const;//tested
    // Calculate the determinant of this matrix
    // (only for square matrices)
    float det(void);//tested
    // Calculate the inverse of this matrix and returns it as a new matrix
    // (only for square matrices)
    matrix inverse(void);//tested

    // Calculate the trace of this matrix
    // (only for square matrices)
    float trace(void)const;//tested

    // Calculate the rank of this matrix
    int rank(void);//tested

    // Check if this matrix is symmetric
    bool is_symmetric(void);//tested

    // Check if this matrix is skew-symmetric
    bool is_skew_symmetric(void);//tested

    // Check if this matrix is orthogonal
    bool is_orthogonal(void);//tested
    //returns length of the caller
    float norm2(void) ;//tested
    //same as previous but different wrapper
    float length(void) ;//tested
    //theta between caller and passed matrix
    float theta(matrix&) ;//tested
    //solves appended matrix using @gauss_down and then @back_sub
    matrix solve(void);//tested
    //performs axpy operation between 2 rows
    void row_axpy(float alpha,int x_row,int y_row) ;

    //performs gaussian elimination downward
    //added an optional input if you want to see where are the pivots
    //for each row just pass and address of the matrix and if you don't want
    //just leave it empty i use this functionality in other pieces of code
    matrix gauss_down(matrix *) ;//tested
    //performs gaussian elimination upward
    matrix gauss_up(matrix *) ;//tested
    //performs back substitution on a selected row and solution matrix is passed with it
    float back_sub(int selected_row,matrix& solution_matrix);//tested
    //performs forward substitution on a selected row and solution matrix is passed with it
    float fwd_sub(int selected_row,matrix& solution_matrix) ;//tested
    //yeah name is opvious
    bool switch_rows(int row1,int row2);//tested
    //performs lu factorization on a matrix
    //lower_fact and upper_fact have the results
    void lu_fact(matrix& lower_fact,matrix&permutation,matrix& upper_fact) ;//tested
    //assignment function
    //allows for matrix reuse
    void operator=(const matrix&) ;//tested
        //checks if caller is perpindicular on the passed matrix
    bool is_perp(matrix&) ;//tested
    //checks if caller is in parallel with the passed matrix
    bool is_parallel(matrix&) ;//tested
    //checks if 2 matrices are equal
    bool operator==(matrix&) const;//tested
    // Check if this matrix is idempotent
    bool is_idempotent(void);//tested

    // Check if this matrix is nilpotent
    bool is_nilpotent(void);//tested

    // Check if this matrix is involutory
    bool is_involutory(void);//tested

    // Check if this matrix is diagonal
    bool is_diagonal(void);//tested

    // Check if this matrix is scalar
    bool is_scalar(void);//tested

    // Check if this matrix is identity
    bool is_identity(void);//tested

    // Check if this matrix is upper triangular
    bool is_upper_tri(void);//tested

    // Check if this matrix is lower triangular
    bool is_lower_tri(void);//tested
    //this function checks if a current element is a pivot
    //also it switches rows if the pivot is not at same row
    //and returns true
    int is_pivot(int row_index , int col_index);//tested
    //same as is_pivot but used in gauss_up
    int is_pivot_up(int,int) ;

    //this function returns row reduced echolon form of a matrix
    //it mapps for each row the index of its pivot if found
    // if at that row there are no pivots its assigned the value -1
    matrix rref(matrix & pivots_indices);//tested
    // Checks if the set of vectors (columns of the matrix) is linearly independent.
    bool is_independent(void);//tested
    // Calculates the dimension of the null space (kernel) of the matrix.
    // The null space consists of all vectors that are mapped to the zero vector by the linear transformation represented by the matrix.
    int dim_null_cols(void);//tested
    int dim_null_rows(void);//tested
    // Calculates the dimension of the column space (range) of the matrix.
    // The column space consists of all possible linear combinations of the column vectors in the matrix.
    int dim(void);//tested
    // Checks if the set of vectors (columns of the matrix) forms a basis for the vector space of the given dimension.
    // A set of vectors forms a basis if they are linearly independent and span the vector space.
    bool is_basis(int dimension);//tested
    // Returns a set of vectors (as a matrix) that forms a basis for the vector space of the given dimension.
    matrix basis_cols(void);//tested
    // Returns a set of vectors (as a matrix) that forms a basis for the vector space of the given dimension.
    matrix basis_rows(void);//tested
    matrix null_rows(matrix*) ;
    matrix null_cols(void) ;


};

#endif // VEC_H_INCLUDED
