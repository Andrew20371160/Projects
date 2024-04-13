#include "matrix_algebra.h"
/*-update : added fix_pivots() this function rearranges the matrix rows
so that the rows contatining the pivotsare on top and the rest of rows at bottom
its crucial when using functions like lu_fact not really since i added permutation matrix earlier
but if you use elementary matrix from null_rows() and tried to test if elementary * matrix euqals
rref(matrix) this sometimes isn't true since elementary matrix doesn't record the switches
in rows that happens during the rref of the matrix its advisable to use after you initialize the matrix
but i wouldn't force that its on you :) .
*/
matrix::matrix(){
        vec= NULL ;
        rows = 0;
        cols = 0 ;
    }
matrix::matrix(int r,int c,float value = 0){
        rows= r;
        cols= c;
        vec=get_vec(r,c) ;
        if(vec){
            for(int i =0 ;i<rows; i++){
                for(int j= 0 ;j<cols ;j++){
                    vec[i][j] = value;
                }
            }
    }
}
matrix ::~matrix(){
    for(int i = 0 ; i <rows ; i++){
        delete[]vec[i];
    }
        delete vec ;
        vec = NULL;
}

matrix::matrix(const matrix&mat){
    rows= mat.get_rows();
    cols= mat.get_cols();
    vec = get_vec(rows,cols) ;

    for(int i =0 ; i <rows; i++){
        for(int j = 0 ; j<cols ; j++){
            if(abs(mat.vec[i][j])>tolerance){
               vec[i][j] = mat.vec[i][j] ;
            }
            else{
                vec[i][j] = 0 ;
            }
        }
    }
}

matrix ::matrix(int r,int c , float*arr,int size){
    if(size<=r*c){
        rows= r;
        cols= c;
        vec=get_vec(r,c) ;
            for(int i =0 ;i<rows; i++){
                for(int j= 0 ;j<cols ;j++){
                if((i*c+j)<size){
                    vec[i][j] = arr[i*c+j];
                }
                //fill rest of elements with zeroes
                else{
                    vec[i][j] = 0;
                }
            }
        }
    }
}
int matrix ::get_rows()const{
    return rows ;
}

int matrix ::get_cols()const{
    return cols ;
}
//append cols of 2 matrices and return the new matrix
matrix matrix::append_cols(matrix&src){
    matrix ret_mat ;
    if(src.rows==rows){
        ret_mat = matrix(rows,cols+src.cols);
        for(int row_c = 0;row_c<rows;row_c++){
            for(int j= 0 ; j<cols;j++){
                ret_mat.vec[row_c][j] =vec[row_c][j] ;
            }
            for(int j= 0 ; j<src.cols;j++){
                ret_mat.vec[row_c][j+cols]=src.vec[row_c][j] ;
            }
        }
    }
    else{
        cout<<"can't append 2 matrices with different number of rows default garbage value is -1" ;
        ret_mat = matrix(1,1,-1) ;
    }
    return ret_mat ;
}
matrix matrix::append_rows(matrix&src){
    matrix ret_mat ;
    if(src.cols==cols){
        ret_mat = matrix(rows+src.rows,cols);
        for(int row_c = 0;row_c<rows+src.rows;row_c++){
            if(row_c<rows){
                for(int j= 0 ; j<cols;j++){
                    ret_mat.vec[row_c][j] =vec[row_c][j] ;
                }
            }
            else{
                for(int j= 0 ; j<cols;j++){
                    ret_mat.vec[row_c][j] =src.vec[row_c-rows][j] ;
                }
            }
        }
    }
    else{
        cout<<"can't append 2 matrices with different number of rows default garbage value is -1" ;
        ret_mat = matrix(1,1,-1) ;
    }
    return ret_mat ;
}
//append rows of 2 matrices and return the new matrix
float matrix::dot(matrix&mat)const{
    if(same_shape(mat)){
        float res = 0;
        for(int i = 0 ;i <rows;i++){
            for(int j = 0 ; j<cols ;j++){
                res+=mat.vec[i][j]*vec[i][j];
            }
        }
        return res ;
    }
    cout<<shape_error;
    return -1 ;
}
//performs a*x+y
float matrix ::axpy(float alpha,matrix&y)const{
    if(y.vec&&same_shape(y)){
        float res = 0;
         for(int i = 0 ;i <rows;i++){
            for(int j = 0 ; j<cols;j++){
                res+=alpha*vec[i][j]+y.vec[i][j] ;
            }
        }
        return res ;
    }
        cout<<shape_error ;
        return -1 ;
}

bool matrix ::same_shape(const matrix&mat)const{
    return ((mat.get_rows()==get_rows())&&(mat.get_cols()==get_cols())) ;
}

void matrix :: identity(){
    if(is_square()){
        for(int i = 0 ;i <rows;i++){
            for(int j = 0 ; j<cols ;j++){
                if(i==j){
                    vec[i][j] =1;
                }
                else{
                    vec[i][j] =0;
                }
           }
        }
    }
    else{
    cout<<square_error;
    }
}
//shows the matrix :)
void matrix :: show(void)const{
    if(vec){
        for(int row_counter=  0 ;  row_counter<rows; row_counter++){
            cout<<'\n' ;
            for(int col_counter = 0  ; col_counter<cols;col_counter++){
                cout<<vec[row_counter][col_counter]<<" ";
        }
    }
}
}
//turns the whole matrix into a string ease printing
string matrix::mat_to_string(void)const{
    string ret_str="" ;
    for(int i = 0 ; i<rows;i++){
        ret_str+='[' ;
        for(int j= 0 ; j<cols ;j++){
            ret_str+=to_string(vec[i][j]);
            if(j!=cols-1){
                ret_str+= " , " ;
            }
        }
        ret_str+="]\n" ;
    }
    return ret_str ;
}

matrix matrix:: operator+(matrix&mat)const{
    if(vec&&same_shape(mat)){
        matrix ret_mat(rows,cols) ;
        for(int i = 0 ;i<rows; i++){
            for(int j = 0 ; j<cols ;j++){
                ret_mat.vec[i][j] =  vec[i][j]+mat.vec[i][j];
            }
        }
        return ret_mat ;
    }
    cout<<shape_error ;
     matrix error_mat(1,1,-1);
    return error_mat  ;
}
// Subtract a matrix from caller
matrix matrix:: operator-(matrix&mat)const{
    if(vec&&same_shape(mat)){
        matrix ret_mat(rows,cols) ;
        for(int i = 0 ;i<rows; i++){
            for(int j = 0 ; j<cols ;j++){
              ret_mat.vec[i][j] = vec[i][j]-mat.vec[i][j];
            }
        }
        return ret_mat ;
    }
    cout<<shape_error ;
    matrix error_mat(1,1,-1) ;
    return error_mat ;
}
//returns a scaled up matrix
matrix matrix::operator*(float scalar)const{
    if(vec){
        matrix ret_mat(rows,cols)  ;
        for(int i = 0 ;i<rows; i++){
            for(int j = 0 ; j<cols ;j++){
                ret_mat.vec[i][j]=vec[i][j]*scalar ;
        }
    }

        return ret_mat  ;
    }
    cout<<uninit_error ;
    matrix error_mat(1,1,-1) ;
    return error_mat ;
}
matrix matrix:: operator * (matrix&mat)const{
    if(cols ==mat.rows){
        matrix ret_mat(rows,mat.cols,0) ;
        for(int row_counter=  0 ;  row_counter<rows; row_counter++){
            for(int col_counter = 0  ; col_counter<mat.cols;col_counter++){
                for(int ele_counter = 0 ; ele_counter <cols;ele_counter++){
                    ret_mat.vec[row_counter][col_counter]+= vec[row_counter][ele_counter]*mat.vec[ele_counter][col_counter];
                }
            }
        }
        return ret_mat;
    }
    cout<<shape_error ;
    matrix error_mat(1,1,-1) ;
    return error_mat ;
}

matrix matrix::transpose(void)const{
    if(vec){
        matrix ret_mat(cols,rows);
        for(int i = 0 ; i <rows;i++){
            for(int j = 0 ; j<cols;j++){
               ret_mat.vec[j][i]=vec[i][j];
            }
        }
        return ret_mat ;
    }
    cout<<square_error ;
    matrix error_mat(1,1,-1) ;
    return error_mat ;
}

float matrix ::trace(void)const{
    if(vec&&is_square()){
        int res = 0;
        for(int i = 0 ; i <rows;i++){
            res+=vec[i][i];
        }
        return res ;
    }
    cout<<square_error ;
    return -1 ;
}

bool matrix ::is_square(void)const{
    return rows==cols;
}

bool matrix ::is_symmetric(void){
    if(vec&&is_square()){
        for(int i = 0 ; i <rows;i++){
            for(int j=i+1;j<cols;j++){
                if(vec[i][j]!=vec[j][i]){
                    return false ;
            }
        }

    }
    return true ;
    }
    return false ;
}

bool matrix::is_diagonal(void) {
    if (vec && is_square()) {
        int zero_flag=true ;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j <cols; j++) {
                if (i != j &&abs(vec[i][j])>tolerance) {
                    return false;
                }
            else{
                //zero flag checks for diagonal elements so that it makes sure they aren't all zeroes
                zero_flag &=abs(vec[i][j])<tolerance;
            }
        }
    }
        return (zero_flag==false);
    }
    return false  ;
}

float matrix ::norm2(void) {
    if(vec){
        return sqrt(dot(*this)) ;
    }
    cout<<uninit_error ;
    return -1 ;
}

//same functionality as norm2 just different wrapper
float matrix ::length(void) {
    return norm2() ;
}

float matrix ::theta(matrix&mat) {
    //a.b  =|a||b|costheta
    //theta = acos(a.b/ab)
    if(same_shape(mat)){
        float len_a = length() ;
        float len_b = mat.length() ;
        float adotb = dot(mat) ;
        if(len_a>=tolerance&&len_b>=tolerance){
            float val =acos(adotb/(len_a*len_b)) ;
            return (val>=tolerance)?val*(180/M_PI):0 ;
        }
    }
    cout<<shape_error ;
    return -1 ;
}
// Check if this matrix is orthogonal
bool matrix ::is_orthogonal(void){
    matrix trans_mat = transpose() ;
    trans_mat = *this *trans_mat ;
    return trans_mat.is_identity() ;
}
//check if this matrix is orthogonal with matrix mat
bool matrix ::is_orthogonal(matrix&mat) {
    if(rows==mat.rows){
       matrix trans= transpose() ;
       trans = trans*mat ;
       return trans.is_zero() ;
    }
    return false ;
}

bool matrix :: is_parallel(matrix&mat){
    return  abs(theta(mat))<=tolerance||abs(theta(mat)-180)<=tolerance ;
}

bool matrix ::operator == (matrix&mat)const{
    if(same_shape(mat)){
       for (int i = 0; i < rows; i++){
            for (int j = 0; j <cols; j++) {
             if(abs(vec[i][j]-mat.vec[i][j])>tolerance){
                return false ;
            }
        }
    }
        return true ;
    }
    return false ;
}

//helper function
void matrix ::row_axpy(float scalar,int upper_row,int lower_row){
    for(int col_counter =0 ; col_counter<get_cols();col_counter++){
        vec[lower_row][col_counter]+= vec[upper_row][col_counter]*scalar;
    }
}
//performs downward gaussian elimination producing an upper triangular matrix
//optional if you want to know the indices of the pivots for each row
//pass in a matrix aka pivots_indices
matrix matrix ::gauss_down(matrix*pivots_indices=NULL,int pivots_locations=new_locations) {
    matrix ret_mat = *this;
    if(pivots_indices){
        if(pivots_locations==new_locations){
            *pivots_indices = matrix(rows,1,-1) ;
        }
        else{
            //here it will be permutaions matrix
            //to record each row exchange happening
            *pivots_indices = matrix(rows,rows);
             pivots_indices->identity();
        }
    }
    //when getting pivot indices we have to keep track of old pivot since
    //the new pivot won't exist in the same column so we go to next column each iteration
    int old_pivot = -1 ;
    for(int up_r = 0;up_r<rows; up_r++){
        //check for pivot in the next column
            //at first iteration we check for sure for first col hence 1-1 = 0
        int pivot_index =old_pivot+1  ;
        //if not a pivot then we find next pivot by increasing the pivot index
        //aka find it in the next column
        int pivot_condition = ret_mat.is_pivot(up_r,pivot_index) ;
        while(pivot_index<cols&&pivot_condition==-1){
            pivot_index++ ;
            pivot_condition = ret_mat.is_pivot(up_r,pivot_index);
        }
        //make sure you aren't out of bounds
        if(pivot_index<cols){
            if(pivots_indices){
                //if user wants new locations after switching rows
                if(pivots_locations==new_locations){
                        pivots_indices->vec[up_r][0] = pivot_index ;
                    }
                //else user wants the locations of pivots lying in original rows
                else if(pivots_locations==old_locations){
                    pivots_indices->switch_rows(up_r,pivot_condition) ;
                }
            }
            for(int low_r = up_r+1; low_r<rows; low_r++){
                //do gaussian elimination downward
                //check if lower element is not zero to save processing power
                if(abs(ret_mat.vec[low_r][pivot_index])>tolerance){
                    float c = -1*(ret_mat.vec[low_r][pivot_index]/ret_mat.vec[up_r][pivot_index]);
                    for(int i =pivot_index ; i<cols;i++){
                        ret_mat.vec[low_r][i]+=c*ret_mat.vec[up_r][i] ;
                    }
                }
            }
            //record that pivot to search for next pivot in the next column not in same column
            //as mentioned above
            old_pivot = pivot_index ;
        }
    }
    return ret_mat ;
}
//performs upward gaussian elimination producing a lower triangular matrix
//optional if you want to know the indices of the pivots for each row
//pass in a matrix aka pivots_indices
matrix matrix ::gauss_up(matrix *pivots_indices = NULL){
    matrix ret_mat = *this ;
    if(pivots_indices){
        *pivots_indices = matrix(rows,1,-1) ;
    }
    //same idea as gauss_down but instead of -1 its now rows since we look
    //for pivots from last row till first row
    int old_pivot =cols;
    for(int low_r = rows-1 ; low_r>=0;low_r--){
        //pivot_index in first iteration will be rows-1 which is the first location
        //to look for a pivot
        int pivot_index =old_pivot-1 ;
        //if not a pivot then we find next pivot by decreasing the pivot index
        //aka find it in the prev column
        while(pivot_index>=0&&ret_mat.is_pivot_up(low_r,pivot_index)==-1){
            pivot_index-- ;
        }
        if(pivot_index>=0){
            if(pivots_indices){
               pivots_indices->vec[low_r][0] = pivot_index ;
           }
        for(int up_r = low_r-1;up_r>=0;up_r--){
            if(abs(ret_mat.vec[up_r][pivot_index])>tolerance){
                float c = -1 * (ret_mat.vec[up_r][pivot_index]/ret_mat.vec[low_r][pivot_index]);
                    for(int col_c = pivot_index ; col_c>=0; col_c--){
                        ret_mat.vec[up_r][col_c]+= c*ret_mat.vec[low_r][col_c];

                }
            }
        }
        //keep track of pivot same as gauss_down
        old_pivot = pivot_index ;
    }
}
    return ret_mat ;
}
//this function switches 2 rows and returns state of switching meaning the rows are valid
bool matrix ::switch_rows(int r1 ,int r2 ){
    if(r1>=0&&r1<get_rows()&&r2>=0&&r2<get_rows()&&r1!=r2){
    for(int i = 0 ; i <get_cols();i++){
        swap(vec[r1][i],vec[r2][i]);
    }
    return true ;
}
    return false  ;
}
//performs back substitution on lower triangular invertible matrix
float matrix:: back_sub(int row_index,matrix&sol_mat){
    float sum  = vec[row_index][get_cols()-1];
    for(int col_counter = row_index+1  ;col_counter<get_cols()-1; col_counter++){
        sum-=vec[row_index][col_counter]*sol_mat.vec[col_counter][0];
    }
    return sum/vec[row_index][row_index] ;
}
//performs forward substitution on lower triangular invertible matrix
float matrix:: fwd_sub(int row_index,matrix&sol_mat){
    float sum  = vec[row_index][get_cols()-1];
    for(int col_counter = 0  ;col_counter<row_index;col_counter++){
        sum-=vec[row_index][col_counter]*sol_mat.vec[col_counter][0];
    }
    return sum/vec[row_index][row_index] ;
}

//pass an appended matrix
matrix matrix:: solve(void) {
    matrix pivots_indices;
    //turns the system into uppertriangular system
    matrix mat_cpy=gauss_down(&pivots_indices,new_locations);
    //check for number of pivots first
    for(int i = 0 ; i<rows;i++){
        if(pivots_indices.vec[i][0]==-1){
            cout<<"Number of pivots is insufficient default garbage value is -1" ;
            matrix ret_mat = matrix(1,1,-1);
            return ret_mat ;
        }
    }
    //the new matrix in which the answer will be returned
    matrix sol_mat(get_rows(),1,0) ;
    for(int row_c = get_rows()-1; row_c>=0;row_c--){
        sol_mat.vec[row_c][0] = mat_cpy.back_sub(row_c,sol_mat) ;
    }
    return sol_mat ;
}
//calculate determinant of a matrix
float matrix::det(){
//determinant is for square matrices
    if(is_square()){
        //here we store place of original pivots
        //we walk through the matrix from 0 to row -1
        //if you are at first row and the pivot location is originally
        //in the 3rd row then we multiply the determinant by -1
        //if there is no pivot we return 0 easy as that
        matrix original_pivots_indices ;
        matrix mat_cpy =gauss_down(&original_pivots_indices,old_locations) ;
        float det_val = 1 ;
        unsigned int sign_change = 0   ;
        for(int i= 0  ; i<rows;i++){
            if(original_pivots_indices.vec[i][i]!=1){
                sign_change++;
            }
            det_val*=mat_cpy.vec[i][i] ;
        }
        if(sign_change>0){
                return(sign_change%2==0)?det_val*-1:det_val ;
        }
        return det_val;

}
    cout<<square_error ;
    return -1 ;
}
//access and modify an element at a certain position
float& matrix ::at(int r_ind,int c_ind){
    if(r_ind>=0&&r_ind<rows&&c_ind>=0&&c_ind<cols){
        return vec[r_ind][c_ind] ;
    }
    cout<<"out of bounds";
}
//calculates inverse of a square matrix if available
matrix matrix ::inverse(void){
    if(is_square()){
        //copying the m matrix into mat_cpy
        matrix mat_cpy =*this ;
        //creating return matrix which at first will be identity
        matrix ret_mat(rows,cols) ;
        ret_mat.identity() ;
        //first do Gaussian elimination downward
        for(int up_r = 0 ; up_r<rows-1;up_r++){
                for(int low_r = up_r+1;low_r<rows;low_r++){
                    if(mat_cpy.is_pivot(up_r,up_r)!=-1){
                        float c = -1 * (mat_cpy.vec[low_r][up_r]/mat_cpy.vec[up_r][up_r]);
                        for(int col_c = 0 ; col_c<cols ; col_c++){
                            mat_cpy.vec[low_r][col_c]+= c*mat_cpy.vec[up_r][col_c] ;
                            ret_mat.vec[low_r][col_c] += c*ret_mat.vec[up_r][col_c];
                        }
                    }
                    else{
                        //if the pivot is zero then its not invertible matrix
                        cout<<"determinant of the passed matrix is zero or not squre matrix to begin with";
                        matrix error_matrix(1,1,-1);
                        return error_matrix ;
                    }
                }
            }
        //then do Gaussian elimination upward
            //here we don't need to check if its a pivot since its shown clearly
            //from first elemination that it contains pivots at each row
            for(int low_r = rows-1 ; low_r>0;low_r--){
                for(int up_r = low_r-1;up_r>=0;up_r--){
                    float c = -1 * (mat_cpy.vec[up_r][low_r] /mat_cpy.vec[low_r][low_r]);
                    for(int col_c = 0 ; col_c<cols ; col_c++){
                        mat_cpy.vec[up_r][col_c]+= c*mat_cpy.vec[low_r][col_c];
                        ret_mat.vec[up_r][col_c]+= c*ret_mat.vec[low_r][col_c];
                    }
                }
            }
            for(int i= 0 ; i<rows;i++){
                for(int j= 0 ; j<cols ; j++){
                    ret_mat.vec[i][j] /=mat_cpy.vec[i][i] ;
                }
            }
            return ret_mat ;
}
    cout<<"determinant of the passed matrix is zero or not a squre matrix to begin with";
    matrix error_matrix(1,1,-1);
    return error_matrix ;
}
//calculates A/B where A is left side and B is right
matrix matrix::operator/(matrix& m)const
{
        matrix ret_mat = m.inverse() ;
        if(ret_mat.rows<rows)
        {
        cout<<"determinant of the denum is zero";
        matrix error_matrix(1,1,-1);
        return error_matrix ;
        }
        return *this * ret_mat;
}
//this allows for multiple functions reuse old matrices , copy
void matrix::operator=(const matrix&mat){
    if(this!=&mat){
        //then check if they don't have same shape
        if(!same_shape(mat)){
            //delete old memeory
            if(vec!=NULL){
                for(int i =0  ;i<rows;i++){
                    delete[]vec[i] ;
                }
                delete vec ;
            }
            vec= NULL  ;
            //reallocate for copying
            rows = mat.rows;
            cols = mat.cols ;
            vec= get_vec(mat.get_rows(),mat.get_cols()) ;
        }
        //copying mechanism
        for(int i = 0 ; i <rows;i++){
            for(int j= 0 ; j<cols ;j++){
            if(abs(mat.vec[i][j])>tolerance){
                vec[i][j] = mat.vec[i][j] ;
            }
            else{
                vec[i][j] = 0  ;
            }
        }
        }

    }
}
// Check if this matrix is idempotent
bool matrix:: is_idempotent(void){
    matrix mat = (*this)*(*this) ;
    return mat == *this ;
}
//tested
// Check if this matrix is identity
bool matrix:: is_identity(void){
        if(is_square()){
    for(int i = 0 ; i<rows;i++){
        for(int j= 0 ; j<cols; j++){
            if(i==j){
                if(abs(vec[i][j]-1)>tolerance) {
                    return false ;
                }
            }
            else{
                if(abs(vec[i][j])>tolerance){
                    return false ;
                }
            }
    }
}
return true ;
}
return false ;
}//tested
    // Check if this matrix is the zero matrix
bool matrix ::is_zero(void){
    for(int i = 0; i<rows;i++){
        for(int j= 0 ;j<cols ;j++){
            if(abs(vec[i][j])>tolerance){
                return false ;
            }
        }
    }
    return true ;
}

bool matrix::is_upper_tri(void) {
    if(is_square()){
     bool zero_flag= true ;
        for(int i =0 ; i <rows;i++){
            for(int j=  0 ; j<cols; j++){
                if(j<i){
                    if(abs(vec[i][j])<tolerance){
                        return false ;
                    }
                }
                else{
                    //check for rest of elements so that they aren't all zeroes
                    zero_flag&=(abs(vec[i][j])<tolerance)?false:true ;
                }
            }
        }
        if(zero_flag!=true){
            return true ;
        }
    }
    return false ;
}

bool matrix::is_lower_tri() {
if(is_square()){
 bool zero_flag= true ;
    for(int i =0 ; i <rows;i++){
        for(int j=  0 ; j<cols; j++){
            if(j>i){
                if(abs(vec[i][j])<tolerance){
                    return false ;
                }
            }
            else{
                //check for rest of elements so that they aren't all zeroes
                zero_flag&=(abs(vec[i][j])<tolerance)?false:true ;
            }
        }
    }
    if(zero_flag!=true){
        return true ;
    }
}
return false ;
}

// Check if this matrix is scalar
bool matrix:: is_scalar(void){//tested
    if(is_square()){
        int val = vec[0][0] ;
        for(int i=  0 ; i<rows; i++){
            for(int j= 0  ;j<cols ; j++){
                if(i==j){
                    if(abs(vec[i][j]-val)>tolerance){
                        return false ;
                    }
                }
                else{
                    if(abs(vec[i][j])>tolerance){
                        return false ;
                    }
                }
            }
        }
    return true ;
    }
    return false ;
}
// Calculate the rank of this matrix
int matrix ::rank(void){//tested
    matrix pivots_indices ;
    //first perform gaussian elimination downward
        gauss_down(&pivots_indices) ;
        int counter = 0;
        //then count number of pivots
        for(int i = 0 ;i<rows ; i++){
            if(pivots_indices.vec[i][0]!=-1){
                counter ++ ;
            }
            else{
                break  ;
            }
        }
        return counter ;
}//tested

// Check if this matrix is skew-symmetric
bool matrix ::is_skew_symmetric(void){
    if(vec&&is_square()){
        for(int i = 0 ; i <rows;i++){
            for(int j=i+1;j<cols;j++){
                if(abs(vec[i][j]-vec[j][i])>tolerance){
                    return false ;
            }
        }

    }
    return true ;
    }
    return false ;

}

// Check if this matrix is nilpotent
bool matrix :: is_nilpotent(void){
    if(is_square()){
        //keep multiplying the matrix by itself untill the nth power
        matrix mat_pow = *this ;
        matrix zeroes(rows,cols,0) ;
        for(int i = 0 ; i<rows ; i++){
            if(mat_pow==zeroes){
                return true ;
            }
            else{
                mat_pow =  mat_pow*mat_pow ;
            }
        }
        return false ;
    }
    return false ;
}

// Check if this matrix is involutory
bool matrix :: is_involutory(void){
    if(is_square()){
        matrix temp =(*this)*(*this)  ;
        return temp.is_identity();
    }
    cout<<square_error ;
    return false ;
}
//added permutation matrix since during lu factorization if the rows are switched
//if the pivot is not in its position it will be switched we have to keep track of this
//using permutation matrix its set first as identity but if rows are switched
//the rows of the identity are switched aswell
void matrix:: lu_fact(matrix&lower_fact,matrix&permutation,matrix&upper_fact) {
    //first check if its square matrix
    if(is_square()){
        //the lower_fact matrix is the identity matrix (at first) in which we store
        // the constants during the gaussian elimination of the original matrix
        //after finisning the gaussian elimination the upper_fact is finished
        lower_fact = matrix(rows,cols,0);
        lower_fact.identity() ;
        //if permutations happen its recorded in this matrix
        permutation = matrix(rows,cols,0);
        permutation.identity() ;
        //copy original matrix into upper_fact to performa gaussian elimination on it
        upper_fact = *this  ;
        for(int up_r = 0;up_r<rows; up_r++){
            int pivot_condition =upper_fact.is_pivot(up_r,up_r);
            if(pivot_condition!=-1){
                //aka its a pivot
                //if a switch happened
            if(pivot_condition!=up_r){
                  permutation.switch_rows(up_r,pivot_condition);
            }
                //no switch happened
            for(int low_r = up_r+1; low_r<rows-1; low_r++){
                    //check first if upper element is a pivot
                    //the constant we calculate
                    float c = -1*(upper_fact.vec[low_r][up_r]/upper_fact.vec[up_r][up_r]);
                    //first record it into the lower_fact matrix at its position
                    lower_fact.vec[low_r][up_r]  = -1* c ;
                    for(int i =0 ; i<cols;i++){
                        //then continue the gaussian elimination
                        upper_fact.vec[low_r][i]+=c*upper_fact.vec[up_r][i] ;
                    }
                }
 }
                else{
                cout<<"matrix doesn't have an inverese" ;
                lower_fact =  matrix(1,1,-1) ;
                upper_fact =  matrix(1,1,-1) ;
                return ;
                }
            }
        }
    else{
        cout<<square_error;
        lower_fact =  matrix(1,1,-1) ;
        upper_fact =  matrix(1,1,-1) ;
    }
}
//this function checks if an element is a pivot
//and switches the rows if the original element is not a pivot
//with the first non zero element it finds
//now updated to return the row of the pivot to keep record of the rows
//if rows are switched used in lu_fact
int matrix:: is_pivot(int r_ind , int c_ind) {
    if(r_ind<rows&&c_ind<cols){
        //find first non zero element in that row
        int pivot_index = r_ind ;
        while(pivot_index<rows){
            if(abs(vec[pivot_index][c_ind])>tolerance){
                //if you found a non zero element
                //if its not the original element
                //element at r_ind , c_ind rows are switched
                //and this is the new pivot and the function ends
                if(pivot_index!=r_ind){
                    switch_rows(pivot_index,r_ind);
                    //notice we returned pivot_index not r_ind since the rows
                    //were switched
                    return pivot_index ;
                }
                return r_ind ;
            }
            //else check for next element or col
            pivot_index++;
        }
    return -1 ;
    }
    return -1 ;
}
//this function checks if an element is a pivot
//and switches the rows if the original element is not a pivot
//with the first non zero element it finds
int matrix:: is_pivot_up(int r_ind , int c_ind) {
    if(r_ind<rows&&c_ind<cols){
        //find first non zero element in that row
        int pivot_index = r_ind ;
        while(pivot_index>0){
            if(abs(vec[pivot_index][c_ind])>tolerance){
                //if you found a non zero element
                //if its not the original element
                //element at r_ind , c_ind rows are switched
                //and this is the new pivot and the function ends
                if(pivot_index!=r_ind){
                    switch_rows(pivot_index,r_ind);
                    return pivot_index ;
                }
                return r_ind ;
            }
            //else chec for next element or col
            pivot_index--;
        }
    return -1 ;
    }
    return -1 ;
}
//this function returns reduced row echolon form of the matrix
//and saves pivots locations in the input pivots matrix for each row containing
//a pivot it saves that pivot location in that row index
matrix matrix :: rref(matrix&pivots_indices){
    //pivots locations will be mapped in this array
    //so if row zero contains a pivot at col index 1  for ex and so on
    //it will have the value 1 in that row and so on
    //return matrix
    //do gaussian elemination downward
    matrix ret_mat = gauss_down(&pivots_indices);
    //do gaussian elimination upward using the pivots_locations
    for(int low_r = rows-1 ; low_r>0;low_r--){
        int pivot_index = pivots_indices.vec[low_r][0];
        if(pivot_index!=-1){
            for(int up_r = low_r-1;up_r>=0;up_r--){
                float c = -1 * (ret_mat.vec[up_r][pivot_index] /ret_mat.vec[low_r][pivot_index]);
                for(int col_c = 0 ; col_c<cols ; col_c++){
                    ret_mat.vec[up_r][col_c]+= c*ret_mat.vec[low_r][col_c];
            }
        }
   }
}
    //go in each row and if that row contains a pivot divid each element by
    //by the pivot
    for(int i = 0 ; i<rows;i++){
        int pivot_index = pivots_indices.vec[i][0];
        if(pivot_index!=-1){
            float val = ret_mat.vec[i][pivot_index];
            if(val){
                for(int j=  0 ; j<cols;j++){
                    ret_mat.vec[i][j]/=val ;
                    //tolerance
                    ret_mat.vec[i][j] = (abs(ret_mat.vec[i][j])<tolerance)?0:ret_mat.vec[i][j];
                }
            }
        }
        else{
            //no more pivots
            break ;
        }
    }

    return ret_mat ;
}
//checks if a set of vectors in a column space are independent
bool matrix ::is_independent(void){
    return rank() ==cols ;
}

// Calculates the dimension of the column space (range) of the matrix.
// The column space consists of all possible linear combinations of the column vectors in the matrix.
int matrix ::dim(void){
    return rank() ;
}//tested
//returns dimension of the null space of column space
int matrix ::dim_null_cols(void){
    return cols - rank();
}
//returns dimension of the null space of row space
int matrix ::dim_null_rows(void){
    return rows - rank() ;
}
//checks if a bunch of vectors form basis of a space R^dimension
bool matrix ::is_basis( int dimension){
    //check if they are independent and they span the column space of R^dimension
    return cols==dimension&&is_independent() ;
}
//returns the set of vectors that forms a basis of the column space
matrix matrix ::basis_cols(void) {
    //return matrix
    matrix ret_mat ;
    //matrix in which we store indicex of each pivot in the correspoinding row
    matrix pivots_indices ;
    //perform gaussian elimination downward
    gauss_down(&pivots_indices) ;
    //get dimension of the column space
    int pivot_count = 0 ;
    //count number of pivots and stop when you find -1
    //aka no remaining pivots refer to is_pivot and check what it does for
    //more info
    for(int i = 0 ;i<rows; i++){
        if(pivots_indices.vec[i][0]!=-1){
            pivot_count++ ;
        }
        else{
            break ;
        }
    }
        //we store each column carrying a pivot in this matrix
        ret_mat = matrix(rows,pivot_count);
        //for each element in ret_mat
        for(int row_c = 0 ; row_c<rows ; row_c++){
            for(int col_c =0 ; col_c<pivot_count; col_c++){
                //get the pivot index in that row
                int pivot_index=pivots_indices.vec[col_c][0] ;
                //store the correspoinding element in the pivot's column
                //in ret_mat
                ret_mat.vec[row_c][col_c] =vec[row_c][pivot_index] ;
            }
        }
    return ret_mat ;
}
    // Returns a set of vectors (as a matrix) that forms a basis for the vector space of the given dimension.
    matrix matrix:: basis_rows(void){
        matrix ret_mat ;
        matrix pivots_indices(rows,1,-1);
            //perform gaussian elimination downward
        matrix mat_rref = rref(pivots_indices) ;
        //get dimension of the column space
        int pivot_count = 0 ;
        //count number of pivots and stop when you find -1
        //aka no remaining pivots refer to is_pivot and check what it does for
        //more info
        for(int i = 0 ;i<rows; i++){
            if(pivots_indices.vec[i][0]!=-1){
                pivot_count++ ;
            }
            else{
                break ;
            }
        }
        //copy first rows that are the pivot rows from rref
        ret_mat = matrix(pivot_count,cols) ;
        for(int i = 0 ; i<pivot_count;i++){
            for(int j = 0 ;  j<cols; j++){
                ret_mat.vec[i][j]  = abs(mat_rref.vec[i][j])>tolerance?mat_rref.vec[i][j]:0;
            }
        }
        return ret_mat ;
    }

//where e*A = rref(A)
//matrix e is optional if you want to use it if you pass a matrix as an input
//this matrix returns the null space of row space
matrix matrix:: null_rows(matrix*e= NULL) {
    //pivots indices are stored here
    matrix pivots_indices(rows,1,-1) ;
    matrix elementary=matrix(rows,rows);
    elementary.identity() ;
    matrix mat_cpy = *this ;
    mat_cpy.fix_pivots();
    //when getting pivot indices we have to keep track of old pivot since
    //the new pivot won't exist in the same column so we go to next column each iteration
    int old_pivot = -1 ;
    for(int up_r = 0;up_r<rows; up_r++){
        //check for pivot in the next column
            //at first iteration we check for sure for first col hence 1-1 = 0
        int pivot_index =old_pivot+1  ;
        //if not a pivot then we find next pivot by increasing the pivot index
        //aka find it in the next column
        while(pivot_index<cols&&mat_cpy.is_pivot(up_r,pivot_index)==-1){
            pivot_index++ ;
        }
        //make sure you aren't out of bounds
        if(pivot_index<cols){
            pivots_indices.vec[up_r][0] = pivot_index ;
            for(int low_r = up_r+1; low_r<rows; low_r++){
                //do gaussian elimination downward
                //check if lower element is not zero to save processing power
                if(abs(mat_cpy.vec[low_r][pivot_index])>tolerance){
                    float c = -1*(mat_cpy.vec[low_r][pivot_index]/mat_cpy.vec[up_r][pivot_index]);
                    for(int i =pivot_index ; i<cols;i++){
                        mat_cpy.vec[low_r][i]+=c*mat_cpy.vec[up_r][i] ;
                    }
                    for(int i =0 ; i<rows;i++){
                        elementary.vec[low_r][i] +=c*elementary.vec[up_r][i] ;
                    }
                }
            }
            //record that pivot to search for next pivot in the next column not in same column
                //as mentioned above
            old_pivot = pivot_index ;
        }
    }
    //do gaussian elimination upward using the pivots_locations
    for(int low_r = rows-1 ; low_r>0;low_r--){
        int pivot_index = pivots_indices.vec[low_r][0];
        if(pivot_index!=-1){
            for(int up_r = low_r-1;up_r>=0;up_r--){
                float c = -1 * (mat_cpy.vec[up_r][pivot_index] /mat_cpy.vec[low_r][pivot_index]);
                for(int col_c = 0 ; col_c<cols ; col_c++){
                    mat_cpy.vec[up_r][col_c]+=c*mat_cpy.vec[low_r][col_c] ;
                }
                for(int col_c = 0 ; col_c<rows ; col_c++){
                    elementary.vec[up_r][col_c]+= c*elementary.vec[low_r][col_c];
                }
        }
   }
}
    //go in each row and if that row contains a pivot divide each element by
    //by the pivot
    int pivot_c = 0 ;
    for(; pivot_c<rows;pivot_c++){
        int pivot_index = pivots_indices.vec[pivot_c][0];
        //if the following row contains a pivot then we divide the whole row by that pivot
        if(pivot_index!=-1){
            float val = mat_cpy.vec[pivot_c][pivot_index];
            if(val){
                //do that for each element in the row
                for(int j=  0 ; j<rows;j++){
                    elementary.vec[pivot_c][j]/=val ;
                    //tolerance
                    elementary.vec[pivot_c][j] = (abs(elementary.vec[pivot_c][j])<tolerance)?0:elementary.vec[pivot_c][j];
                }
            }
        }
        //if there is no more pivots then break and head for null space of row space matrix
        else{
            break ;
        }
    }
    //make sure the matrix has dimension in the null space of the row space
    matrix ret_mat;
    if(rows-pivot_c>0){
    ret_mat=matrix(rows-pivot_c,rows);
    int c= 0  ;//counter for rows of return matrix
    for(; pivot_c<rows;pivot_c++){
        for(int j = 0 ; j<rows; j++){
            ret_mat.vec[c][j] = elementary.vec[pivot_c][j] ;
        }
        c++;
    }
}
else{
     ret_mat= matrix(1,rows,0);
}
    if(e){
        //if the user wants the elementary matrix then do the copying into e
        *e= elementary ;
    }
return ret_mat ;
}
matrix matrix ::null_cols(void) {
    //here the pivots indices are stored along with indices of free variables
    matrix pivots_indices =matrix(cols,1,-1);
    //here the pivots indices are stored
    matrix p_cpy ;
    matrix mat_rref = rref(p_cpy) ;
    //solution matrix with all speacial solutions
    matrix ret_mat;
    //copy the content from p_cpu into pivots indices
    int c=  cols<rows?cols:rows ;
    for(int i = 0 ; i<c;i++){
        pivots_indices.vec[i][0] = p_cpy.vec[i][0]  ;
    }
    //counting number of pivots to check if there are special solutions
    int pivot_c  =0   ;
    while(pivot_c<cols&&pivots_indices.vec[pivot_c][0]!=-1){
        pivot_c++;
    }
    if(pivot_c<cols){
        int counter=0 ;
        //fill rest of pivots_indices with free vars indices
        for(int i = 0 ; i<cols;i++){
            //for each index that is not a pivot put it in
            //the rest of the pivots_indices
            bool flag=  false ;
            for(int j= 0 ; j<pivot_c; j++){
                if(i==pivots_indices.vec[j][0]){
                    flag=true ;
                    break;
                }
            }
            if(!flag){
                //if its not a pivot put it
                pivots_indices.vec[pivot_c+counter][0] =i ;
                counter++;
            }
        }
        //cols -pivot_c = number of free variables
        ret_mat = matrix(cols,(cols-pivot_c),0) ;
        //when calculating special solutions
        //the pattern 0 0 1 , 0 1 0 , 1 0 0
        //for x5 ,x4 x3 respectively where they are free variables
        //for example
        //put the one at the position where the first free variable
        //locates
        //for each column of the special solution
        for(int i = (cols-pivot_c)-1;i>=0;i--){
            int one_pos = pivots_indices.vec[cols-i-1][0] ;
            //put the one in its postion for the new special solution
            ret_mat.vec[one_pos][i] =1 ;
            //for the current pivot we are calculating the value for
            //"index of the pivot in special solution matrix"
            for(int curr_piv= pivot_c-1 ; curr_piv>=0; curr_piv--){
                //x1 = (-x3*2-x2*2)/3
                //x0 = (-x3*2-x2*2-x1*3)/4
                int pivot_index = pivots_indices.vec[curr_piv][0];
                for(int j= cols-1  ; j>curr_piv;j--){
                    int free_v_index= pivots_indices.vec[j][0];
                    ret_mat.vec[pivot_index][i]
                    -=mat_rref.vec[curr_piv][free_v_index]*ret_mat.vec[j][i];
                }
            }
            }
    return ret_mat ;
        }
    //else there is only the zero solution to this matrix
    //aka number of pivots equal number of cols
    ret_mat = matrix(cols,1,0);
    return ret_mat ;
}
//it fixes a matrix by putting rows that corresponds to pivots first
//then rist of rows at th every end this fixes an issue at rref
//where if a row switch occurs it won't be recorded in elementary matrix
//or you will need extra permutation matrix fixes the caller itself
void matrix ::fix_pivots(void) {
    matrix  original_pivots_indices ;
    gauss_down(&original_pivots_indices,old_locations) ;
    *this = original_pivots_indices*(*this) ;
}
matrix matrix::projection(void){
/*
    Ax=b has no solution
    AT*A x* =AT*b
    x* = (AT*A )^-1 *AT b
    p = Ax* so P = A*(AT*A)^-1 * AT *b
    so projection matrix where p =projection b
    projection = A*(AT*A)^-1 *AT
*/
    matrix Atrans = transpose() ;
    matrix AtransA = Atrans *(*this) ;
    //get inverse
    AtransA = AtransA.inverse() ;
    //projection matrix for a system A
    //p  = A (AT A)^-1 AT
    return *this *AtransA* Atrans ;
}
//fit a data set into a linear system
//Ax=b can't be solved
//AT*A* x* = AT*b
//now solvable
matrix matrix ::fit_least_squares(matrix &data_set) {
    matrix Atrans = transpose() ;
    //AT *A
    matrix ret_mat = Atrans*(*this);
    //append and solve [AT*A|AT*b]
    Atrans= Atrans*data_set;
    ret_mat = ret_mat.append_cols(Atrans) ;
    return ret_mat.solve();
}

matrix matrix ::extract_col(int index){
    matrix ret_mat ;
    if(index>=0&&index<cols){
        ret_mat= matrix(rows,1);
        for(int i =0;i<rows;i++){
            ret_mat.vec[i][0] = vec[i][index] ;
        }
    }
    else{
        ret_mat = matrix(1,1,-1) ;
        cout<<"out of bounds default garbage value is -1";
    }
    return ret_mat  ;
}
//this function takes a bunch of vectors in a matrix and returns
//the orthonormal vectors in a form of matrix (performs gram-shmidt algorithm)
matrix matrix ::gram_shmidt(void){
    //array of projections for each vector from 0 to n-1
    //no need for the nth
    matrix projections_arr[cols-1];
    //here we store each orthonormal vector
    matrix ret_mat(rows,cols);
    //temporary storage for the resultant vector
    matrix res ;
    //here we store projection[i]*vec
    matrix p;

    matrix temp ;
    //length of a vector variable
    float len = 0;
    //for each vector
    for(int vec_c =0; vec_c <cols;vec_c++){
        //Vn = v- P0*v-P1*v
        //these projections are projections of the new obtained
        //orthogonal vectors
        //res=  v
        res = extract_col(vec_c) ;
        //temp storage for the column itself
        temp = res;
        for(int proj_c = 0;proj_c<vec_c ;proj_c++){
            //get projection of each vector * same vector
            //while subtracting it from the result
            p   = projections_arr[proj_c]*temp;
            res = res -p;
        }
        //get the length
        len=res.length();
        for(int row_c = 0 ; row_c<rows;row_c++){
            //while filling the result column divide by the length
            ret_mat.vec[row_c][vec_c] =res.vec[row_c][0]/len;
        }
        //get the projection of the newly created vector
        projections_arr[vec_c] = res.projection();
    }
    return ret_mat ;
}
