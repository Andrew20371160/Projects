#ifndef MATRIX_ALGEBRA_H_INCLUDED
#define MATRIX_ALGEBRA_H_INCLUDED
/*-update : added fix_pivots() this function rearranges the matrix rows
so that the rows contatining the pivotsare on top and the rest of rows at bottom
its crucial when using functions like lu_fact not really since i added permutation matrix earlier
but if you use elementary matrix from null_rows() and tried to test if elementary * matrix euqals
rref(matrix) this sometimes isn't true since elementary matrix doesn't record the switches
in rows that happens during the rref of the matrix its advisable to use after you initialize the matrix
but i wouldn't force that its on you :) .
*/
#include <iostream>
#include <math.h>
#include <string.h>
#include "complex.h"
using namespace std ;

//error messages
string shape_error ="\nmatrices aren't the same shape default garbage value is -1\n";
string square_error= "\nmatrix must be square to perform this operation default garbage value is -1\n";
string uninit_error = "\nmatrix isn't initialized yet\n";
//write efficient matrix multiplication algos aka diagonal ,upper_tri ,lower_tri  ,
//add some variables to matrices to indicate its properties
//write a function to test or use is_diag ,is_suare etc etc use them in one big function called
//extract specifications of matrix for ex and this writes it into the matrix class so that
//we won't have to do that again
enum{upper_left=0,lower_left,lower_right,upper_right};

enum{lower_half=0,upper_half};

template<typename DataType>
class matrix{
private :
//2d array for holding data
DataType *vec ;
//dimensions of matrix
int rows , cols;
//helper function for allocating memory for a 2d array
DataType*get_vec(int r ,int c){
    //check for passed parameters
    if(r>0&&c>0){
        //memory allocation
        DataType*ret_vec =new DataType[r*c];
        return ret_vec ;
    }
    return NULL ;
}
public:
    //empty matrix
    matrix();//tested
    //by default initializes the matrix with zeroes
    matrix(int rows ,int cols ,DataType initialization_value=0);//tested
        //initializes a matrix with specified 1d array data
    matrix(int rows ,int cols ,DataType* initialization_array,int size_of_array) ;

    //deallocate the memory allocated by the matrix
    ~matrix();//tested
    //copy constructor
    matrix(const matrix&);//tested
    //get rows value
    int get_rows()const;//tested
    //get cols value
    int get_cols()const;//tested
    //accessing element at a specified index
    DataType& at(int r_ind,int c_ind);//tested
        //accessing element at a specified index
    DataType& at(int r_ind,int c_ind)const;//tested
    //fills a matrix with a certain value
    void fill(DataType value);//tested
    //sets current matrix as identity
    void identity(void);//tested
    //check for same dimensions for 2 matrices
    bool same_shape(const matrix&)const ;//tested
    //display functionality
    void show(void)const;//tested
    // Add a matrix to the caller matrix and returns it as a new matrix
    matrix operator+(const matrix&)const;//tested
    // subtracts a matrix from the caller matrix and returns it as a new matrix
    matrix operator-(const matrix&)const;//tested
    // Multiply caller matrix by another matrix
    matrix operator*(const matrix&)const;//tested
    //returns caller/ sent matrix uses @inverse
    matrix operator/(const matrix&)const;//tested
    // Multiply this matrix by a scalar
    matrix operator*(DataType)const;//tested
    //turns a matrix into a string for printing
    string mat_to_string(void) const;//tested
    //performs dot product of 2 matrices and returns the value
    DataType dot(const matrix&)const;//tested
    //performs alpha*x+y and returns the value
    DataType axpy(DataType,const matrix&)const;//tested
    // Transpose caller matrix and returns it as a new matrix
    matrix transpose(void)const;//tested

    // Check if this matrix is square
    bool is_square(void)const;//tested
    // Calculate the determinant of this matrix
    // (only for square matrices)
    DataType det(void)const ;//tested
    // Calculate the inverse of this matrix and returns it as a new matrix
    // (only for square matrices)
    matrix inverse(void)const ;//tested

    // Calculate the trace of this matrix
    // (only for square matrices)
    DataType trace(void)const;//tested

    // Calculate the rank of this matrix
    int rank(void)const ;//tested

    // Check if this matrix is symmetric
    bool is_symmetric(void)const ;//tested

    // Check if this matrix is skew-symmetric
    bool is_skew_symmetric(void)const ;//tested

    // Check if this matrix is orthogonal
    bool is_orthogonal(void)const ;//tested
    //returns length of the caller
    DataType norm2(void) const ;//tested
    //same as previous but different wrapper
    DataType length(void) const ;//tested
    //theta between caller and passed matrix
    DataType theta(matrix&) const ;//tested
    //solves appended matrix using @gauss_down and then @back_sub
    matrix solve(void)const ;//tested
    //performs axpy operation between 2 rows
    void row_axpy(DataType alpha,int x_row,int y_row) ;

    //performs gaussian elimination downward
    //added an optional input if you want to see where are the pivots
    //for each row just pass and address of the matrix and if you don't want
    //just leave it empty i use this functionality in other pieces of code
    //if you want to store new pivots locations in the matrix
    //pass new_locations else old locations by default it returns new locations
    enum {old_locations =0,new_locations=1};
    matrix gauss_down(matrix<int>*pivots_indices=NULL,int pivots_locations = new_locations)const ;//tested
    //performs gaussian elimination upward
    matrix gauss_up(matrix<int>*)const  ;//tested
    //performs back substitution on a selected row and solution matrix is passed with it
    DataType back_sub(int selected_row,const matrix& solution_matrix)const ;//tested
    //performs forward substitution on a selected row and solution matrix is passed with it
    DataType fwd_sub(int selected_row,const matrix& solution_matrix)const ;//tested
    //yeah name is opvious
    bool switch_rows(int row1,int row2);//tested
    //performs lu factorization on a matrix
    //lower_fact and upper_fact have the results
    //now added permutation matrix since during the during the
    //elemination some rows could be switched so the permutation
    //matrix records that change its a simple identity with rows
    //switching as upper_fact rows switched
    void lu_fact(matrix& lower_fact,matrix&permutation,matrix& upper_fact)const ;//tested
    //assignment function
    //allows for matrix reuse
    void operator=(const matrix&) ;//tested
    //append 2 matrices by cols aka return matrix =[mat1 mat2]
    matrix append_cols(const matrix&src)const ;
    //append 2 matrices by rows aka return matrix =[mat1]
    //                                             [mat2]
    matrix append_rows(const matrix&src)const ;
    //checks if caller is perpindicular on the passed matrix
    bool is_orthogonal(const matrix&)const  ;//tested
    //checks if caller is in parallel with the passed matrix
    bool is_parallel(const matrix&)const  ;//tested
    //checks if 2 matrices are equal
    bool operator==(const matrix&) const;//tested
    // Check if this matrix is identity
    bool is_identity(void)const ;//tested
    // Check if this matrix is the zero matrix
    bool is_zero(void)const ;

    // Check if this matrix is upper triangular
    bool is_upper_tri(void)const ;//tested

    // Check if this matrix is lower triangular
    bool is_lower_tri(void)const ;//tested
    // Check if this matrix is idempotent
    bool is_idempotent(void)const ;//tested

    // Check if this matrix is nilpotent
    bool is_nilpotent(void)const ;//tested

    // Check if this matrix is involutory
    bool is_involutory(void)const ;//tested

    // Check if this matrix is diagonal
    bool is_diagonal(void)const ;//tested

    // Check if this matrix is scalar
    bool is_scalar(void)const ;//tested

    //this function checks if a current element is a pivot
    //it now returns pivot's row since its used in functions like lu_fact
    int is_pivot(int row_index , int col_index) ;//tested
    //same as is_pivot but used in gauss_up
    int is_pivot_up(int,int) ;

    //this function returns row reduced echolon form of a matrix
    //it mapps for each row the index of its pivot if found
    // if at that row there are no pivots its assigned the value -1
    matrix rref(matrix<int> * pivots_indices =NULL)const ;//tested
    // Checks if the set of vectors (columns of the matrix) is linearly independent.
    bool is_independent(void)const ;//tested
    // Calculates the dimension of the null space (kernel) of the matrix.
    // The null space consists of all vectors that are mapped to the zero vector by the linear transformation represented by the matrix.
    int dim_null_cols(void)const ;//tested
    int dim_null_rows(void)const ;//tested
    // Calculates the dimension of the column space (range) of the matrix.
    // The column space consists of all possible linear combinations of the column vectors in the matrix.
    int dim(void)const ;//tested
    // Checks if the set of vectors (columns of the matrix) forms a basis for the vector space of the given dimension.
    // A set of vectors forms a basis if they are linearly independent and span the vector space.
    bool is_basis(int dimension)const ;//tested
    // Returns a set of vectors (as a matrix) that forms a basis column space
    matrix basis_cols(void)const ;//tested
    // Returns a set of vectors (as a matrix) that forms a basis for the row space
    matrix basis_rows(void)const ;//tested
    //returns Null space of row space
    matrix null_rows(matrix*)const  ;
    //returns null space of column space
    matrix null_cols(void)const  ;//tested
    //it fixes a matrix by putting rows that corresponds to pivots first
    //then rist of rows at th every end this fixes an issue at rref
    //where if a row switch occurs it won't be recorded in elementary matrix
    //or you will need extra permutation matrix fixes the caller itself
    void fix_pivots(void) ;
    //returns projection matrix of a linear system
    /*
    Ax=b has no solution
    AT*A x* =AT*b
    x* = (AT*A )^-1 *AT b
    p = Ax* so P = A*(AT*A)^-1 * AT *b
    so projection matrix where p =projection b
    projection = A*(AT*A)^-1 *AT
    */
    matrix projection(void)const ;

    matrix fit_least_squares(const matrix&data_set)const  ;

    matrix extract_col(int index)const ;

    matrix gram_shmidt(void)const ;
    //returns cofactor of an element at position row_i,col_i
    DataType cofactor(int row_i, int col_i)const  ;
    //returns matrix of cofactors of all elements of the matrix
    matrix cofactors(void)const  ;

    matrix SubLambdaI(DataType lambda)const ;
    matrix eigen_vectors(const matrix&eigen_values)const ;

    matrix arrange(const matrix<int>&seq)const;

    void at_quarter(int,const matrix&) ;

    //performs fast fourier transform on one column
    //dimension is just the number of rows or size of column
    matrix fft_col(int dimension)const ;

    //performs fast fourier transform on the whole matrix
    matrix fft(void)const;

    matrix split(int half )const;
};
    //when calling do this
    //identity<DataType>
    template <typename DataType>
    matrix<DataType> identity(int);


#endif // VEC_H_INCLUDED
