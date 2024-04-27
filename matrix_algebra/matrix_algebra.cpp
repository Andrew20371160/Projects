#include "matrix_algebra.h"
/*-update : added fix_pivots() this function rearranges the matrix<DataType>rows
so that the rows contatining the pivotsare on top and the rest of rows at bottom
its crucial when using functions like lu_fact not really since i added permutation matrix<DataType>earlier
but if you use elementary matrix<DataType>from null_rows() and tried to test if elementary * matrix<DataType>euqals
rref(matrix) this sometimes isn't true since elementary matrix<DataType>doesn't record the switches
in rows that happens during the rref of the matrix<DataType>its advisable to use after you initialize the matrix
but i wouldn't force that its on you :) .
*/
template<typename DataType>
matrix<DataType>::matrix(){
        vec= NULL ;
        rows = 0;
        cols = 0 ;
    }
template<typename DataType>
matrix<DataType>::matrix(int r,int c,DataType value){
        rows= r;
        cols= c;
        vec=get_vec(r,c) ;
        if(vec){
            for(int i =0 ;i<rows; i++){
                for(int j= 0 ;j<cols ;j++){
                    at(i,j) = value;
                }
            }
    }
}
template <typename DataType>
matrix<DataType>::~matrix(){
    delete[] vec ;
    vec = NULL;
}
template <typename DataType>
matrix<DataType>::matrix(const matrix&mat){
    rows= mat.get_rows();
    cols= mat.get_cols();
    vec = get_vec(rows,cols) ;
    for(int i =0 ; i <rows; i++){
        for(int j = 0 ; j<cols ; j++){
            if(abs(mat.at(i,j))>tolerance){
               at(i,j) = mat.at(i,j);
            }
            else{
                at(i,j) = 0 ;
            }
        }
    }
}

template <typename DataType>
matrix<DataType>::matrix(int r,int c , DataType*arr,int size){
    if(size<=r*c){
        rows= r;
        cols= c;
        vec=get_vec(r,c) ;
            for(int i =0 ;i<rows; i++){
                for(int j= 0 ;j<cols ;j++){
                if((i*c+j)<size){
                    at(i,j) = arr[i*c+j];
                }
                //fill rest of elements with zeroes
                else{
                    at(i,j) = 0;
                }
            }
        }
    }
}
template <typename DataType>
int matrix<DataType>::get_rows()const{
    return rows ;
}
template <typename DataType>
int matrix<DataType>::get_cols()const{
    return cols ;
}
//append cols of 2 matrices and return the new matrix
template <typename DataType>
matrix<DataType> matrix<DataType>::append_cols(const matrix&src)const {
    matrix<DataType>ret_mat ;
    if(src.rows==rows){
        ret_mat = matrix<DataType>(rows,cols+src.cols);
        for(int row_c = 0;row_c<rows;row_c++){
            for(int j= 0 ; j<cols;j++){
                ret_mat.at(row_c,j) =at(row_c,j) ;
            }
            for(int j= 0 ; j<src.cols;j++){
                ret_mat.at(row_c,j+cols)=src.at(row_c,j) ;
            }
        }
    }
    else{
        cout<<"can't append 2 matrices with different number of rows default garbage value is -1" ;
        ret_mat = matrix(1,1,-1) ;
    }
    return ret_mat ;
}
template <typename DataType>
matrix<DataType> matrix<DataType>::append_rows(const matrix&src)const {
    matrix<DataType>ret_mat ;
    if(src.cols==cols){
        ret_mat = matrix(rows+src.rows,cols);
        for(int row_c = 0;row_c<rows+src.rows;row_c++){
            if(row_c<rows){
                for(int j= 0 ; j<cols;j++){
                    ret_mat.at(row_c,j) =at(row_c,j) ;
                }
            }
            else{
                for(int j= 0 ; j<cols;j++){
                    ret_mat.at(row_c,j) =src.at(row_c-rows,j) ;
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
template <typename DataType>
DataType matrix<DataType>::dot(const matrix&mat)const{
    if(same_shape(mat)){
        DataType res = 0;
        for(int i = 0 ;i <rows;i++){
            for(int j = 0 ; j<cols ;j++){
                res+=mat.at(i,j)*conjugate(at(i,j));
            }
        }
        return res ;
    }
    cout<<shape_error;
    return -1 ;
}
//performs a*x+y
template <typename DataType>
DataType matrix<DataType>::axpy(DataType alpha,const matrix&y)const{
    if(y.vec&&same_shape(y)){
        DataType res = 0;
         for(int i = 0 ;i <rows;i++){
            for(int j = 0 ; j<cols;j++){
                res+=alpha*at(i,j)+y.at(i,j) ;
            }
        }
        return res ;
    }
        cout<<shape_error ;
        return -1 ;
}
template <typename DataType>

bool matrix<DataType>::same_shape(const matrix&mat)const{
    return ((mat.get_rows()==get_rows())&&(mat.get_cols()==get_cols())) ;
}
template <typename DataType>
void matrix<DataType>:: identity(){
    if(is_square()){
        for(int i = 0 ;i <rows;i++){
            for(int j = 0 ; j<cols ;j++){
                if(i==j){
                    at(i,j) =1;
                }
                else{
                    at(i,j) =0;
                }
           }
        }
    }
    else{
    cout<<square_error;
    }
}
//shows the matrix<DataType>:)
template <typename DataType>
void matrix<DataType>:: show(void)const {
    if(vec){
        for(int row_counter=  0 ;  row_counter<rows; row_counter++){
            cout<<'\n' ;
            for(int col_counter = 0  ; col_counter<cols;col_counter++){
                cout<<at(row_counter,col_counter)<<" ";
        }
    }
}
}
//turns the whole matrix<DataType>into a string ease printing
template <typename DataType>
string matrix<DataType>::mat_to_string(void)const{
    string ret_str="" ;
    for(int i = 0 ; i<rows;i++){
        ret_str+='[' ;
        for(int j= 0 ; j<cols ;j++){
            ret_str+=to_string(at(i,j));
            if(j!=cols-1){
                ret_str+= " , " ;
            }
        }
        ret_str+="]\n" ;
    }
    return ret_str ;
}
template <typename DataType>

matrix<DataType> matrix<DataType>:: operator+(const matrix&mat)const{
    if(vec&&same_shape(mat)){
        matrix<DataType>ret_mat(rows,cols) ;
        for(int i = 0 ;i<rows; i++){
            for(int j = 0 ; j<cols ;j++){
                ret_mat.at(i,j) =  at(i,j)+mat.at(i,j);
            }
        }
        return ret_mat ;
    }
    cout<<shape_error ;
     matrix<DataType>error_mat(1,1,-1);
    return error_mat  ;
}
// Subtract a matrix<DataType>from caller
template <typename DataType>
matrix<DataType> matrix<DataType>:: operator-(const matrix&mat)const{
    if(vec&&same_shape(mat)){
        matrix<DataType>ret_mat(rows,cols) ;
        for(int i = 0 ;i<rows; i++){
            for(int j = 0 ; j<cols ;j++){
              ret_mat.at(i,j) = at(i,j)-mat.at(i,j);
            }
        }
        return ret_mat ;
    }
    cout<<shape_error ;
    matrix<DataType>error_mat(1,1,-1) ;
    return error_mat ;
}
//returns a scaled up matrix
template <typename DataType>
matrix<DataType> matrix<DataType>::operator*(DataType scalar)const{
    if(vec){
        matrix<DataType>ret_mat(rows,cols)  ;
        for(int i = 0 ;i<rows; i++){
            for(int j = 0 ; j<cols ;j++){
                ret_mat.at(i,j)=at(i,j)*scalar ;
        }
    }

        return ret_mat  ;
    }
    cout<<uninit_error ;
    matrix<DataType>error_mat(1,1,-1) ;
    return error_mat ;
}
template <typename DataType>
matrix<DataType> matrix<DataType>:: operator * (const matrix&mat)const{
    if(cols ==mat.rows){
        matrix<DataType>ret_mat(rows,mat.cols,0) ;
        for(int row_counter=  0 ;  row_counter<rows; row_counter++){
            for(int col_counter = 0  ; col_counter<mat.cols;col_counter++){
                for(int ele_counter = 0 ; ele_counter <cols;ele_counter++){
                    ret_mat.at(row_counter,col_counter)+= at(row_counter,ele_counter)*mat.at(ele_counter,col_counter);
                }
            }
        }
        return ret_mat;
    }
    cout<<shape_error ;
    matrix<DataType>error_mat(1,1,-1) ;
    return error_mat ;
}
template <typename DataType>
matrix<DataType> matrix<DataType>::transpose(void)const{
    if(vec){
        matrix<DataType>ret_mat(cols,rows);
        for(int i = 0 ; i <rows;i++){
            for(int j = 0 ; j<cols;j++){
               //don't worry conjugate is overloaded
               //so that if its any data type other than complex
               //it does nothing but if its a complex number
               //it produces the conjugate
               ret_mat.at(j,i)=conjugate(at(i,j));
            }
        }
        return ret_mat ;
    }
    cout<<square_error ;
    matrix<DataType> error_mat(1,1,-1) ;
    return error_mat ;
}
template <typename DataType>
DataType matrix<DataType>::trace(void)const{
    if(vec&&is_square()){
        int res = 0;
        for(int i = 0 ; i <rows;i++){
            res+=at(i,i);
        }
        return res ;
    }
    cout<<square_error ;
    return -1 ;
}
template <typename DataType>
bool matrix<DataType>::is_square(void)const{
    return rows==cols;
}
template <typename DataType>

bool matrix<DataType>::is_symmetric(void)const {
    if(vec&&is_square()){
        for(int i = 0 ; i <rows;i++){
            for(int j=i+1;j<cols;j++){
                if(at(i,j)!=conjugate(at(j,i))){
                    return false ;
            }
        }

    }
    return true ;
    }
    return false ;
}
template <typename DataType>

bool matrix<DataType>::is_diagonal(void) const {
    if (vec && is_square()) {
        int zero_flag=true ;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j <cols; j++) {
                if (i != j &&abs(at(i,j))>tolerance) {
                    return false;
                }
            else{
                //zero flag checks for diagonal elements so that it makes sure they aren't all zeroes
                zero_flag &=abs(at(i,j))<tolerance;
            }
        }
    }
        return (zero_flag==false);
    }
    return false  ;
}
template <typename DataType>
DataType matrix<DataType>::norm2(void) const {
    if(vec){
        return sqrt(abs(dot(*this))) ;
    }
    cout<<uninit_error ;
    return -1 ;
}
//same functionality as norm2 just different wrapper
template <typename DataType>
DataType matrix<DataType>::length(void) const {
    return norm2() ;
}
template <typename DataType>
DataType matrix<DataType>::theta(matrix&mat) const {
    //a.b  =|a||b|costheta
    //theta = acos(a.b/ab)
    if(same_shape(mat)){
        DataType len_a = length() ;
        DataType len_b = mat.length() ;
        DataType adotb = dot(mat) ;
        if(len_a>=tolerance&&len_b>=tolerance){
            DataType val =acos(abs(adotb/(len_a*len_b))) ;
            return (val>=tolerance)?val*(180/M_PI):0 ;
        }
    }
    cout<<shape_error ;
    return -1 ;
}
// Check if this matrix<DataType>is orthogonal
template <typename DataType>
bool matrix<DataType>::is_orthogonal(void)const {
    matrix<DataType>trans_mat = transpose() ;
    trans_mat = *this *trans_mat ;
    return trans_mat.is_identity() ;
}
//check if this matrix<DataType>is orthogonal with matrix<DataType>mat
template <typename DataType>
bool matrix<DataType>::is_orthogonal(const matrix&mat) const {
    if(rows==mat.rows){
       matrix<DataType>trans= transpose() ;
       trans = trans*mat ;
       return trans.is_zero() ;
    }
    return false ;
}
template <typename DataType>

bool matrix<DataType>:: is_parallel(const matrix&mat)const {
    return  abs(theta(mat))<=tolerance||abs(theta(mat)-180)<=tolerance ;
}
template <typename DataType>

bool matrix<DataType>::operator == (const matrix&mat)const{
    if(same_shape(mat)){
       for (int i = 0; i < rows; i++){
            for (int j = 0; j <cols; j++) {
             if(abs(at(i,j)-mat.at(i,j))>tolerance){
                return false ;
            }
        }
    }
        return true ;
    }
    return false ;
}
//helper function
template <typename DataType>
void matrix<DataType>::row_axpy(DataType scalar,int upper_row,int lower_row){
    for(int col_counter =0 ; col_counter<get_cols();col_counter++){
        at(lower_row,col_counter)+= at(upper_row,col_counter)*scalar;
    }
}
//performs downward gaussian elimination producing an upper triangular matrix
//optional if you want to know the indices of the pivots for each row
//pass in a matrix<DataType>aka pivots_indices
template <typename DataType>
matrix<DataType> matrix<DataType>::gauss_down( matrix<int>*pivots_indices,int pivots_locations) const {
    matrix<DataType>ret_mat = *this;
    if(pivots_indices){
        if(pivots_locations==new_locations){
            *pivots_indices = matrix<int>(rows,1,-1) ;
        }
        else{
            //here it will be permutaions matrix
            //to record each row exchange happening
            *pivots_indices = matrix<int>(rows,1);
            for(int i= 0 ; i<pivots_indices->get_rows();i++){
                pivots_indices->at(i,0) = i;
            }
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
                        pivots_indices->at(up_r,0) = pivot_index ;
                    }
                //else user wants the locations of pivots lying in original rows
                else if(pivots_locations==old_locations){
                    pivots_indices->switch_rows(up_r,pivot_condition) ;
                }
            }
            for(int low_r = up_r+1; low_r<rows; low_r++){
                //do gaussian elimination downward
                //check if lower element is not zero to save processing power
                if(abs(ret_mat.at(low_r,pivot_index))>tolerance){
                    DataType c = (ret_mat.at(low_r,pivot_index)/ret_mat.at(up_r,pivot_index))*-1;
                    for(int i =pivot_index ; i<cols;i++){
                        ret_mat.at(low_r,i)+=c*ret_mat.at(up_r,i) ;
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
//pass in a matrix<DataType>aka pivots_indices
template <typename DataType>
matrix<DataType> matrix<DataType>::gauss_up( matrix<int>*pivots_indices)const {
    matrix<DataType>ret_mat = *this ;
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
               pivots_indices->at(low_r,0) = pivot_index ;
           }
        for(int up_r = low_r-1;up_r>=0;up_r--){
            if(abs(ret_mat.at(up_r,pivot_index))>tolerance){
                DataType c =(ret_mat.at(up_r,pivot_index)/ret_mat.at(low_r,pivot_index))*-1  ;
                    for(int col_c = pivot_index ; col_c>=0; col_c--){
                        ret_mat.at(up_r,col_c)+= c*ret_mat.at(low_r,col_c);

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
template <typename DataType>
bool matrix<DataType>::switch_rows(int r1 ,int r2 ){
    if(r1>=0&&r1<get_rows()&&r2>=0&&r2<get_rows()&&r1!=r2){
    for(int i = 0 ; i <get_cols();i++){
        swap(at(r1,i),at(r2,i));
    }
    return true ;
}
return false  ;
}
//performs back substitution on lower triangular invertible matrix
template <typename DataType>
DataType matrix<DataType>:: back_sub(int row_index,const matrix&sol_mat)const {
    DataType sum  = at(row_index,get_cols()-1);
    for(int col_counter = row_index+1  ;col_counter<get_cols()-1; col_counter++){
        sum-=at(row_index,col_counter)*sol_mat.at(col_counter,0);
    }
    return sum/at(row_index,row_index) ;
}
//performs forward substitution on lower triangular invertible matrix
template <typename DataType>
DataType matrix<DataType>:: fwd_sub(int row_index,const matrix&sol_mat)const {
    DataType sum  = at(row_index,get_cols()-1);
    for(int col_counter = 0  ;col_counter<row_index;col_counter++){
        sum-=at(row_index,col_counter)*sol_mat.at(col_counter,0);
    }
    return sum/at(row_index,row_index) ;
}

//pass an appended matrix
template <typename DataType>
matrix<DataType> matrix<DataType>:: solve(void) const {
    matrix<int>pivots_indices;
    //turns the system into uppertriangular system
    matrix<DataType>mat_cpy=gauss_down(&pivots_indices,new_locations);
    //check for number of pivots first
    for(int i = 0 ; i<rows;i++){
        if(pivots_indices.at(i,0)==-1){
            cout<<"Number of pivots is insufficient default garbage value is -1" ;
            matrix<DataType>ret_mat = matrix(1,1,-1);
            return ret_mat ;
        }
    }
    //the new matrix<DataType>in which the answer will be returned
    matrix<DataType>sol_mat(get_rows(),1,0) ;
    for(int row_c = get_rows()-1; row_c>=0;row_c--){
        sol_mat.at(row_c,0) = mat_cpy.back_sub(row_c,sol_mat) ;
    }
    return sol_mat ;
}
//calculate determinant of a matrix
template <typename DataType>
DataType matrix<DataType>::det()const {
//determinant is for square matrices
    if(is_square()){
        //here we store place of original pivots
        //we walk through the matrix<DataType>from 0 to row -1
        //if you are at first row and the pivot location is originally
        //in the 3rd row then we multiply the determinant by -1
        //if there is no pivot we return 0 easy as that
        matrix<int>original_pivots_indices ;
        matrix<DataType>mat_cpy =gauss_down(&original_pivots_indices,old_locations) ;
        DataType det_val = 1 ;
        unsigned int sign_change = 0   ;
        for(int i= 0  ; i<rows;i++){
            if(original_pivots_indices.at(i,0)!=i){
                sign_change++;
            }
            det_val*=mat_cpy.at(i,i) ;
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
template <typename DataType>
DataType& matrix<DataType>::at(int r_ind,int c_ind){
    if(r_ind>=0&&r_ind<rows&&c_ind>=0&&c_ind<cols){
        return vec[r_ind*cols+c_ind] ;
    }
    cout<<"out of bounds";
}
//access and modify an element at a certain position
template <typename DataType>
DataType& matrix<DataType>::at(int r_ind,int c_ind)const{
    if(r_ind>=0&&r_ind<rows&&c_ind>=0&&c_ind<cols){
        return vec[r_ind*cols+c_ind] ;
    }
    cout<<"out of bounds";
}
//calculates inverse of a square matrix<DataType>if available
template <typename DataType>
matrix<DataType> matrix<DataType>::inverse(void)const {
    if(is_square()){
        //copying the m matrix<DataType>into mat_cpy
        matrix<DataType>mat_cpy =*this ;
        //creating return matrix<DataType>which at first will be identity
        matrix<DataType>ret_mat(rows,cols) ;
        ret_mat.identity() ;
        //first do Gaussian elimination downward
        for(int up_r = 0 ; up_r<rows-1;up_r++){
                for(int low_r = up_r+1;low_r<rows;low_r++){
                    if(mat_cpy.is_pivot(up_r,up_r)!=-1){
                        DataType c =(mat_cpy.at(low_r,up_r)/mat_cpy.at(up_r,up_r)) *-1  ;
                        for(int col_c = 0 ; col_c<cols ; col_c++){
                            mat_cpy.at(low_r,col_c)+= c*mat_cpy.at(up_r,col_c) ;
                            ret_mat.at(low_r,col_c) += c*ret_mat.at(up_r,col_c);
                        }
                    }
                    else{
                        //if the pivot is zero then its not invertible matrix
                        cout<<"determinant of the passed matrix<DataType>is zero or not squre matrix<DataType>to begin with";
                        matrix<DataType>error_matrix(1,1,-1);
                        return error_matrix;
                    }
                }
            }
        //then do Gaussian elimination upward
            //here we don't need to check if its a pivot since its shown clearly
            //from first elemination that it contains pivots at each row
            for(int low_r = rows-1 ; low_r>0;low_r--){
                for(int up_r = low_r-1;up_r>=0;up_r--){
                    DataType c = (mat_cpy.at(up_r,low_r) /mat_cpy.at(low_r,low_r))*-1  ;
                    for(int col_c = 0 ; col_c<cols ; col_c++){
                        mat_cpy.at(up_r,col_c)+= c*mat_cpy.at(low_r,col_c);
                        ret_mat.at(up_r,col_c)+= c*ret_mat.at(low_r,col_c);
                    }
                }
            }
            for(int i= 0 ; i<rows;i++){
                for(int j= 0 ; j<cols ; j++){
                    ret_mat.at(i,j) /=mat_cpy.at(i,i) ;
                }
            }
            return ret_mat ;
}
cout<<"determinant of the passed matrix<DataType>is zero or not a squre matrix<DataType>to begin with";
    matrix<DataType> error_matrix(1,1,-1);
    return error_matrix;
}
//calculates A/B where A is left side and B is right
template <typename DataType>
matrix<DataType> matrix<DataType>::operator/(const matrix& m)const
{
        matrix<DataType>ret_mat = m.inverse() ;
        if(ret_mat.rows<rows)
        {
        cout<<"determinant of the denum is zero";
        matrix<DataType> error_matrix(1,1,-1);
        return error_matrix;
        }
        return *this * ret_mat;
}
//this allows for multiple functions reuse old matrices , copy
template <typename DataType>
void matrix<DataType>::operator=(const matrix<DataType>&mat){
    if(this!=&mat){
        //then check if they don't have same shape
        if(rows*cols<mat.rows*mat.cols){
            //delete[] old memeory
            if(vec!=NULL){
                delete[]vec ;
            }
            vec= NULL  ;
            //reallocate for copying
            rows = mat.rows;
            cols = mat.cols ;
            vec= get_vec(mat.get_rows(),mat.get_cols()) ;
        }
        else{
            rows=mat.rows;
            cols = mat.cols;
        }
        //copying mechanism
        for(int i = 0 ; i <rows;i++){
            for(int j= 0 ; j<cols ;j++){
            if(abs(mat.at(i,j))>tolerance){
                at(i,j) = mat.at(i,j) ;
            }
            else{
                at(i,j) = 0  ;
            }
        }
        }

    }
}
// Check if this matrix<DataType>is idempotent
template <typename DataType>
bool matrix<DataType>:: is_idempotent(void)const {
    matrix<DataType>mat = (*this)*(*this) ;
    return mat == *this ;
}
//tested
// Check if this matrix<DataType>is identity
template <typename DataType>
bool matrix<DataType>:: is_identity(void)const {
        if(is_square()){
    for(int i = 0 ; i<rows;i++){
        for(int j= 0 ; j<cols; j++){
            if(i==j){
                if(abs(at(i,j)-1)>tolerance) {
                    return false ;
                }
            }
            else{
                if(abs(at(i,j))>tolerance){
                    return false ;
                }
            }
    }
}
return true ;
}
return false ;
}//tested
    // Check if this matrix<DataType>is the zero matrix
template <typename DataType>
bool matrix<DataType>::is_zero(void)const {
    for(int i = 0; i<rows;i++){
        for(int j= 0 ;j<cols ;j++){
            if(abs(at(i,j))>tolerance){
                return false ;
            }
        }
    }
    return true ;
}
template <typename DataType>

bool matrix<DataType>::is_upper_tri(void)const  {
    if(is_square()){
     bool zero_flag= true ;
        for(int i =0 ; i <rows;i++){
            for(int j=  0 ; j<cols; j++){
                if(j<i){
                    if(abs(at(i,j))<tolerance){
                        return false ;
                    }
                }
                else{
                    //check for rest of elements so that they aren't all zeroes
                    zero_flag&=(abs(at(i,j))<tolerance)?false:true ;
                }
            }
        }
        if(zero_flag!=true){
            return true ;
        }
    }
    return false ;
}
template <typename DataType>

bool matrix<DataType>::is_lower_tri()const {
if(is_square()){
 bool zero_flag= true ;
    for(int i =0 ; i <rows;i++){
        for(int j=  0 ; j<cols; j++){
            if(j>i){
                if(abs(at(i,j))<tolerance){
                    return false ;
                }
            }
            else{
                //check for rest of elements so that they aren't all zeroes
                zero_flag&=(abs(at(i,j))<tolerance)?false:true ;
            }
        }
    }
    if(zero_flag!=true){
        return true ;
    }
}
return false ;
}
// Check if this matrix<DataType>is scalar
template <typename DataType>
bool matrix<DataType>:: is_scalar(void)const {//tested
    if(is_square()){
        int val = at(0,0) ;
        for(int i=  0 ; i<rows; i++){
            for(int j= 0  ;j<cols ; j++){
                if(i==j){
                    if(abs(at(i,j)-val)>tolerance){
                        return false ;
                    }
                }
                else{
                    if(abs(at(i,j))>tolerance){
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
template <typename DataType>
int matrix<DataType>::rank(void)const {//tested
    matrix<int>pivots_indices ;
    //first perform gaussian elimination downward
        gauss_down(&pivots_indices) ;
        int counter = 0;
        //then count number of pivots
        for(int i = 0 ;i<rows ; i++){
            if(pivots_indices.at(i,0)!=-1){
                counter ++ ;
            }
            else{
                break  ;
            }
        }
        return counter ;
}//tested

// Check if this matrix<DataType>is skew-symmetric
template <typename DataType>
bool matrix<DataType>::is_skew_symmetric(void)const {
    if(vec&&is_square()){
        for(int i = 0 ; i <rows;i++){
            for(int j=i+1;j<cols;j++){
                if(abs(at(i,j)-at(j,i))>tolerance){
                    return false ;
            }
        }

    }
    return true ;
    }
    return false ;

}

// Check if this matrix<DataType>is nilpotent
template <typename DataType>
bool matrix<DataType>:: is_nilpotent(void)const {
    if(is_square()){
        //keep multiplying the matrix<DataType>by itself untill the nth power
        matrix<DataType>mat_pow = *this ;
        matrix<DataType>zeroes(rows,cols,0) ;
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
// Check if this matrix<DataType>is involutory
template <typename DataType>
bool matrix<DataType>:: is_involutory(void)const {
    if(is_square()){
        matrix<DataType>temp =(*this)*(*this)  ;
        return temp.is_identity();
    }
    cout<<square_error ;
    return false ;
}
//added permutation matrix<DataType>since during lu factorization if the rows are switched
//if the pivot is not in its position it will be switched we have to keep track of this
//using permutation matrix<DataType>its set first as identity but if rows are switched
//the rows of the identity are switched aswell
template <typename DataType>
void matrix<DataType>:: lu_fact(matrix&lower_fact,matrix&permutation,matrix&upper_fact) const {
    //first check if its square matrix
    if(is_square()){
        //the lower_fact matrix<DataType>is the identity matrix<DataType>(at first) in which we store
        // the constants during the gaussian elimination of the original matrix
        //after finisning the gaussian elimination the upper_fact is finished
        lower_fact = matrix(rows,cols,0);
        lower_fact.identity() ;
        //if permutations happen its recorded in this matrix
        permutation = matrix(rows,cols,0);
        permutation.identity() ;
        //copy original matrix<DataType>into upper_fact to performa gaussian elimination on it
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
                    DataType c = -1*(upper_fact.at(low_r,up_r)/upper_fact.at(up_r,up_r));
                    //first record it into the lower_fact matrix<DataType>at its position
                    lower_fact.at(low_r,up_r)  = -1* c ;
                    for(int i =0 ; i<cols;i++){
                        //then continue the gaussian elimination
                        upper_fact.at(low_r,i)+=c*upper_fact.at(up_r,i) ;
                    }
                }
 }
                else{
                cout<<"matrix<DataType>doesn't have an inverese" ;
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
template <typename DataType>
int matrix<DataType>:: is_pivot(int r_ind , int c_ind) {
    if(r_ind<rows&&c_ind<cols){
        //find first non zero element in that row
        int pivot_index = r_ind ;
        while(pivot_index<rows){
            if(abs(at(pivot_index,c_ind))>tolerance){
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
template <typename DataType>
int matrix<DataType>:: is_pivot_up(int r_ind , int c_ind) {
    if(r_ind<rows&&c_ind<cols){
        //find first non zero element in that row
        int pivot_index = r_ind ;
        while(pivot_index>0){
            if(abs(at(pivot_index,c_ind))>tolerance){
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
    //and saves pivots locations in the input pivots matrix<DataType>for each row containing
    //a pivot it saves that pivot location in that row index
    template <typename DataType>
    matrix<DataType> matrix<DataType>:: rref(matrix<int>*pivots_indices)const {
        //pivots locations will be mapped in this array
        //so if row zero contains a pivot at col index 1  for ex and so on
        //it will have the value 1 in that row and so on
        //return matrix
        //do gaussian elemination downward
        matrix<int>pivots_locations;
        matrix<DataType>ret_mat = gauss_down(&pivots_locations);
        //do gaussian elimination upward using the pivots_locations
        for(int low_r = rows-1 ; low_r>0;low_r--){
            int pivot_index = pivots_locations.at(low_r,0);
            if(pivot_index!=-1){
                for(int up_r = low_r-1;up_r>=0;up_r--){
                    DataType c =(ret_mat.at(up_r,pivot_index) /ret_mat.at(low_r,pivot_index)) *-1  ;
                    for(int col_c = 0 ; col_c<cols ; col_c++){
                        ret_mat.at(up_r,col_c)+= c*ret_mat.at(low_r,col_c);
                }
            }
       }
    }
        //go in each row and if that row contains a pivot divid each element by
        //by the pivot
        for(int i = 0 ; i<rows;i++){
            int pivot_index = pivots_locations.at(i,0);
            if(pivot_index!=-1){
                DataType val = ret_mat.at(i,pivot_index);
                if(abs(val)>tolerance){
                    for(int j=  0 ; j<cols;j++){
                        ret_mat.at(i,j)/=val ;
                        //tolerance
                        ret_mat.at(i,j) = (abs(ret_mat.at(i,j))<tolerance)?0:ret_mat.at(i,j);
                    }
                }
            }
            else{
                //no more pivots
                break ;
            }
        }
        if(pivots_indices){
            *pivots_indices = pivots_locations ;
        }
        return ret_mat ;
    }
    //checks if a set of vectors in a column space are independent
    template <typename DataType>
    bool matrix<DataType>::is_independent(void)const {
        return rank() ==cols ;
    }
    template <typename DataType>
    // Calculates the dimension of the column space (range) of the matrix.
    // The column space consists of all possible linear combinations of the column vectors in the matrix.
    int matrix<DataType>::dim(void)const {
        return rank() ;
    }//tested
    //returns dimension of the null space of column space
    template <typename DataType>
    int matrix<DataType>::dim_null_cols(void)const {
        return cols - rank();
    }
    //returns dimension of the null space of row space
    template <typename DataType>
    int matrix<DataType>::dim_null_rows(void)const {
        return rows - rank() ;
    }
    //checks if a bunch of vectors form basis of a space R^dimension
    template <typename DataType>
    bool matrix<DataType>::is_basis( int dimension)const {
        //check if they are independent and they span the column space of R^dimension
        return cols==dimension&&is_independent() ;
    }
    //returns the set of vectors that forms a basis of the column space
    template <typename DataType>
    matrix<DataType> matrix<DataType>::basis_cols(void) const {
        //return matrix
        matrix<DataType>ret_mat ;
        //matrix<DataType>in which we store indicex of each pivot in the correspoinding row
        matrix<int>pivots_indices ;
        //perform gaussian elimination downward
        gauss_down(&pivots_indices) ;
        //get dimension of the column space
        int pivot_count = 0 ;
        //count number of pivots and stop when you find -1
        //aka no remaining pivots refer to is_pivot and check what it does for
        //more info
        for(int i = 0 ;i<rows; i++){
            if(pivots_indices.at(i,0)!=-1){
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
                    int pivot_index=pivots_indices.at(col_c,0) ;
                    //store the correspoinding element in the pivot's column
                    //in ret_mat
                    ret_mat.at(row_c,col_c) =at(row_c,pivot_index) ;
                }
            }
        return ret_mat ;
    }
    // Returns a set of vectors (as a matrix) that forms a basis for the vector space of the given dimension.
    template <typename DataType>
    matrix<DataType> matrix<DataType>:: basis_rows(void)const {
        matrix<DataType>ret_mat ;
        matrix<int>pivots_indices(rows,1,-1);
            //perform gaussian elimination downward
        matrix<DataType>mat_rref = rref(&pivots_indices) ;
        //get dimension of the column space
        int pivot_count = 0 ;
        //count number of pivots and stop when you find -1
        //aka no remaining pivots refer to is_pivot and check what it does for
        //more info
        for(int i = 0 ;i<rows; i++){
            if(pivots_indices.at(i,0)!=-1){
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
                ret_mat.at(i,j)  = abs(mat_rref.at(i,j))>tolerance?mat_rref.at(i,j):0;
            }
        }
        return ret_mat ;
    }

    //where e*A = rref(A)
    //matrix<DataType>e is optional if you want to use it if you pass a matrix<DataType>as an input
    //this matrix<DataType>returns the null space of row space
    template <typename DataType>
    matrix<DataType> matrix<DataType>:: null_rows(matrix*e) const {
        //pivots indices are stored here
        matrix<int>pivots_indices(rows,1,-1) ;
        matrix<DataType>elementary=matrix(rows,rows);
        elementary.identity() ;
        matrix<DataType>mat_cpy = *this ;
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
                pivots_indices.at(up_r,0) = pivot_index ;
                for(int low_r = up_r+1; low_r<rows; low_r++){
                    //do gaussian elimination downward
                    //check if lower element is not zero to save processing power
                    if(abs(mat_cpy.at(low_r,pivot_index))>tolerance){
                        DataType c = -1*(mat_cpy.at(low_r,pivot_index)/mat_cpy.at(up_r,pivot_index));
                        for(int i =pivot_index ; i<cols;i++){
                            mat_cpy.at(low_r,i)+=c*mat_cpy.at(up_r,i) ;
                        }
                        for(int i =0 ; i<rows;i++){
                            elementary.at(low_r,i) +=c*elementary.at(up_r,i) ;
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
            int pivot_index = pivots_indices.at(low_r,0);
            if(pivot_index!=-1){
                for(int up_r = low_r-1;up_r>=0;up_r--){
                    DataType c = -1 * (mat_cpy.at(up_r,pivot_index) /mat_cpy.at(low_r,pivot_index));
                    for(int col_c = 0 ; col_c<cols ; col_c++){
                        mat_cpy.at(up_r,col_c)+=c*mat_cpy.at(low_r,col_c) ;
                    }
                    for(int col_c = 0 ; col_c<rows ; col_c++){
                        elementary.at(up_r,col_c)+= c*elementary.at(low_r,col_c);
                    }
            }
       }
    }
        //go in each row and if that row contains a pivot divide each element by
        //by the pivot
        int pivot_c = 0 ;
        for(; pivot_c<rows;pivot_c++){
            int pivot_index = pivots_indices.at(pivot_c,0);
            //if the following row contains a pivot then we divide the whole row by that pivot
            if(pivot_index!=-1){
                DataType val = mat_cpy.at(pivot_c,pivot_index);
                if(val){
                    //do that for each element in the row
                    for(int j=  0 ; j<rows;j++){
                        elementary.at(pivot_c,j)/=val ;
                        //tolerance
                        elementary.at(pivot_c,j) = (abs(elementary.at(pivot_c,j))<tolerance)?0:elementary.at(pivot_c,j);
                    }
                }
            }
            //if there is no more pivots then break and head for null space of row space matrix
            else{
                break ;
            }
        }
        //make sure the matrix<DataType>has dimension in the null space of the row space
        matrix<DataType>ret_mat;
        if(rows-pivot_c>0){
        ret_mat=matrix(rows-pivot_c,rows);
        int c= 0  ;//counter for rows of return matrix
        for(; pivot_c<rows;pivot_c++){
            for(int j = 0 ; j<rows; j++){
                ret_mat.at(c,j) = elementary.at(pivot_c,j) ;
            }
            c++;
        }
    }
    else{
         ret_mat= matrix(1,rows,0);
    }
    if(e){
            //if the user wants the elementary matrix<DataType>then do the copying into e
            *e= elementary ;
        }
    return ret_mat ;
    }
    template <typename DataType>
    matrix<DataType> matrix<DataType>::null_cols(void)const  {
        //here the pivots indices are stored along with indices of free variables
        matrix<int>pivots_indices =matrix<int>(cols,1,-1);
        //here the pivots indices are stored
        matrix<int>p_cpy ;
        matrix<DataType>mat_rref = rref(&p_cpy) ;
        //solution matrix<DataType>with all speacial solutions
        matrix<DataType>ret_mat;
        //copy the content from p_cpu into pivots indices
        int c=  cols<rows?cols:rows ;
        for(int i = 0 ; i<c;i++){
            pivots_indices.at(i,0) = p_cpy.at(i,0)  ;
        }
        //counting number of pivots to check if there are special solutions
        int pivot_c  =0   ;
        while(pivot_c<cols&&pivots_indices.at(pivot_c,0)!=-1){
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
                    if(i==pivots_indices.at(j,0)){
                        flag=true ;
                        break;
                    }
                }
                if(!flag){
                    //if its not a pivot put it
                    pivots_indices.at(pivot_c+counter,0) =i ;
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
            for(int i =0;i<(cols-pivot_c);i++){
                int one_pos = pivots_indices.at(cols-i-1,0) ;
                //put the one in its postion for the new special solution
                ret_mat.at(one_pos,i) =1 ;
                //for the current pivot we are calculating the value for
                //"index of the pivot in special solution matrix"
                for(int curr_piv= pivot_c-1 ; curr_piv>=0; curr_piv--){
                    //x1 = (-x3*2-x2*2)/3
                    //x0 = (-x3*2-x2*2-x1*3)/4
                    int pivot_index = pivots_indices.at(curr_piv,0);
                    for(int j= cols-1  ; j>curr_piv;j--){
                        int free_v_index= pivots_indices.at(j,0);
                        ret_mat.at(pivot_index,i)
                        -=mat_rref.at(curr_piv,free_v_index)*ret_mat.at(free_v_index,i);
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
    //it fixes a matrix<DataType>by putting rows that corresponds to pivots first
    //then rist of rows at th every end this fixes an issue at rref
    //where if a row switch occurs it won't be recorded in elementary matrix
    //or you will need extra permutation matrix<DataType>fixes the caller itself
    template <typename DataType>
    void matrix<DataType>::fix_pivots(void) {
        matrix<int> original_pivots_indices ;
        gauss_down(&original_pivots_indices,old_locations) ;
        //if i switched already don't do it again
        //i switched 2 with 1 then don't switch 1 with 2 again
        /*
        1
        0
        2
        */
        bool switch_rec[rows] ={0} ;
        for(int i= 0 ; i<rows;i++){
            if(original_pivots_indices.at(i,0)!=i&&!switch_rec[original_pivots_indices.at(i,0)]){
                //switch happened
                switch_rows(i,original_pivots_indices.at(i,0));
                switch_rec[i] =1;
            }
        }
    }
    template <typename DataType>
    matrix<DataType> matrix<DataType>::projection(void)const {
    /*
        Ax=b has no solution
        AT*A x* =AT*b
        x* = (AT*A )^-1 *AT b
        p = Ax* so P = A*(AT*A)^-1 * AT *b
        so projection matrix<DataType>where p =projection b
        projection = A*(AT*A)^-1 *AT
    */
        matrix<DataType>Atrans  = transpose() ;
        matrix<DataType>AtransA= Atrans *(*this) ;
        //get inverse
        AtransA = AtransA.inverse() ;
        //projection matrix<DataType>for a system A
        //p  = A (AT A)^-1 AT
        return *this *AtransA* Atrans ;
    }
    //fit a data set into a linear system
    //Ax=b can't be solved
    //AT*A* x* = AT*b
    //now solvable
    template <typename DataType>
    matrix<DataType> matrix<DataType>::fit_least_squares(const matrix<DataType>&data_set) const {
        if(rows==data_set.rows){
            matrix<DataType>Atrans = transpose() ;
            //AT *A
            matrix<DataType>ret_mat = Atrans*(*this);
            //append and solve [AT*A|AT*b]
            Atrans= Atrans*data_set;
            ret_mat = ret_mat.append_cols(Atrans) ;
            return ret_mat.solve();
        }
        cout<<"the system's rows don't match rows of the data set default garbage value is -1";
        matrix<DataType> err_mat(1,1,-1);
        return err_mat ;
    }
    template <typename DataType>
    matrix<DataType> matrix<DataType>::extract_col(int index)const {
        matrix<DataType>ret_mat ;
        if(index>=0&&index<cols){
            ret_mat= matrix<DataType>(rows,1);
            for(int i =0;i<rows;i++){
                ret_mat.at(i,0) = at(i,index) ;
            }
        }
        else{
            ret_mat = matrix<DataType>(1,1,-1) ;
            cout<<"out of bounds default garbage value is -1";
        }
        return ret_mat  ;
    }
    //this function takes a bunch of vectors in a matrix<DataType>and returns
    //the orthonormal vectors in a form of matrix<DataType>(performs gram-shmidt algorithm)
    template <typename DataType>
    matrix<DataType> matrix<DataType>::gram_shmidt(void)const {
        //array of projections for each vector from 0 to n-1
        //no need for the nth
        matrix<DataType>projections_arr[cols-1];
        //here we store each orthonormal vector
        matrix<DataType>ret_mat(rows,cols);
        //temporary storage for the resultant vector
        matrix<DataType>res ;
        //here we store projection[i]*vec
        matrix<DataType>p;

        matrix<DataType>temp ;
        //length of a vector variable
        DataType len = 0;
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
                ret_mat.at(row_c,vec_c) =res.at(row_c,0)/len;
            }
            //get the projection of the newly created vector
            if(vec_c<cols-1){
                projections_arr[vec_c] = res.projection();
            }
        }
        return ret_mat ;
    }
    //performs A -lambda * I
    //where I is the identity
    //then returns the solution
    template <typename DataType>
    matrix<DataType> matrix<DataType>::SubLambdaI(DataType lambda)const {
        matrix<DataType>ret_mat =*this ;
        for(int i = 0 ;i<rows;i++){
            ret_mat.at(i,i)-=lambda ;
        }
        return ret_mat ;
    }
    //returns eigen vectors of a system using eigen values
    //calculate null space for each A-lambda *I
    //and append it to eigen vectors matrix
    template <typename DataType>
    matrix<DataType> matrix<DataType>::eigen_vectors(const matrix&eigen_values)const {
        matrix<DataType>ret_mat =SubLambdaI(eigen_values.at(0,0)).null_cols() ;
        for(int i = 1;i<rows;i++){
           ret_mat= ret_mat.append_cols(SubLambdaI(eigen_values.at(i,0)).null_cols());
        }
        return ret_mat ;
    }
    //returns cofactor of an element at position row_i,col_i
    template <typename DataType>
    DataType matrix<DataType>::cofactor(int row_i, int col_i)const {
        if(is_square()&&row_i>=0&&row_i<rows&&col_i>=0&&col_i<cols){
            matrix<DataType>temp(rows-1,cols-1);
            int tr=0,tc= 0;//counters for temp matrix

            for(int i = 0 ; i<rows;i++){
                tc=0;
                //don't include the row where we want to get its cofacotr
                if(i!=row_i){
                    for(int j= 0 ; j<cols; j++){
                        //same for col
                        if(j!=col_i){
                            temp.at(tr,tc)=at(i,j);
                            tc++;
                        }
                    }
                tr++;
            }
        }
            //if row_i+col_i is even then its a positive cofactor
            //else its negative cofactor
            return temp.det()*pow(-1,(row_i+col_i)) ;
        }
        cout<<"invalid index default garbage value is -1";
        return -1;
    }
    //returns matrix<DataType>of cofactors of all elements of the matrix
    template <typename DataType>
    matrix<DataType> matrix<DataType>:: cofactors(void)const {
        if(is_square()){
            matrix<DataType>ret_mat(rows,cols) ;
            for(int i= 0  ; i<rows;i++){
                for(int j=  0 ;j<cols;j++){
                    //get cofactor of each element
                    ret_mat.at(i,j) =cofactor(i,j);
                }
            }
            return ret_mat  ;
        }
        cout<<square_error;
        matrix<DataType>err_mat(1,1,-1) ;
        return err_mat ;
    }
    template <typename DataType>
    matrix<DataType> matrix<DataType> ::arrange(const matrix<int>&seq){
        matrix<DataType> ret_mat;
        if(rows==seq.rows){
            ret_mat = matrix<DataType>(rows,cols);
            for(int i =0 ; i<rows;i++){
                int row_ind  = seq.at(i,0) ;
                for(int j = 0; j<cols;j++){
                    ret_mat.at(i,j) = at(row_ind,j);
                }
            }
        }
        else{
            cout<<"sequence must be same size as matrix size \naka rows of sequence equal rows of caller";
            cout<<"\ndenied\n";
            ret_mat = matrix<DataType>(1,1,-1) ;
        }
        return ret_mat ;
    }
    template <typename DataType>
    void matrix<DataType>:: at_quarter(int quarter,const matrix<DataType>&src){
        if(quarter>=0&&quarter<4){
            if(src.rows<=rows/2&&src.cols<=cols/2){
                int row_offset,col_offset ;
                switch(quarter){
                    case upper_left:{row_offset=0;col_offset=0;}break;
                    case lower_left:{row_offset=rows/2;col_offset=0;}break;
                    case upper_right:{row_offset=0;col_offset=cols/2;}break;
                    case lower_right:{row_offset=rows/2;col_offset=cols/2;}break;
                }
                for(int i = 0 ; i<src.rows;i++){
                    for(int j= 0 ; j<src.cols;j++){
                        at(row_offset+i,j+col_offset) = src.at(i,j) ;
                    }
                }
            }
        }
        else{
            cout<<"\ndenied\n";
        }
    }

    //returns a square matrix representing forier transform
    matrix<complex> forier_mat(int dimension){
        if(dimension>0){
            complex w(cos(to_rad*(360/dimension)),sin(to_rad*(360/dimension)));
            matrix<complex> ret_mat(dimension,dimension);
            for(int i=0  ; i<dimension;i++){
                for(int j= i ; j<dimension;j++){
                   complex temp =  w^(i*j) ;
                   ret_mat.at(i,j) =temp;
                   ret_mat.at(j,i) =temp;
                }
            }
            return ret_mat ;
        }
        cout<<"can't have 0 or -ve dimensions default garbage value is -1";
        matrix<complex> err_mat(1,1,-1) ;
        return err_mat;
    }
    matrix<complex> forier_diagonal(int dimension){
        if(dimension>0){
            complex w(cos(to_rad*(360/dimension)),sin(to_rad*(360/dimension)));
            matrix <complex>ret_mat(dimension,1) ;
            for(int i = 0 ; i<dimension;i++){
                ret_mat.at(i,0) =w^(i*i) ;
            }
            return ret_mat ;
        }
        matrix<complex> err_mat(1,1,-1);
        cout<<"invalid dimension default garbage value is -1";
        return err_mat;
    }

#include <chrono>

int main() {
    auto start = chrono::high_resolution_clock::now();

    matrix<complex> f1  = forier_mat(10000);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;

    cout << "Time taken : " << diff.count() << " s\n";

    return 0;
}
