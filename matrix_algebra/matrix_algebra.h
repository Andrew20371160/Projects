#ifndef MATRIX_ALGEBRA_H_INCLUDED
#define MATRIX_ALGEBRA_H_INCLUDED
//tolerance is used in calculations like inverse and gram-shmidt ,gauss
//this is sufficient for gram-shmidt since it requires a percision
//const long double tolerance =1e-18;
//check_tolerance is for is_identity , is_zero , aka every function starting with is_
//modify this the way you want
//const long double check_tolerance =1e-6;
#include "complex.h"
#include <iostream>
#include <math.h>
#include <string.h>
#include <random>
#include <time.h>

//feel free to change no_init its just to indicate that the matrix doesn't need to be
//initialized with values
using namespace std ;
#define no_init INT_MIN


//error messages
string shape_error ="\nmatrices aren't the same shape default garbage value is -1\n";
string square_error= "\nmatrix must be square to perform this operation default garbage value is -1\n";
string uninit_error = "\nmatrix isn't initialized yet\n";


//enum used in at_quarter which puts an input matrix
//in a wanted quarter of the matrix if applicable
enum{upper_left=0,lower_left,lower_right,upper_right};
//enum for split which splits the matrix int o 2 halves and returns
//the half you want (used in FFT)
enum{lower_half=0,upper_half};
//used in gauss_down to specify if you want the locations of the pivots
//either the new ones or the old ones
enum {old_locations =0,new_locations=1};
//types of matrices
//used in compression and accessors
enum{general=0,utri,ltri,diagonal,symmetric,anti_symmetric,constant,iden,orthonormal};
enum{general_compress,utri_compress,ltri_compress,diagonal_compress,symmetric_compress,
anti_symmetric_compress,constant_compress,iden_compress,orthonormal_compress};

//helper function for creating a vector (allocating memory)
template<typename DataType>
DataType*get_vec(int  r ,int  c);

//helper function for filling a vector with data
template<typename DataType>
void fill_vec(DataType*vec,int  size, DataType val = -1) ;

//helper function for copying
template<typename DataType>
void copy_vec(DataType*&dest,const DataType*&src,int  size) ;


template<typename DataType>
class matrix{

private :
    //dimensions of matrix
    int  rows , cols;

    DataType *vec ;//storage

    int  *row_start,*pindex;//for mapping utri &ltri
    /*
    row_start mapps the start of each row into @vec since utri ,ltri are stored without zeroes
    pindex is for pivots locations
*/

    //make sure not to compress a compressed matrix (usage of the  bool)
    bool is_compressed;
    //type of compression of the matrix
    int compression_type ;
    //actual size allocated for the matrix
    int  actual_size ;

    //dummy array of one element
    //for utri it returns 0
    //allows for compression of anti-symmetric since the lower part is -ve of the upper part
    //for mutable the idea is store in empty_vec the value at upper part multiplied by -1
    //and return the value so it can be both used in constant and non constant matrices
    mutable DataType empty_vec[1];

    mutable int  matrix_type ;//general or orthonormal or utri or etc etc?
    //fills matrix_type and sets at_ptr ,at_ptr_c
    void set_feature(int  matrix_t);

    //sets at_ptr &&at_ptr_C according to matrix_type
    void set_at_ptr(int  matrix_type);
    //at_ptr & at_ptr_c are member function pointers that store the address of at
    //there are 8 at functions one for utri,ltri,symmetric,anti-symmetric etc etc
    //each access the data according to matrix type so at_ptr is put inside the
    //original at that's accessible to the user and inside it it calls the specific accessor
    //according to matrix type using the pointer
    DataType&(matrix::*at_ptr)(int  , int  );
    //accessing for constatnt matrices
    const DataType&(matrix::*at_ptr_c)(int  , int  ) const;

    //according to matrix type using the pointer
    int(matrix::*start_ptr)(int)const;

    //accessing for constatnt matrices
    int(matrix::*end_ptr)(int)const;


    /*
    compression functions for each matrix type

    */
    //compress upper-triangular matrices
    //pass a matrix with its pindex filled its easier to use compress
    //it does that for you w8 its private (well its open source do what you want :)
    //the pindex must be filled with pivots same for compress_ltri
    /*
    if a function returns a matrix with special features (i think i covered all of them)
    like gauss_down ,gauss_up ,get_pivots,gram_shmidt
    the matrix is compressed or matrix type if the matrix isn't compressable like the one from
    gram shmidt but its efficient when calculating the inverse for example
    since if its orthonormal then the transpose is returned instead of performing
    gauss-jordan
    matrices performing operations on compressed matrices (for example if you multiply a compressed matric by a non-compressed one)
    no problems occur it's been a rough week of testing and adjusting and now its stable
    */
    void compress_utri(const matrix<int>&compression_vec) ;
    void compress_ltri(const matrix<int>&compression_vec) ;
    //compress symmetric matrices no need for pindex
    void compress_symmetric(void) ;
    void compress_anti_symmetric(void) ;
    //compress diagonal,constant,identity matrices no need to fill pindex of the matrix
    void compress_diagonal(void) ;
    void compress_identity(void) ;
    void compress_const(void) ;


    /*
    at functions for each matrix type
    compressed matrices like utri,ltri,symmetric,anti-symmetric are stored in row major order
    refere to at definitions to see the mapping if you are interested
    for diagonal we just store the main diagonal
    for constatnt we just store one element
    for identity we just store a 1
    */
    //declarations of at for each matrix type
    //for general matrices
    DataType&at_general(int  ,int  )  ;
    //for upper triangular matrices
    DataType&at_utri(int  ,int  )  ;
    //for lower triangular matrices
    DataType&at_ltri(int  ,int  )  ;
    //for diagonal matrices
    DataType&at_diagonal(int  ,int  )  ;
    //for identity matrices
    DataType&at_identity(int  ,int  )  ;
    //for matrices containing one element including zeroes
    DataType&at_const(int  ,int  )  ;
    //for symmetric matrices
    DataType&at_symmetric(int  ,int  )  ;
    //for anti symmetric matrices
    //still working on them
    DataType&at_anti_symmetric(int  ,int  )  ;
    //declarations of at for each matrix type for matrices that are constant
    //and just used in calculations
    const DataType&at_general_c(int  ,int  )const  ;
    const DataType&at_utri_c(int  ,int  )const ;
    const DataType&at_ltri_c(int  ,int  )const  ;
    const DataType&at_diagonal_c(int  ,int  )const  ;
    const DataType&at_identity_c(int  ,int  )const  ;
    const DataType&at_const_c(int  ,int  )const ;
    const DataType&at_symmetric_c(int  ,int  )const  ;
    const DataType&at_anti_symmetric_c(int  ,int  )const  ;



    int start_general(int row_i )const;
    int end_general(int row_i )const;
    int start_constant(int row_i )const;
    int end_constant(int row_i )const;
    int start_utri(int row_i)const ;
    int end_utri(int row_i) const;
    int start_ltri(int row_i)const ;
    int end_ltri(int row_i)const ;
    int start_diagonal(int row_i)const;
    int end_diagonal(int row_i)const ;
    int start_identity(int row_i) const;
    int end_identity(int row_i)const ;
    int start_symmetric(int row_i)const ;
    int end_symmetric(int row_i)const;
    int start_anti_symmetric(int row_i) const;
    int end_anti_symmetric(int row_i)const ;
    void set_start_end_ptr(int  matrix_t);


public:
    //empty matrix
    matrix();//tested
    //by default doesn't initialize the matrix with data
    //by default its not compressed if you want just add 1 after the data
    //matrix(5,5,data,1)
    matrix(int  rows ,int  cols ,DataType initialization_value=no_init,bool compressed= false);//tested
    //initializes a matrix with specified 1d array data by default matrix type is general
    matrix(int  rows ,int  cols ,DataType* initialization_array,int  size_of_array) ;
    //deallocate the memory allocated by the matrix
    ~matrix();//tested
    //copy constructor
    matrix(const matrix&);
    //getters
    int  get_rows()const;
    int  get_cols()const;
    //returns number of elements stored in the matrix
    int  get_size()const;
    //returns type of the matrix refer to the enum to know its type
    int  get_type()const;
    //accessors
    //accessing element at a specified index
    DataType& at(int  r_ind,int   c_ind);//tested
    const DataType& at(int   r_ind,int   c_ind)const;//tested

    //fills a matrix with a certain value
    void fill(DataType value);//tested
    //sets current matrix as identity
    void set_identity(void);//tested
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
    //turns a matrix int o a string for print ing
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
    int  rank(void)const ;//tested
    /*
    for each is_feature function it stores the features in matrix_type if it does exist
    */
    // Check if this matrix is symmetric
    bool is_symmetric(void)const ;//tested

    // Check if this matrix is skew-symmetric
    bool is_anti_symmetric(void)const ;//tested

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
    void row_axpy(DataType alpha,int  x_row,int  y_row) ;

    //performs gaussian elimination downward
    //added an optional input if you want to see where are the pivots
    //for each row just pass and address of the matrix and if you don't want
    //just leave it empty i use this functionality in other pieces of code
    //if you want to store new pivots locations in the matrix
    //pass new_locations else old locations by default it returns new locations
    matrix gauss_down(matrix<int >*pivots_indices=NULL,int  pivots_locations = new_locations)const ;//tested
    //performs gaussian elimination upward
    matrix gauss_up(matrix<int >*pivots_incices=NULL)const  ;//tested
    //performs back substitution on a selected row and solution matrix is passed with it
    DataType back_sub(int  selected_row,const matrix& solution_matrix)const ;//tested
    //performs forward substitution on a selected row and solution matrix is passed with it
    DataType fwd_sub(int  selected_row,const matrix& solution_matrix)const ;//tested
    //yeah name is opvious
    bool switch_rows(int  row1,int  row2);//tested
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
     int is_pivot(int  row_index , int  col_index) ;//tested
    //same as is_pivot but used in gauss_up
     int is_pivot_up(int  ,int  ) ;

    //this function returns row reduced echolon form of a matrix
    //it mapps for each row the index of its pivot if found
    // if at that row there are no pivots its assigned the value -1
    matrix rref(matrix<int  > * pivots_indices =NULL)const ;//tested
    // Checks if the set of vectors (columns of the matrix) is linearly independent.
    bool is_independent(void)const ;//tested
    // Calculates the dimension of the null space (kernel) of the matrix.
    // The null space consists of all vectors that are mapped to the zero vector by the linear transformation represented by the matrix.
    int  dim_null_cols(void)const ;//tested
    int  dim_null_rows(void)const ;//tested
    // Calculates the dimension of the column space (range) of the matrix.
    // The column space consists of all possible linear combinations of the column vectors in the matrix.
    int  dim(void)const ;//tested
    // Checks if the set of vectors (columns of the matrix) forms a basis for the vector space of the given dimension.
    // A set of vectors forms a basis if they are linearly independent and span the vector space.
    bool is_basis(int  dimension)const ;//tested
    // Returns a set of vectors (as a matrix) that forms a basis column space
    matrix basis_cols(void)const ;//tested
    // Returns a set of vectors (as a matrix) that forms a basis for the row space
    matrix basis_rows(void)const ;//tested
    //returns Null space of row space
    matrix null_rows(matrix*elementary=NULL)const  ;
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
    //performs least squares fit
    //fits an output to a linear system
    matrix fit_least_squares(const matrix&output)const  ;
    //extracts a column at a specified index
    //and returns it as column matrix
    matrix extract_col(int  index)const ;
    //performs gram_shmidt algorithm and returns resultant
    //orthonormal vectors as a matrix
    matrix gram_shmidt(void)const ;
    //returns cofactor of an element at position row_i,col_i
    DataType cofactor(int  row_i, int  col_i)const  ;
    //returns matrix of cofactors of all elements of the matrix
    matrix cofactors(void)const  ;
    //performs A-l*identity and returns the matrix
    matrix SubLambdaI(DataType lambda)const ;
    //returns eigen vectors of a matrix
    //pass in eigen values as a column matrix
    matrix eigen_vectors(const matrix&eigen_values)const ;
    //arranges rows of a matrix in a wanted sequence
    //permutation matrix without extra usage of memory
    matrix arrange(const matrix<int >&seq)const;
    //puts input matrix in a quarter
    //upper_left,lower_right,upper_right,lower_right
    //input matrix rows & cols must be less than or equal to caller's size by
    //factor of 2
    void at_quarter(int  ,const matrix&) ;

    //performs fast fourier transform on one column
    //dimension is just the number of rows or size of column
    matrix fft_col(int  dimension)const ;

    //performs fast fourier transform on the whole matrix
    matrix fft(void)const;
    //splits the matrix int o 2 halves upper or lower and returns
    //the wanted size
    matrix split(int  half )const;

    //resize the matrix int o wanted dimensions
    //and pad rest of it with certain padding value
    //by default the dimensions are same as caller
    //and padding value by default is zero
    matrix resize(int  wanted_rows = get_rows(),int  wanted_cols=get_cols(),DataType padding_value=0)const ;
    //returns pivots of a matrix in column matrix
     matrix get_pivots(matrix<int >*pivots_locations=NULL)const;
    //checks if a matrix is positive definite
    bool is_positive_definite(void)const;
    //performs QR factorization on a matrix and puts them in q ,r passed in the function input
     void qr_fact( matrix&q, matrix&r)const;
    //returns eigen values of a matrix in a column matrix
    //computations made by qr factorization
    //doesn't generate correct results all the time due to divergence issues
     matrix eigen_values(const int &max_iteration,const double&min_diff = check_tolerance)const;
    //filters the matrix elements from data less than a specified tolerance
    //by default filters by check_tolerance
    void filter(double filter_tolerance=check_tolerance);
    //matrix to the power of k A^k
    matrix operator^(const DataType& power)const ;
    //A = U S VT
    void svd(matrix&u, matrix&s, matrix&vt)const;
    //calculates the length of a column at a specified index
    DataType col_length(const int &col_i)const ;
    //returns the linear transformation matrix that turns and input (caller) int o an output (input parameter)
    //input->system->output
    matrix transformer(const matrix&output)const ;

    bool is_valid_index(int  ,int  )const;

    //this works as a more efficient way to extract
    //pivots locations of an upper triangular matrix
    matrix<int>get_pindex(void);
    //compress the matrix no need to do anything just pass a function
    //and fill_features will analyze the function efficiently for speacial features
    //and will fill the matrix_type with the feature and compress it accordingly
    void compress(void);

    void decompress(void) ;

    //analyzes the function for special features and fills matrix_type
    void fill_features(double check_tol=1e-6);

    int start(int row_i)const ; //refers to start of non zero elements in a row

    int end(int row_i)const; //ends of non zero elements of a row (end of computations)
};



    //when calling do this
    //identity<DataType>
    template <typename DataType>
    matrix<DataType> identity(int );
    //returns randomly generated mahtrix
    //must specify dimensions
    //rand<DataType>
    template <typename DataType>
    matrix<DataType> rand(int  ,int  ,int  max_val=INT_MAX);

    //returns a column matrix representing
    //for i =0 to n-1 of w^i
    //used in fft
    matrix<complex> fourier_diagonal(int dimension,int  n);
    //returns fourier matrix which is used in
    //discrete fourier transform matrix
    matrix<complex> fourier_mat(int  dimension);

    //fill the matrix with its features if its symmetric
    //utri,ltri ,etc

#endif // VEC_H_INCLUDED
