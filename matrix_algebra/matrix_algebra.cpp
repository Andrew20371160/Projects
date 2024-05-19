#include "matrix_algebra.h"

/*bool operator>(const complex& a, const complex& b) {
    return std::norm(a) > std::norm(b);
}

bool operator<(const complex& a, const complex& b) {
    return std::norm(a) < std::norm(b);
}

bool operator>=(const complex& a, const complex& b) {
    return std::norm(a) >= std::norm(b);
}

bool operator<=(const complex& a, const complex& b) {
    return std::norm(a) <= std::norm(b);
}

bool operator==(const complex& a, const complex& b) {
    return a.real() == b.real() && a.imag() == b.imag();
}

bool operator!=(const complex& a, const complex& b) {
    return !(a == b);
}
*/

//this assigns the matrix_type variable and sets the at_ptr ,at_ptr_c
template<typename DataType>
void matrix<DataType>::set_feature(int  matrix_t){
    if(matrix_t>=general&&matrix_t<=orthonormal){
        matrix_type= matrix_t;
        set_at_ptr(matrix_t) ;
    }
}
//helper function for copying
template<typename DataType>
void copy_vec(DataType*& dest, const DataType* src, int  size) {
    if(src) {
        if(!dest) {
            dest = get_vec<DataType>(size, 1);
        }
        else {
            delete[] dest;
            dest = get_vec<DataType>(size, 1);
        }
        for(int  i = 0; i < size; i++) {
            dest[i] = src[i];
        }
    }
}
//helper function for filling vectors like pindex and row_start
template<typename DataType>
void fill_vec(DataType*vec,int  size, DataType val){
    if(vec){
        for(int  i = 0 ; i<size;i++){
            vec[i]=val;
        }
    }
}


template<typename DataType>
DataType*get_vec(int  r ,int  c){
    //check for passed parameters
    if(r>0&&c>0){
        //memory allocation
        DataType*ret_vec =new DataType[r*c];
        return ret_vec ;
    }
    return NULL ;
}



template<typename DataType>
matrix<DataType>::matrix(){
        rows = 0;
        cols = 0 ;
        acutal_size =0;
        vec= NULL ;
        row_start= NULL ;
        pindex=NULL ;
        empty_vec[0]=0;
        is_compressed = false;
        set_feature(general);
    }

//initialize a matrix with one value compressed or not
//by default its not compressed
template<typename DataType>
matrix<DataType>::matrix(int  r,int  c,DataType value,bool compressed){
        rows= r;
        cols= c;
        pindex=NULL ;
        row_start=NULL ;
        empty_vec[0] = 0;
        if(compressed){
            //first dimensions
            vec =  get_vec<DataType>(1,1) ;
            acutal_size= 1;
            if(value!=DataType(no_init)){
                vec[0] =value;
            }
            is_compressed=true;
            set_feature(constant) ;
        }
        else{
            is_compressed =false;
            set_feature(general) ;
            vec=get_vec<DataType>(r,c) ;
            acutal_size = r*c;
            if(value!=DataType(no_init)){
                for(int  i =0 ;i<rows; i++){
                    for(int  j= 0 ;j<cols ;j++){
                        at(i,j) = value;

                    }
                }
            }

        }
}

template <typename DataType>
matrix<DataType>::~matrix(){
    delete[] vec ;
    vec = NULL;
    if(row_start){
        delete[]row_start ;
        row_start=NULL;
    }
    if(pindex){
        delete[]pindex;
        pindex=NULL;
    }

}

template <typename DataType>
matrix<DataType>::matrix(const matrix&mat){
    //setting matrix features
    rows= mat.get_rows();
    cols= mat.get_cols();
    row_start=NULL ;
    pindex=NULL ;
    vec=NULL;
    matrix_type= mat.matrix_type;
    set_at_ptr(mat.matrix_type) ;
    acutal_size=  mat.acutal_size ;
    empty_vec[0] =mat.empty_vec[0];
    is_compressed=mat.is_compressed;
    if(mat.matrix_type ==utri||mat.matrix_type==ltri){
        copy_vec(row_start, mat.row_start, rows);
        copy_vec(pindex, mat.pindex, rows);
    }
    //memory allocation and copy
    vec = get_vec<DataType>(mat.acutal_size,1) ;
    for(int  i =0 ; i <rows; i++){
        for(int  j = 0 ; j<cols ; j++){
                at(i,j) = mat.at(i,j);
            }
        }
}


template <typename DataType>
matrix<DataType>::matrix(int  r,int  c , DataType*arr,int  size){
    if(r>0&&c>0&&size<=r*c){
        rows= r;
        cols= c;
        vec=get_vec<DataType>(r,c) ;
        row_start=NULL ;
        pindex=NULL ;
        acutal_size= r*c;
        matrix_type= general ;
        set_at_ptr(general) ;
        is_compressed= false;
        empty_vec[0] =  0;
            for(int  i =0 ;i<rows; i++){
                for(int  j= 0 ;j<cols ;j++){
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
int  matrix<DataType>::get_rows()const{
    return rows ;
}
template <typename DataType>
int  matrix<DataType>::get_cols()const{
    return cols ;
}

template <typename DataType>
int  matrix<DataType>::get_size()const{
    return acutal_size ;
}

template <typename DataType>
int  matrix<DataType>::get_type()const{
    return matrix_type ;
}

template<typename DataType>
void matrix<DataType>:: set_at_ptr(int  matrix_t){
    switch(matrix_t){
        case symmetric :{
            at_ptr_c  = at_symmetric_c;
            at_ptr= at_symmetric ;
        }break ;
        case diagonal :{
            at_ptr_c  = at_diagonal_c;
            at_ptr= at_diagonal ;
            empty_vec[0]  =0;
        }break ;
        case utri :{
             at_ptr_c= at_utri_c;
             at_ptr= at_utri ;
             empty_vec[0]  =0;
        }break;
        case ltri :{
             at_ptr_c= at_ltri_c;
             at_ptr= at_ltri ;
             empty_vec[0]  =0;
        }break;
        case general :{
            at_ptr_c  = at_general_c;
            at_ptr= at_general ;
        }break ;
        case orthonormal :{
            at_ptr_c  = at_general_c;
            at_ptr= at_general ;
        }break ;
       case anti_symmetric :{
            at_ptr_c  = at_anti_symmetric_c;
            at_ptr= at_anti_symmetric ;
        }break ;
        case iden :{
             at_ptr_c= at_identity_c;
             at_ptr= at_identity ;
             empty_vec[0]  =0;
        }break;
        case constant:{
             at_ptr_c= at_const_c;
             at_ptr= at_const ;
        }break ;
    default:{
            at_ptr_c  = at_general_c;
            at_ptr= at_general ;
        }break;
    }
}



template <typename DataType>
bool matrix<DataType>::is_valid_index(int  row_i,int  col_i)const{
    return (row_i>=0&&row_i<rows&&col_i>=0&&col_i< cols);
}

//declarations of at for each matrix type
//for general matrices
template<typename DataType>
const DataType& matrix<DataType>::at_general_c(int  row_i,int  col_i) const {
        return vec[row_i*cols+col_i] ;
    }

template<typename DataType>
DataType& matrix<DataType>::at_general(int  row_i,int  col_i){
    return vec[row_i*cols+col_i] ;
}

//for upper triangular matrices
template<typename DataType>
 DataType& matrix<DataType>::at_utri(int  row_i,int  col_i)  {
    if(pindex[row_i]!=-1&&(col_i>=pindex[row_i])){
        return vec[row_start[row_i]+(col_i-pindex[row_i])] ;
    }
    else{
        return empty_vec[0];
    }
    }
    //for lower triangular matrices
    template<typename DataType>
    DataType& matrix<DataType>::at_ltri(int  row_i,int  col_i)  {
        //if this row has a pivot and the col index is before or is the pivot
        //then we return data else its a zero
        if(pindex[row_i]!=-1&&col_i<=pindex[row_i]){
            return vec[row_start[row_i]+pindex[row_i]-col_i] ;
            }
        else{
            return empty_vec[0];
        }
    }
//for diagonal matrices
template<typename DataType>
DataType& matrix<DataType>:: at_diagonal(int  row_i,int  col_i)  {
        if(row_i==col_i){
            return vec[row_i];
        }
        else{
            return empty_vec[0] ;
        }
    }

//for identity matrices
template<typename DataType>
DataType& matrix<DataType>::at_identity(int  row_i,int  col_i)  {
    if(row_i==col_i){
        //vec will only contain one element which is one
        //over engineered
        return vec[0];
    }
    else{
        return empty_vec[0] ;
    }
}

template<typename DataType>
DataType& matrix<DataType>::at_const(int  row_i,int  col_i)  {
    return vec[0];
}

template<typename DataType>
DataType& matrix<DataType>::at_symmetric(int  row_i, int  col_i) {
    if(col_i >=row_i) {
        return vec[(row_i * (2*rows - row_i + 1))/2 + col_i - row_i];
    }
    else {
        return vec[(col_i * (2*rows - col_i + 1))/2 + row_i - col_i];
    }
}

template<typename DataType>
const DataType& matrix<DataType>::at_symmetric_c(int  row_i, int  col_i)const{
    if(col_i >=row_i) {
        return vec[(row_i * (2*rows - row_i + 1))/2 + col_i - row_i];
    }
    else {
        return vec[(col_i * (2*rows - col_i + 1))/2 + row_i - col_i];
    }
}

template<typename DataType>
const DataType& matrix<DataType>::at_anti_symmetric_c(int  row_i, int  col_i)const{
    if(col_i >=row_i) {
        return vec[(row_i * (2*rows - row_i + 1))/2 + col_i - row_i];
    }
    else {
        empty_vec[0]= vec[(col_i * (2*rows - col_i + 1))/2 + row_i - col_i]*DataType(-1);
        return empty_vec[0] ;
    }
}
    template<typename DataType>
    DataType& matrix<DataType>::at_anti_symmetric(int  row_i, int  col_i) {
        if(col_i >=row_i) {
            return vec[(row_i * (2*rows - row_i + 1))/2 + col_i - row_i];
        }
        else {
            empty_vec[0]= vec[(col_i * (2*rows - col_i + 1))/2 + row_i - col_i]*DataType(-1);
            return empty_vec[0] ;
        }
    }


//for upper triangular matrices
template<typename DataType>
const DataType& matrix<DataType>:: at_utri_c(int  row_i,int  col_i)  const{
    if(pindex[row_i]!=-1&&(col_i>=pindex[row_i])){
        return vec[row_start[row_i]+(col_i-pindex[row_i])] ;
    }
    else{
        return empty_vec[0];
    }
    }
//for lower triangular matrices
template<typename DataType>
 const DataType& matrix<DataType>:: at_ltri_c(int  row_i,int  col_i)  const {
    //if this row has a pivot and the col index is before or is the pivot
    //then we return data else its a zero
    if(pindex[row_i]!=-1&&col_i<=pindex[row_i]){
        return vec[row_start[row_i]+pindex[row_i]-col_i] ;
        }
    else{
        return empty_vec[0];
    }
    }
//for diagonal matrices
template<typename DataType>
 const DataType& matrix<DataType>:: at_diagonal_c(int  row_i,int  col_i)  const {
        if(row_i==col_i){
            return vec[row_i];
        }
        else{
            return empty_vec[0] ;
        }
    }

//for identity matrices
template<typename DataType>
const DataType& matrix<DataType>::at_identity_c(int  row_i,int  col_i)  const {

        if(row_i==col_i){
            //vec will only contain one element which is one
            //over engineered
            return vec[0];
        }
        else{
            return empty_vec[0] ;
        }
    }



    template<typename DataType>
    const DataType& matrix<DataType>:: at_const_c(int  row_i,int  col_i)  const{
            return vec[0] ;
        }

    template<typename DataType>
    const DataType& matrix<DataType>:: at(int  row_i,int  col_i)const{
        return (this->*at_ptr_c)(row_i, col_i);
    }

    template<typename DataType>
    DataType& matrix<DataType>:: at(int  row_i,int  col_i){
        return (this->*at_ptr)(row_i, col_i);
    }


//append cols of 2 matrices and return the new matrix
template <typename DataType>
matrix<DataType> matrix<DataType>::append_cols(const matrix&src)const {
    matrix<DataType>ret_mat ;
    if(src.rows==rows){
        ret_mat = matrix<DataType>(rows,cols+src.cols);
        for(int  row_c = 0;row_c<rows;row_c++){
            for(int  j= 0 ; j<cols;j++){
                ret_mat.at(row_c,j) =at(row_c,j) ;
            }
            for(int  j= 0 ; j<src.cols;j++){
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
        for(int  row_c = 0;row_c<rows+src.rows;row_c++){
            if(row_c<rows){
                for(int  j= 0 ; j<cols;j++){
                    ret_mat.at(row_c,j) =at(row_c,j) ;
                }
            }
            else{
                for(int  j= 0 ; j<cols;j++){
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
        for(int  i = 0 ;i <rows;i++){
            for(int  j = 0 ; j<cols ;j++){
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
         for(int  i = 0 ;i <rows;i++){
            for(int  j = 0 ; j<cols;j++){
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
void matrix<DataType>:: set_identity(){
    if(is_square()){
        for(int  i = 0 ;i <rows;i++){
            for(int  j = 0 ; j<cols ;j++){
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
template <typename DataType>
void matrix<DataType>::fill(DataType value){
    if(vec){
        for(int  i= 0 ; i <rows;i++){
            for(int  j =0 ; j<cols;j++){
                at(i,j) = value;
            }
        }
        matrix_type=constant ;
    }
}

//shows the matrix<DataType>:)
template <typename DataType>
void matrix<DataType>:: show(void)const {
    if(vec){
        for(int  row_counter=  0 ;  row_counter<rows; row_counter++){
            cout<<'\n' ;
            for(int  col_counter = 0  ; col_counter<cols;col_counter++){
                cout<<at(row_counter,col_counter)<<" ";
            }
        }
    }
}
//turns the whole matrix<DataType>int o a string ease print ing
template <typename DataType>
string matrix<DataType>::mat_to_string(void)const{
    string ret_str="" ;
    for(int  i = 0 ; i<rows;i++){
        ret_str+='[' ;
        for(int  j= 0 ; j<cols ;j++){
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
        for(int  i = 0 ;i<rows; i++){
            for(int  j = 0 ; j<cols ;j++){
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
        for(int  i = 0 ;i<rows; i++){
            for(int  j = 0 ; j<cols ;j++){
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
        for(int  i = 0 ;i<rows; i++){
            for(int  j = 0 ; j<cols ;j++){
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
        for(int  row_counter=  0 ;  row_counter<rows; row_counter++){
            for(int  col_counter = 0  ; col_counter<mat.cols;col_counter++){
                for(int  ele_counter = 0 ; ele_counter <cols;ele_counter++){
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
        for(int  i = 0 ; i <rows;i++){
            for(int  j = 0 ; j<cols;j++){
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
        int  res = 0;
        for(int  i = 0 ; i <rows;i++){
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
        for(int  i = 0 ; i <rows;i++){
            for(int  j=i+1;j<cols;j++){
                if(abs(at(i,j)-conjugate(at(j,i)))>check_tolerance){
                    return false ;
                }
            }
        }
    matrix_type =symmetric;
    return true ;
    }
    return false ;
}
template <typename DataType>

bool matrix<DataType>::is_diagonal(void) const {
    bool logic= is_upper_tri()&&is_lower_tri();
    if(logic){
        matrix_type==diagonal ;
    }
    return logic ;
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
    bool logic =trans_mat.is_identity() ;
    if(logic){
        matrix_type= orthonormal;
    }
    return logic;
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
    return  abs(theta(mat))<=tolerance||abs(theta(mat)-180)<=check_tolerance ;
}
template <typename DataType>

bool matrix<DataType>::operator == (const matrix&mat)const{
    if(same_shape(mat)){
       for (int  i = 0; i < rows; i++){
            for (int  j = 0; j <cols; j++) {
             if(abs(at(i,j)-mat.at(i,j))>check_tolerance){
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
void matrix<DataType>::row_axpy(DataType scalar,int  upper_row,int  lower_row){
    for(int  col_counter =0 ; col_counter<get_cols();col_counter++){
        at(lower_row,col_counter)+= at(upper_row,col_counter)*scalar;
    }
}
//performs downward gaussian elimination producing an upper triangular matrix
//optional if you want to know the indices of the pivots for each row
//pass in a matrix<DataType>aka pivots_indices
template <typename DataType>
matrix<DataType> matrix<DataType>::gauss_down( matrix<int >*pivots_indices,int  pivots_locations) const {
    if(matrix_type!=utri){
        matrix<DataType>ret_mat = *this;
        ret_mat.pindex =get_vec<int >(rows,1) ;
        fill_vec<int >(ret_mat.pindex,rows,-1) ;

        if(pivots_indices){
            if(pivots_locations==new_locations){
                *pivots_indices = matrix<int >(rows,1,-1) ;
            }
            else{
                //here it will be permutaions matrix
                //to record each row exchange happening
                *pivots_indices = matrix<int >(rows,1);
                for(int  i= 0 ; i<pivots_indices->get_rows();i++){
                    pivots_indices->at(i,0) = i;
                }
            }
        }
        //when getting pivot indices we have to keep track of old pivot since
        //the new pivot won't exist in the same column so we go to next column each iteration
        int  old_pivot = -1 ;
        for(int  up_r = 0;up_r<rows; up_r++){
            //check for pivot in the next column
                //at first iteration we check for sure for first col hence 1-1 = 0
            int  pivot_index =old_pivot+1  ;
            //if not a pivot then we find next pivot by increasing the pivot index
            //aka find it in the next column
            int  pivot_condition = ret_mat.is_pivot(up_r,pivot_index) ;
            while(pivot_index<cols&&pivot_condition==-1){
                pivot_index++ ;
                pivot_condition = ret_mat.is_pivot(up_r,pivot_index);
            }
            //make sure you aren't out of bounds
            if(pivot_index<cols){
                ret_mat.pindex[up_r]  =pivot_index;
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
                for(int  low_r = up_r+1; low_r<rows; low_r++){
                    //do gaussian elimination downward
                    //check if lower element is not zero to save processing power
                    if(abs(ret_mat.at(low_r,pivot_index))>tolerance){
                        DataType c = (ret_mat.at(low_r,pivot_index)/ret_mat.at(up_r,pivot_index))*DataType(-1);
                        for(int  i =pivot_index ; i<cols;i++){
                            ret_mat.at(low_r,i)+=c*ret_mat.at(up_r,i) ;
                        }
                    }
                }
                //record that pivot to search for next pivot in the next column not in same column
                //as mentioned above
                old_pivot = pivot_index ;
            }
        }
        ret_mat.matrix_type=utri ;
        ret_mat.compress_utri();
        return ret_mat;
    }
    matrix<DataType> ret_mat = *this;
    ret_mat.compress_utri()  ;
    return ret_mat;
}
//performs upward gaussian elimination producing a lower triangular matrix
//optional if you want to know the indices of the pivots for each row
//pass in a matrix<DataType>aka pivots_indices
template <typename DataType>
matrix<DataType> matrix<DataType>::gauss_up( matrix<int >*pivots_indices)const {
    if(matrix_type!=ltri){
        matrix<DataType>ret_mat = *this ;
        ret_mat.pindex = get_vec<int >(rows,1) ;
        fill_vec<int >(pindex,rows,-1) ;
        //same idea as gauss_down but instead of -1 its now rows since we look
        //for pivots from last row till first row
        int  old_pivot =cols;
        for(int  low_r = rows-1 ; low_r>=0;low_r--){
            //pivot_index in first iteration will be rows-1 which is the first location
            //to look for a pivot
            int  pivot_index =old_pivot-1 ;
            //if not a pivot then we find next pivot by decreasing the pivot index
            //aka find it in the prev column
            while(pivot_index>=0&&ret_mat.is_pivot_up(low_r,pivot_index)==-1){
                pivot_index-- ;
            }
            if(pivot_index>=0){
                ret_mat.pindex[low_r] = pivot_index ;
                for(int  up_r = low_r-1;up_r>=0;up_r--){
                    if(abs(ret_mat.at(up_r,pivot_index))>tolerance){
                        DataType c =(ret_mat.at(up_r,pivot_index)/ret_mat.at(low_r,pivot_index))*DataType(-1)  ;
                            for(int  col_c = pivot_index ; col_c>=0; col_c--){
                                ret_mat.at(up_r,col_c)+= c*ret_mat.at(low_r,col_c);

                        }
                    }
                }
                //keep track of pivot same as gauss_down
                old_pivot = pivot_index ;
            }
        }
        if(pivots_indices){
            *pivots_indices=matrix<int >(rows,1,ret_mat.pindex,rows) ;
       }
        ret_mat.matrix_type=ltri ;
        ret_mat.compress_ltri() ;
        return ret_mat;
    }
    matrix<DataType>ret_mat = *this;
    ret_mat.compress_ltri()  ;
    return ret_mat ;
}
//this function switches 2 rows and returns state of switching meaning the rows are valid
template <typename DataType>
bool matrix<DataType>::switch_rows(int  r1 ,int  r2 ){
    if(r1>=0&&r1<get_rows()&&r2>=0&&r2<get_rows()&&r1!=r2){
    for(int  i = 0 ; i <get_cols();i++){
        swap(at(r1,i),at(r2,i));
    }
    return true ;
}
return false  ;
}
//performs back substitution on lower triangular invertible matrix
template <typename DataType>
DataType matrix<DataType>:: back_sub(int  row_index,const matrix&sol_mat)const {
    DataType sum  = at(row_index,get_cols()-1);
    for(int  col_counter = row_index+1  ;col_counter<get_cols()-1; col_counter++){
        sum-=at(row_index,col_counter)*sol_mat.at(col_counter,0);
    }
    return sum/at(row_index,row_index) ;
}
//performs forward substitution on lower triangular invertible matrix
template <typename DataType>
DataType matrix<DataType>:: fwd_sub(int  row_index,const matrix&sol_mat)const {
    DataType sum  = at(row_index,get_cols()-1);
    for(int  col_counter = 0  ;col_counter<row_index;col_counter++){
        sum-=at(row_index,col_counter)*sol_mat.at(col_counter,0);
    }
    return sum/at(row_index,row_index) ;
}

//pass an appended matrix
template <typename DataType>
matrix<DataType> matrix<DataType>:: solve(void) const {
    matrix<int >pivots_indices;
    //turns the system int o uppertriangular system
    matrix<DataType>mat_cpy=gauss_down(&pivots_indices,new_locations);
    //check for number of pivots first
    for(int  i = 0 ; i<rows;i++){
        if(pivots_indices.at(i,0)==-1){
            cout<<"Number of pivots is insufficient default garbage value is -1" ;
            matrix<DataType>ret_mat = matrix(1,1,-1);
            return ret_mat ;
        }
    }
    //the new matrix<DataType>in which the answer will be returned
    matrix<DataType>sol_mat(get_rows(),1,0) ;
    for(int  row_c = get_rows()-1; row_c>=0;row_c--){
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
        matrix<int >original_pivots_indices ;
        matrix<DataType>mat_cpy =gauss_down(&original_pivots_indices,old_locations) ;
        DataType det_val = 1 ;
        int  sign_change = 0   ;
        for(int  i= 0  ; i<rows;i++){
            if(original_pivots_indices.at(i,0)!=i){
                sign_change++;
            }
            det_val*=mat_cpy.at(i,i) ;
        }
        if(sign_change>0){
                return(sign_change%2==0)?det_val*DataType(-1):det_val ;
        }
        return det_val;

}
    cout<<square_error ;
    return -1 ;
}

//calculates inverse of a square matrix<DataType>if available
template <typename DataType>
matrix<DataType> matrix<DataType>::inverse(void)const {
    if(is_square()){
        if(matrix_type!=orthonormal){
            //copying the m matrix<DataType>int o mat_cpy
            matrix<DataType>mat_cpy =*this ;
            //creating return matrix<DataType>which at first will be identity
            matrix<DataType>ret_mat=identity<DataType>(rows);
        //when getting pivot indices we have to keep track of old pivot since
        //the new pivot won't exist in the same column so we go to next column each iteration
        for(int  up_r = 0;up_r<rows; up_r++){
            int  pivot_condition = mat_cpy.is_pivot(up_r,up_r) ;
            if(pivot_condition!=-1){
                if(pivot_condition!=up_r){
                    ret_mat.switch_rows(up_r,pivot_condition);
                }
            //make sure you aren't out of bounds
                for(int  low_r = up_r+1; low_r<rows; low_r++){
                    //do gaussian elimination downward
                    //check if lower element is not zero to save processing power
                    if(abs(mat_cpy.at(low_r,up_r))>=tolerance){
                        DataType c = (mat_cpy.at(low_r,up_r)/mat_cpy.at(up_r,up_r))*DataType(-1);
                        for(int  i =0 ; i<cols;i++){
                            mat_cpy.at(low_r,i)+=c*mat_cpy.at(up_r,i) ;
                            ret_mat.at(low_r,i)+=c*ret_mat.at(up_r,i) ;
                        }
                    }
                }
            }
            else{
                cout<<"determinant of the passed matrix<DataType>is zero or not a squre matrix<DataType>to begin with";
                return matrix<DataType>(1,1,-1 );
            }
        }

            //then do Gaussian elimination upward
                //here we don't need to check if its a pivot since its shown clearly
                //from first elemination that it contains pivots at each row
                for(int  low_r = rows-1 ; low_r>0;low_r--){
                    for(int  up_r = low_r-1;up_r>=0;up_r--){
                        if(abs(mat_cpy.at(up_r,low_r))>tolerance){
                            DataType c = (mat_cpy.at(up_r,low_r) /mat_cpy.at(low_r,low_r))*DataType(-1)  ;
                            for(int  col_c = 0 ; col_c<cols ; col_c++){
                                mat_cpy.at(up_r,col_c)+= c*mat_cpy.at(low_r,col_c);
                                ret_mat.at(up_r,col_c)+= c*ret_mat.at(low_r,col_c);
                            }
                        }
                    }
                }
                for(int  i= 0 ; i<rows;i++){
                    for(int  j= 0 ; j<cols ; j++){
                        ret_mat.at(i,j) /=mat_cpy.at(i,i) ;
                    }
                }
                return ret_mat ;
            }
            return transpose() ;
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
        rows=mat.rows;
        cols = mat.cols ;
        empty_vec[0] =mat.empty_vec[0];
        matrix_type= mat.matrix_type;
        is_compressed=mat.is_compressed;
        set_feature(matrix_type);
        //then check if they don't have same shape
        if(acutal_size!=mat.acutal_size){
            //delete[] old memeory
            if(vec!=NULL){
                delete[]vec ;
            }
            if(row_start!=NULL){
                delete[]row_start ;
            }
            if(pindex!=NULL){
                delete[]pindex ;
            }
            //reallocate for copying
            vec= get_vec<DataType>(mat.acutal_size,1) ;
            row_start=NULL;
            pindex=NULL ;
            if(mat.matrix_type==utri||mat.matrix_type==ltri){
                copy_vec(row_start,mat.row_start,rows);
                copy_vec(pindex,mat.pindex,rows);
             }
             acutal_size =mat.acutal_size;
        }
        //copying mechanism
        for(int  i = 0 ; i <rows;i++){
            for(int  j= 0 ; j<cols ;j++){
                at(i,j) = mat.at(i,j) ;
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
    for(int  i = 0 ; i<rows;i++){
        for(int  j= 0 ; j<cols; j++){
            if(i==j){
                if(abs(at(i,j)-1)>check_tolerance) {
                    return false ;
                }
            }
            else{
                if(abs(at(i,j))>check_tolerance){
                    return false ;
                }
            }
    }
}
matrix_type= iden;
return true ;
}
return false ;
}//tested
    // Check if this matrix<DataType>is the zero matrix
template <typename DataType>
bool matrix<DataType>::is_zero(void)const {
    for(int  i = 0; i<rows;i++){
        for(int  j= 0 ;j<cols ;j++){
            if(abs(at(i,j))>check_tolerance){
                return false ;
            }
        }
    }
    matrix_type = constant;
    return true ;
}
template <typename DataType>

bool matrix<DataType>::is_upper_tri(void)const  {
        for(int  i =0 ; i <rows;i++){
            for(int  j=  0 ; j<i; j++){
                    if(abs(at(i,j))>check_tolerance){
                        return false ;

                    }
                }
            }
            matrix_type = utri;
            return true ;
}
template <typename DataType>

bool matrix<DataType>::is_lower_tri()const {
    for(int  i =0 ; i <rows;i++){
        for(int  j=  i+1 ; j<rows; j++){
                if(abs(at(i,j))>check_tolerance){
                    return false ;
                }
            }
        }
        matrix_type =ltri ;
        return true ;
}
// Check if this matrix<DataType>is scalar
template <typename DataType>
bool matrix<DataType>:: is_scalar(void)const {//tested
    if(is_square()){
        int  val = at(0,0) ;
        for(int  i=  0 ; i<rows; i++){
            for(int  j= 0  ;j<cols ; j++){
                if(i==j){
                    if(abs(at(i,j)-val)>check_tolerance){
                        return false ;
                    }
                }
                else{
                    if(abs(at(i,j))>check_tolerance){
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
int  matrix<DataType>::rank(void)const {//tested
    matrix<int >pivots_indices ;
    //first perform gaussian elimination downward
        gauss_down(&pivots_indices) ;
        int  counter = 0;
        //then count number of pivots
        for(int  i = 0 ;i<rows ; i++){
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
bool matrix<DataType>::is_anti_symmetric(void)const {
    if(vec&&is_square()){
        for(int  i = 0 ; i <rows;i++){
            for(int  j=i+1;j<cols;j++){
                if(abs(at(i,j)+conjugate(at(j,i)))>check_tolerance){
                    return false ;
            }
        }

    }
    matrix_type =anti_symmetric ;
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
        for(int  i = 0 ; i<rows ; i++){
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


template <typename DataType>
void  matrix<DataType>::lu_fact(matrix&lower_fact,matrix&permutation,matrix&upper_fact) const {
    if(matrix_type==utri){
        lower_fact=identity<DataType>(rows) ;
        lower_fact.matrix_type=iden ;
        lower_fact.compress_identity() ;
        permutation=identity<DataType>(rows) ;
        permutation.matrix_type=iden ;
        permutation.compress_identity() ;
        if(!is_compressed){
           upper_fact = *this;
           upper_fact.compress_utri() ;
        }
        else{
            upper_fact=*this;
        }
    }
    else{
    //first check if its square matrix
    if(is_square()){
        //the lower_fact matrix<DataType>is the identity matrix<DataType>(at first) in which we store
        // the constants during the gaussian elimination of the original matrix
        //after finisning the gaussian elimination the upper_fact is finished
        lower_fact = identity<DataType>(rows);
        //if permutations happen its recorded in this matrix
        permutation = identity<DataType>(rows);
        upper_fact = *this  ;
        lower_fact.pindex=get_vec<int >(rows,1);
        upper_fact.pindex=get_vec<int >(rows,1);
        //copy original matrix<DataType>int o upper_fact to performa gaussian elimination on it
        for(int  up_r = 0;up_r<rows-1; up_r++){
            int  pivot_condition =upper_fact.is_pivot(up_r,up_r);
            if(pivot_condition!=-1){
                //aka its a pivot
                //if a switch happened
                if(pivot_condition!=up_r){
                    permutation.switch_rows(up_r,pivot_condition);
                }
                upper_fact.pindex[up_r]= up_r;
                lower_fact.pindex[up_r] = up_r;
                    //no switch happened
                for(int  low_r = up_r+1; low_r<rows; low_r++){
                    //check first if upper element is a pivot
                    //the constant we calculate
                    DataType c = (upper_fact.at(low_r,up_r)/upper_fact.at(up_r,up_r))*DataType(-1);
                    //first record it int o the lower_fact matrix<DataType>at its position
                    lower_fact.at(low_r,up_r)  = c*DataType(-1) ;
                    for(int  i =0 ; i<cols;i++){
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
            upper_fact.pindex[rows-1] = rows-1;
            lower_fact.pindex[rows-1] = rows-1;
            lower_fact.matrix_type=ltri;
            upper_fact.matrix_type=utri ;
            lower_fact.compress_ltri();
            upper_fact.compress_utri();
        }
    else{
        cout<<square_error;
        lower_fact =  matrix(1,1,-1) ;
        upper_fact =  matrix(1,1,-1) ;
    }
}
}
//this function checks if an element is a pivot
//and switches the rows if the original element is not a pivot
//with the first non zero element it finds
//now updated to return the row of the pivot to keep record of the rows
//if rows are switched used in lu_fact
template <typename DataType>
 int matrix<DataType>:: is_pivot(int  r_ind , int  c_ind) {
    if(r_ind<rows&&c_ind<cols){
        //find first non zero element in that row
        int  pivot_index = r_ind ;
        while(pivot_index<rows){
            if(abs(at(pivot_index,c_ind))>check_tolerance){
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
int matrix<DataType>:: is_pivot_up(int  r_ind , int  c_ind) {
    if(r_ind<rows&&c_ind<cols){
        //find first non zero element in that row
        int  pivot_index = r_ind ;
        while(pivot_index>=0){
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
    matrix<DataType> matrix<DataType>:: rref(matrix<int  >*pivots_indices)const {
        //pivots locations will be mapped in this array
        //so if row zero contains a pivot at col index 1  for ex and so on
        //it will have the value 1 in that row and so on
        //return matrix
        //do gaussian elemination downward
        matrix<int >pivots_locations;
        matrix<DataType>ret_mat = gauss_down(&pivots_locations);
        //do gaussian elimination upward using the pivots_locations
        for(int  low_r = rows-1 ; low_r>0;low_r--){
            int  pivot_index = pivots_locations.at(low_r,0);
            if(pivot_index!=-1){
                for(int  up_r = low_r-1;up_r>=0;up_r--){
                    DataType c =(ret_mat.at(up_r,pivot_index) /ret_mat.at(low_r,pivot_index)) *DataType(-1)  ;
                    for(int  col_c = 0 ; col_c<cols ; col_c++){
                        ret_mat.at(up_r,col_c)+= c*ret_mat.at(low_r,col_c);
                }
            }
       }
    }
        //go in each row and if that row contains a pivot divid each element by
        //by the pivot
        for(int  i = 0 ; i<rows;i++){
            int  pivot_index = pivots_locations.at(i,0);
            if(pivot_index!=-1){
                DataType val = ret_mat.at(i,pivot_index);
                if(abs(val)>tolerance){
                    for(int  j=  0 ; j<cols;j++){
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
    int  matrix<DataType>::dim(void)const {
        return rank() ;
    }//tested
    //returns dimension of the null space of column space
    template <typename DataType>
    int  matrix<DataType>::dim_null_cols(void)const {
        return cols - rank();
    }
    //returns dimension of the null space of row space
    template <typename DataType>
    int  matrix<DataType>::dim_null_rows(void)const {
        return rows - rank() ;
    }
    //checks if a bunch of vectors form basis of a space R^dimension
    template <typename DataType>
    bool matrix<DataType>::is_basis( int  dimension)const {
        //check if they are independent and they span the column space of R^dimension
        return cols==dimension&&is_independent() ;
    }
    //returns the set of vectors that forms a basis of the column space
    template <typename DataType>
    matrix<DataType> matrix<DataType>::basis_cols(void) const {
        //return matrix
        matrix<DataType>ret_mat ;
        //matrix<DataType>in which we store indicex of each pivot in the correspoinding row
        matrix<int >pivots_indices ;
        //perform gaussian elimination downward
        gauss_down(&pivots_indices) ;
        //get dimension of the column space
        int  pivot_count = 0 ;
        //count number of pivots and stop when you find -1
        //aka no remaining pivots refer to is_pivot and check what it does for
        //more info
        for(int  i = 0 ;i<rows; i++){
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
            for(int  row_c = 0 ; row_c<rows ; row_c++){
                for(int  col_c =0 ; col_c<pivot_count; col_c++){
                    //get the pivot index in that row
                    int  pivot_index=pivots_indices.at(col_c,0) ;
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
        matrix<int >pivots_indices(rows,1,-1);
            //perform gaussian elimination downward
        matrix<DataType>mat_rref = rref(&pivots_indices) ;
        //get dimension of the column space
        int  pivot_count = 0 ;
        //count number of pivots and stop when you find -1
        //aka no remaining pivots refer to is_pivot and check what it does for
        //more info
        for(int  i = 0 ;i<rows; i++){
            if(pivots_indices.at(i,0)!=-1){
                pivot_count++ ;
            }
            else{
                break ;
            }
        }
        //copy first rows that are the pivot rows from rref
        ret_mat = matrix(pivot_count,cols) ;
        for(int  i = 0 ; i<pivot_count;i++){
            for(int  j = 0 ;  j<cols; j++){
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
        matrix<DataType>elementary=identity<DataType>(rows);
        matrix<DataType>mat_cpy = *this ;
        mat_cpy.fix_pivots();
        //when getting pivot indices we have to keep track of old pivot since
        //the new pivot won't exist in the same column so we go to next column each iteration
        int  old_pivot = -1 ;
        for(int  up_r = 0;up_r<rows; up_r++){
            //check for pivot in the next column
                //at first iteration we check for sure for first col hence 1-1 = 0
            int  pivot_index =old_pivot+1  ;
            //if not a pivot then we find next pivot by increasing the pivot index
            //aka find it in the next column
            while(pivot_index<cols&&mat_cpy.is_pivot(up_r,pivot_index)==-1){
                pivot_index++ ;
            }
            //make sure you aren't out of bounds
            if(pivot_index<cols){
                pivots_indices.at(up_r,0) = pivot_index ;
                for(int  low_r = up_r+1; low_r<rows; low_r++){
                    //do gaussian elimination downward
                    //check if lower element is not zero to save processing power
                    if(abs(mat_cpy.at(low_r,pivot_index))>tolerance){
                        DataType c = (mat_cpy.at(low_r,pivot_index)/mat_cpy.at(up_r,pivot_index))*-1;
                        for(int  i =pivot_index ; i<cols;i++){
                            mat_cpy.at(low_r,i)+=c*mat_cpy.at(up_r,i) ;
                        }
                        for(int  i =0 ; i<=pivot_index;i++){
                            elementary.at(low_r,i) +=elementary.at(up_r,i)*c ;
                        }
                    }
                }
                //record that pivot to search for next pivot in the next column not in same column
                    //as mentioned above
                old_pivot = pivot_index ;
            }
        }
        //do gaussian elimination upward using the pivots_locations
        for(int  low_r = rows-1 ; low_r>0;low_r--){
            int  pivot_index = pivots_indices.at(low_r,0);
            if(pivot_index!=-1){
                for(int  up_r = low_r-1;up_r>=0;up_r--){
                    DataType c = -1 * (mat_cpy.at(up_r,pivot_index) /mat_cpy.at(low_r,pivot_index));
                    for(int  col_c = cols-1 ; col_c>=pivot_index; col_c--){
                        mat_cpy.at(up_r,col_c)+=c*mat_cpy.at(low_r,col_c) ;
                    }
                    for(int  col_c = rows-1 ; col_c>=pivot_index ; col_c--){
                        elementary.at(up_r,col_c)+= c*elementary.at(low_r,col_c);
                    }
                }
           }
        }
        //go in each row and if that row contains a pivot divide each element by
        //by the pivot
        int  pivot_c = 0 ;
        for(; pivot_c<rows;pivot_c++){
            int  pivot_index = pivots_indices.at(pivot_c,0);
            //if the following row contains a pivot then we divide the whole row by that pivot
            if(pivot_index!=-1){
                DataType val = mat_cpy.at(pivot_c,pivot_index);
                if(val){
                    //do that for each element in the row
                    for(int  j=  0 ; j<rows;j++){
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
            int  c= 0  ;//counter for rows of return matrix
            for(; pivot_c<rows;pivot_c++){
                for(int  j = 0 ; j<rows; j++){
                    ret_mat.at(c,j) = elementary.at(pivot_c,j) ;
                }
                c++;
            }
        }
        else{
             ret_mat= matrix(1,rows,0);
        }
    if(e){
            //if the user wants the elementary matrix<DataType>then do the copying int o e
            *e= elementary ;
        }
    return ret_mat ;
    }
    template <typename DataType>
    matrix<DataType> matrix<DataType>::null_cols(void)const  {
        //here the pivots indices are stored along with indices of free variables
        matrix<int >pivots_indices =matrix<int >(cols,1,-1);
        //here the pivots indices are stored
        matrix<int >p_cpy ;
        matrix<DataType>mat_rref = rref(&p_cpy) ;
        //solution matrix<DataType>with all speacial solutions
        matrix<DataType>ret_mat;
        //copy the content from p_cpu int o pivots indices
        int  c=  cols<rows?cols:rows ;
        for(int  i = 0 ; i<c;i++){
            pivots_indices.at(i,0) = p_cpy.at(i,0)  ;
        }
        //counting number of pivots to check if there are special solutions
        int  pivot_c  =0   ;
        while(pivot_c<cols&&pivots_indices.at(pivot_c,0)!=-1){
            pivot_c++;
        }
        if(pivot_c<cols){
            int  counter=0 ;
            //fill rest of pivots_indices with free vars indices
            for(int  i = 0 ; i<cols;i++){
                //for each index that is not a pivot put it in
                //the rest of the pivots_indices
                bool flag=  false ;
                for(int  j= 0 ; j<pivot_c; j++){
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
            for(int  i =0;i<(cols-pivot_c);i++){
                int  one_pos = pivots_indices.at(cols-i-1,0) ;
                //put the one in its postion for the new special solution
                ret_mat.at(one_pos,i) =1 ;
                //for the current pivot we are calculating the value for
                //"index of the pivot in special solution matrix"
                for(int  curr_piv= pivot_c-1 ; curr_piv>=0; curr_piv--){
                    //x1 = (-x3*2-x2*2)/3
                    //x0 = (-x3*2-x2*2-x1*3)/4
                    int  pivot_index = pivots_indices.at(curr_piv,0);
                    for(int  j= cols-1  ; j>curr_piv;j--){
                        int  free_v_index= pivots_indices.at(j,0);
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
        matrix<int > original_pivots_indices ;
        gauss_down(&original_pivots_indices,old_locations) ;
        //if i switched already don't do it again
        //i switched 2 with 1 then don't switch 1 with 2 again
        /*
        1
        0
        2
        */
        bool switch_rec[rows] ={0} ;
        for(int  i= 0 ; i<rows;i++){
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
        AtransA = *this *AtransA* Atrans ;
        AtransA.matrix_type= symmetric;
        AtransA.compress_symmetric() ;
        return AtransA;
    }
    //fit a data set int o a linear system
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
    matrix<DataType> matrix<DataType>::extract_col(int  index)const {
        matrix<DataType>ret_mat ;
        if(index>=0&&index<cols){
            ret_mat= matrix<DataType>(rows,1);
            for(int  i =0;i<rows;i++){
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
/*when using gram_shmidt its better to use it with double and with very low
tolerance value very close to zero
i've noticed it produces wrong answers due to those 2 problems when testing the algorithm */
    template <typename DataType>
    matrix<DataType> matrix<DataType>::gram_shmidt(void)const {
        //array of projections for each vector from 0 to n-1
        //no need for the nth
        matrix<DataType>projections_arr[cols-1];
        //here we store each orthonormal vector
        matrix<DataType>ret_mat(rows,cols);
        //temporary storage for the resultant vector
        matrix<DataType>res(rows,1) ;
        //here we store projection[i]*vec
        matrix<DataType>temp(rows,1) ;
        //length of a vector variable
        DataType len = 0;
        //for each vector
        for(int  vec_c =0; vec_c <cols;vec_c++){
            //Vn = v- P0*v-P1*v
            //these projections are projections of the new obtained
            //orthogonal vectors
            //res=  v
            for(int  i = 0 ; i<rows;i++){
                res.at(i,0) = at(i,vec_c);
                temp.at(i,0)=res.at(i,0) ;
            }
            //temp storage for the column itself
            for(int  proj_c = 0;proj_c<vec_c ;proj_c++){
               //get projection of each vector * same vector
                //while subtracting it from the result
                res = res - projections_arr[proj_c]*temp;

            }
            //get the length
            len=res.length();
            if(len>tolerance){
                for(int  row_c = 0 ; row_c<rows;row_c++){
                    //while filling the result column divide by the length
                    res.at(row_c,0) =res.at(row_c,0)/len;
                    ret_mat.at(row_c,vec_c) =res.at(row_c,0);
                }
            }
            //get the projection of the newly created vector
            if(vec_c<cols-1){
                projections_arr[vec_c] = res.projection();
            }
        }
        ret_mat.matrix_type = orthonormal ;
        return ret_mat ;
    }
    //performs A -lambda * I
    //where I is the identity
    //then returns the solution
    template <typename DataType>
    matrix<DataType> matrix<DataType>::SubLambdaI(DataType lambda)const {
        matrix<DataType>ret_mat =*this ;
        for(int  i = 0 ;i<rows;i++){
            ret_mat.at(i,i)-=lambda ;
        }
        return ret_mat ;
    }
    //returns eigen vectors of a system using eigen values
    //calculate null space for each A-lambda *I
    //and append it to eigen vectors matrix
    template <typename DataType>
    matrix<DataType> matrix<DataType>::eigen_vectors(const matrix&eigen_vals)const {
        matrix<DataType>ret_mat(rows,rows);
        matrix<DataType>temp_mat =*this ;
        for(int  i = 0;i<rows;i++){
            for(int  k = 0 ;k<rows;k++){
                temp_mat.at(k,k)-=eigen_vals.at(i,i) ;
            }
            matrix<DataType>null_vec=temp_mat.null_cols() ;

            for(int  j= 0;j<rows;j++){
                temp_mat.at(j,j)=at(j,j) ;
            }
            for(int  j= 0;j<rows;j++){
                ret_mat.at(j,i) =null_vec.at(j,0) ;
            }
        }
        return ret_mat ;
    }
    //returns cofactor of an element at position row_i,col_i
    template <typename DataType>
    DataType matrix<DataType>::cofactor(int  row_i, int  col_i)const {
        if(is_square()&&row_i>=0&&row_i<rows&&col_i>=0&&col_i<cols){
            matrix<DataType>temp(rows-1,cols-1);
            int  tr=0,tc= 0;//counters for temp matrix

            for(int  i = 0 ; i<rows;i++){
                tc=0;
                //don't include the row where we want to get its cofacotr
                if(i!=row_i){
                    for(int  j= 0 ; j<cols; j++){
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
            for(int  i= 0  ; i<rows;i++){
                for(int  j=  0 ;j<cols;j++){
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
    // Function to rearrange the rows of the matrix according to a sequence
    template <typename DataType>
    matrix<DataType> matrix<DataType>::arrange(const matrix<int >&seq)const{
        matrix<DataType> ret_mat;
        // Check if the sequence has the same number of rows as the matrix
        if(rows==seq.get_rows()){
            // Create a new matrix with the same dimensions
            ret_mat = matrix<DataType>(rows,cols);
            // Copy the rows from the original matrix to the new matrix in the order specified by the sequence
            for(int  i =0 ; i<rows;i++){
                int  row_ind  = seq.at(i,0) ;
                for(int  j = 0; j<cols;j++){
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

    // Function to replace a quarter of the matrix with another matrix
    template <typename DataType>
    void matrix<DataType>::at_quarter(int  quarter,const matrix<DataType>&src){
        // Check if the quarter is valid
        if(quarter>=0&&quarter<4){
            // Check if the source matrix fits int o a quarter of the original matrix
            if(src.rows<=rows/2&&src.cols<=cols/2){
                int  row_offset,col_offset ;
                // Determine the offset based on the quarter
                switch(quarter){
                    case upper_left:{row_offset=0;col_offset=0;}break;
                    case lower_left:{row_offset=rows/2;col_offset=0;}break;
                    case upper_right:{row_offset=0;col_offset=cols/2;}break;
                    case lower_right:{row_offset=rows/2;col_offset=cols/2;}break;
                }
                // Copy the elements from the source matrix to the specified quarter of the original matrix
                for(int  i = 0 ; i<src.rows;i++){
                    for(int  j= 0 ; j<src.cols;j++){
                        at(row_offset+i,j+col_offset) = src.at(i,j) ;
                    }
                }
            }
        }
        else{
            cout<<"\ndenied\n";
        }
    }
    // Function to create a Fourier transform matrix
    matrix<complex> fourier_mat(int  dimension){
        // Check if the dimension is valid
        if(dimension>0){
            // Calculate the complex exponential
            complex w(cos((2*M_PI)/dimension),sin((2*M_PI)/dimension));
            // Create a new matrix with the specified dimension
            matrix<complex> ret_mat(dimension,dimension);
            // Fill the matrix with powers of the complex exponential
            for(int  i=0  ; i<dimension;i++){
                for(int  j= i ; j<dimension;j++){
                   complex temp =  pow(w,(i*j)) ;
                   ret_mat.at(i,j) =temp;
                   ret_mat.at(j,i) =temp;
                }
            }
            ret_mat.compress() ;
            return ret_mat ;
        }
        cout<<"can't have 0 or -ve dimensions default garbage value is -1";
        matrix<complex> err_mat(1,1,-1) ;
        return err_mat;
    }

    // Function to split the matrix int o two halves
    template <typename DataType>
    matrix<DataType> matrix<DataType>::split(int  half )const{
        // Create a new matrix with half the rows
        matrix<DataType>ret_mat(rows/2,cols) ;
        int  row_c = (half==lower_half)?(rows/2):0;
        int  rt=0;
        // Copy the elements from the original matrix to the new matrix
        for(;rt<rows/2;rt++){
            for(int  col_c= 0;col_c<cols;col_c++){
                ret_mat.at(rt,col_c)=at(row_c,col_c) ;
            }
            row_c++;
        }
        // Return the new matrix
        return ret_mat;
    }
    // Function to create a diagonal matrix for Fourier transform
    matrix<complex> fourier_diagonal(int  dimension,int  n){
        // Check if the dimension is valid
        if(dimension>0){
            // Calculate the complex exponential
            complex w(cos((2*M_PI)/dimension),sin((2*M_PI)/dimension));
            // Create a new matrix with n rows and 1 column
            matrix <complex>ret_mat(n,1) ;
            // Fill the matrix with powers of the complex exponential
            for(int  i = 0 ; i<n;i++){
                ret_mat.at(i,0) =pow(w,i) ;
            }
            return ret_mat ;
        }
        // If the dimension is not valid, return an error matrix
        matrix<complex> err_mat(1,1,-1);
        cout<<"invalid dimension default garbage value is -1";
        return err_mat;
    }

    // Function to create an identity matrix
    template <typename DataType>
    matrix<DataType> identity( int  dimension){
        matrix<DataType> ret_mat ;
        // Check if the dimension is valid
        if(dimension>0){
            // Create a matrix with all elements 0
            ret_mat=matrix<DataType>(dimension,dimension,0);
            // Set the diagonal elements to 1
            for(int  i =0 ; i<dimension;i++){
                ret_mat.at(i,i) = 1 ;
            }
        }
        else{
            cout<<"sent dimension is less than 1";
            ret_mat = matrix<DataType>(1,1,-1) ;
        }
        return ret_mat ;
    }

    // Function to compute the Fast Fourier Transform (FFT) of a column
    template <typename DataType>
    matrix<DataType> matrix<DataType>::fft_col(int  dimension)const{
        // Base case: if the matrix has only one row, return the matrix itself
        if(rows==1){
            return (*this) ;
        }
        if(dimension<=rows){
            // Create a sequence of even and odd indices
            matrix<int >seq(rows,1);
            for(int  i = 0 ; i<rows/2;i++){
                seq.at(i,0) = 2*i ;
                seq.at(i+rows/2,0)=2*i+1;
            }
            // Create a diagonal matrix for Fourier transform
            matrix<complex>diag=fourier_diagonal(dimension,rows/2);

            // Rearrange the matrix according to the sequence
            matrix<complex>temp_vec = (*this).arrange(seq) ;

            // Split the rearranged matrix int o even and odd halves and compute the FFT of each half
            matrix<complex>even_half=temp_vec.split(upper_half).fft_col(dimension/2);
            matrix<complex>odd_half=temp_vec.split(lower_half).fft_col(dimension/2);
            complex d;
            // Combine the FFTs of the halves
            for(int  i = 0 ; i<(dimension/2);i++){
                d=odd_half.at(i,0)*diag.at(i,0);
                temp_vec.at(i,0) = even_half.at(i,0) +d ;
                temp_vec.at((i+dimension/2),0)= even_half.at(i,0)-d;
            }
            // Return the FFT of the matrix
            return temp_vec;
        }
        else{
            cout<<"Dimension is bigger than size of the column default garbage value is -1";
            return matrix(1,1,-1);
        }
    }
    //fft for a matrix or a column the fft_col is just a helper function

    template<typename DataType>
    matrix<DataType> matrix<DataType>:: fft(void)const{
        matrix<DataType> ret_mat(rows,cols);
        matrix<DataType> col ;
        float val = log2(rows);//check if powers of 2
        if((val-float(int (val)))!=0){
            //int (val) removes fraction
            //float(int (val)) turns the int eger int o a float for no errors
            //resize to higher power of 2 and pad rest of elements with zeroes
            col= matrix<DataType>(pow(2,(int (val)+1)),1,0) ;
        }
        else{
            col = matrix<DataType>(rows,1,0);
        }
        for(int  col_c =0 ; col_c<cols;col_c++){
            //copy content of the column int o a new column
            for(int  k = 0; k<col.rows;k++){
                if(k<ret_mat.rows){
                    col.at(k,0) = at(k,col_c) ;
                }
                //fill rest col elements with zeroes
                else{
                    col.at(k,0)= 0 ;
                }
            }
            //perform the fourier transform on that col
            col = col.fft_col(col.rows) ;
            //copy it int o the resultant matrix
            for(int  j= 0 ; j<ret_mat.rows;j++){
                ret_mat.at(j,col_c)=col.at(j,0);
            }
        }
        return ret_mat ;
    }



    //resize a matrix to wanted dimensions if the new total size is less
    //then it copies that equal chunk of the older matrix int o the new one
    //if its more then the rest are by default equal to the value of zero
    template <typename DataType>//by defaults it operates as equality operator
    matrix<DataType> matrix<DataType>::resize(int  wanted_rows ,int  wanted_cols,DataType padding_value)const{
       if(wanted_rows>0&&wanted_cols>0){
           matrix<DataType> ret_mat= matrix<DataType>(wanted_rows,wanted_cols,padding_value) ;
            int  end_rows = (wanted_rows<rows)?wanted_rows:rows ;
            int  end_cols = (wanted_cols<cols)?wanted_cols:cols ;
            for(int  i = 0 ; i<end_rows;i++){
                for(int  j=0;j<end_cols;j++){
                    ret_mat.at(i,j)=at(i,j) ;
                }
            }
            return ret_mat ;
        }
        cout<<"Can't have dimensions less than 1 default garbage value is -1";
        return matrix<DataType>(1,1,-1) ;
    }
    //returns pivots of a matrix in column matrix
    template <typename DataType>
    matrix<DataType> matrix<DataType>:: get_pivots(matrix<int >*pivots_locations)const{
        matrix<DataType> pivots(rows,1,0);
        matrix<int > pivots_loc;
        matrix<DataType> temp=gauss_down(&pivots_loc,new_locations) ;
        int  piv_c = 0  ;
        while(piv_c<rows&&pivots_loc.at(piv_c,0)!=-1){
            pivots.at(piv_c,0) = temp.at(piv_c,pivots_loc.at(piv_c,0)) ;
            piv_c++;
        }
        if(pivots_locations){
            *pivots_locations = pivots_loc ;
        }
        pivots.set_feature(diagonal) ;
        pivots.is_compressed=true;
        return pivots ;
    }

    //checks if a matrix is positive definite
    template <typename DataType>
    bool matrix<DataType>::is_positive_definite(void)const{
        if(is_symmetric()){
            matrix_type = symmetric ;
            matrix<DataType> pivots= get_pivots();
                for(int  i =  0; i<rows;i++){
                    if(abs(pivots.at(i,i))<=check_tolerance){
                        return false ;
                    }
                }
                return true  ;
        }
        return false ;

    }
    //performs QR factorization on a matrix and puts them in q ,r passed in the function input
    template<typename DataType>
    void matrix<DataType>:: qr_fact(matrix<DataType>&q,matrix<DataType>&r)const{
        q= gram_shmidt() ;
        q.matrix_type= orthonormal;
        r= q.transpose() *(*this) ;
        r.matrix_type =utri;
        r.compress_utri() ;
    }
    //returns eigen values of a matrix in a column matrix
    //computations made by qr factorization
    //doesn't generate correct results all the time due to divergence issues
    template <typename DataType>
    matrix<DataType> matrix<DataType>::eigen_values(const int &max_iteration,const double& min_diff)const{
        matrix<DataType>q,r ;
        matrix<DataType>mat_cpy = *this;
        matrix<DataType>eigen(rows,1,0);
        int  iter = 0  ;
        int  diff_counter = 0;
        while(!(mat_cpy.is_upper_tri())&&(diff_counter<rows)&&(iter<max_iteration)){
            for(int  j=  0   ;j <rows ; j++){
                eigen.at(j,0)= mat_cpy.at(j,j) ;
            }
            mat_cpy.qr_fact(q,r) ;
            mat_cpy= r*q;
            //check difference
            diff_counter = 0;
            if(iter>max_iteration/2){
                for(int  j= 0 ; j<rows ;j++){
                    if(abs(mat_cpy.at(j,j)-eigen.at(j,0))<=min_diff){
                        diff_counter++ ;
                    }
                }
            }
            iter++ ;
        }
        for(int  i=  0 ; i<mat_cpy.rows;i++){
            eigen.at(i,0) = mat_cpy.at(i,i) ;
        }
        eigen.cols=rows;
        eigen.set_feature(diagonal);
        eigen.is_compressed=true;
        return eigen ;
    }

    //returns a matrix with data randomly initialized
    template <typename DataType>
    matrix<DataType> rand(int  row_size,int  col_size,int  max_val){
        if(row_size>0&&col_size>0){
            srand(time(0)) ;
            matrix<DataType>ret_mat(row_size,col_size) ;
            for(int  i = 0  ;i<row_size;i++){
                for(int  j = 0 ; j<col_size;j++){
                    int  val=rand()%max_val;
                    ret_mat.at(i,j)=DataType(val) ;
                }
            }
        return ret_mat ;
        }
        cout<<"dimensions less than 1 default garbage value is -1" ;
        return matrix<DataType>(1,1,-1) ;
    }

    //filters the matrix elements from data less than a specified tolerance
    //by default filters by check_tolerance
    template<typename DataType>
    void matrix<DataType>::filter(double filter_tolerance){
        for(int  i =0 ; i<rows;i++){
            for(int  j=  0 ; j<cols;j++){
                if(abs(at(i,j))<=filter_tolerance){
                    at(i,j) = 0;
                }
            }
        }
    }
    template<typename DataType>
    matrix<DataType> matrix<DataType>::operator^(const DataType &power)const {
        /*
        AS=S^
        A=S^S
        Aexp(k)=S^exp(k)S^-1
        */
        //S A^power S^-1
        matrix<DataType> eig_vals = eigen_values(600,0.00001) ;
        matrix<DataType>eig_vecs  = eigen_vectors(eig_vals);//S
        for(int  i =0;i<rows;i++){
            eig_vals.at(i,i) = pow(eig_vals.at(i,i),power) ;
        }
        //get S
        matrix<DataType>inv_eig = eig_vecs.inverse();//S^-1
        for(int  i = 0 ; i<rows;i++){
            for(int  j= 0 ; j<cols;j++){
                eig_vecs.at(i,j)*=eig_vals.at(j,j) ;
            }
        }
        return eig_vecs*inv_eig ;
    }
    template<typename DataType>
    //calculates the length of a column at a specified index
    DataType matrix<DataType>::col_length(const int & col_i)const{
        if(col_i>=0&&col_i<cols){
            DataType len=  0;
            for(int  i= 0;i<rows;i++){
                len+=(at(i,col_i)*at(i,col_i));
            }
            return sqrt(abs(len));
        }
        cout<<"out of bounds default garbage value is -1";
        return DataType(-1);

    }

    template<typename DataType>
    //A = U S VT
    void matrix<DataType>::svd(matrix&u,matrix&s,matrix&vt)const{
        //A V=U S->A=U S VT
        // A AT=U S^2 UT
        //get S , then V
        //A=U S VT ->U = A VT S^-1
        matrix<DataType> AAT= (*this)*transpose() ;
        s=AAT.eigen_values(600,0.00001);//S^2
        u =AAT.eigen_vectors(s);//U
        //a row to store length of each column
        for(int  i = 0 ; i<u.cols;i++){
            DataType len = u.col_length(i);
            if(len>tolerance){
                for(int  j =  0  ; j<u.rows;j++ ){
                    u.at(j,i)/=len;
                }
            }
        }
        vt =(transpose()*(*this)).eigen_vectors(s);
        for(int  i = 0 ; i<vt.cols;i++){
            DataType len = vt.col_length(i) ;
            if(len>tolerance){
                for(int  j =  0  ; j<vt.rows;j++ ){
                    vt.at(j,i)/=len;
                }
            }
        }
        vt=vt.transpose();
        for(int  i =0 ; i<s.rows;i++){
            s.at(i,i) =sqrt(s.at(i,i)) ;
        }
        u.matrix_type=orthonormal;
        s.matrix_type=diagonal;
        s.cols= rows ;
        vt.matrix_type=orthonormal;
    }
    //returns the linear transformation matrix that turns and input (caller) int o an output (input parameter)
    //input->system->output
    template<typename DataType>
    matrix<DataType> matrix<DataType>::transformer(const matrix<DataType>& output)const  {
        //store locations of pivots
        matrix<int > pivots_indices;
        //augment the input with the out put and then perform gaussian elimination
        //on that matrix
        matrix<DataType> augmented = (transpose().append_cols(output.transpose())).gauss_down(&pivots_indices);
        for(int  i = 0 ;  i<pivots_indices.get_rows();i++){
            if(pivots_indices.at(i,0)!=i){
                cout<<"must pass independent cols in both input and output to get the system";
                cout<<" default garbage value is -1";
                return matrix<DataType>(1,1,-1) ;
            }
        }
        matrix<DataType> solution(output.rows,cols);
        //now for every col of the right side do back-substitution with the input
        //to get a column of the system
        //do it on paper and whole picture appeas
        /*
        system  input   output
        [c1 c2] [1,2] = [1,0]
        [c3 c4] [2,2]   [0,1]
        c1*1+c2*2 = 1->[1 2][c1]=[1]solve and get c1 and c2 and repeat for c3 &c4
        c1*2+c2*2 = 0->[2 2][c2] [0]
        so perform gaussian eliminaiton on the augmented matrix once and perform that algorithm for each column
        of the right half
        */
        for (int  col = 0; col < output.cols; col++) {
            for (int  i = get_rows() - 1; i >= 0; i--) {
                DataType sum = augmented.at(i, get_cols()+ col);
                for (int  j = get_cols()-1 ; j >i; j--) {
                    sum -= augmented.at(i, j) * solution.at(j, col);
                }
                solution.at(i, col) = sum / augmented.at(i,i);
            }
        }
        return solution.transpose();
    }




//here is the compression algorithm for each matrix type
//they are private so the public one is compress(int  matrix type)
//here row_start is filled and pindex aswell
//passed function must be one of those types with zeroes
template<typename DataType>
void matrix<DataType> ::compress_utri(void){
    if(!is_compressed&&matrix_type==utri){
        //first dimensions
        is_compressed=true;
        //mapping in here
        row_start = get_vec<int >(get_rows(),1) ;
        fill_vec<int >(row_start ,rows,-1);

        if(pindex==NULL){
            get_pindex() ;
        }
        row_start[0] = 0;
        //size of acutall data in the matrix
        int  size = 0  ;
        //first calculate the size
        //mapping the data to the array
        for(int  i =0; i<get_rows();i++){
            if(pindex[i]!=-1){
                row_start[i]=size;
                size+=cols-pindex[i] ;
            }
        }
        //filling data
        DataType*new_vec =  get_vec<DataType>(size,1) ;
        acutal_size = size;
        is_compressed=true;
        int  pos = 0  ;
        for(int  i=  0 ;i<rows;i++){
            if(pindex[i]!=-1){
                for(int  j= pindex[i];j<cols;j++){
                    new_vec[pos] = at(i,j);
                    pos++;
                }
            }
        }
        delete[]vec ; vec =NULL;
        vec= new_vec ;
        set_at_ptr(utri) ;
    }

}
template<typename DataType>
void matrix<DataType> ::compress_ltri(void){
    //first dimensions
    if(!is_compressed&&matrix_type==ltri){
        //mapping in here
        row_start = get_vec<int  >(get_rows(),1) ;
        fill_vec<int  >(row_start,rows,-1);
        if(pindex==NULL){
            get_pindex() ;
        }
        //size of acutall data in the matrix
        int  size = 0  ;
        //first calculate the size
        //mapping the data to the array
        for(int  i =0; i<get_rows();i++){
            if(pindex[i]!=-1){
                row_start[i]=size;
                size+=pindex[i]+1;
            }
        }
        //filling data
        DataType*new_vec = get_vec<DataType>(size,1) ;
        acutal_size = size;
        is_compressed=true;
        int  pos = 0  ;
        for(int  i=  0 ;i<rows;i++){
            if(pindex[i]!=-1){
            //why its reversed ?
            //if it works don't fix it
                for(int  j=pindex[i];j>=0;j--){
                    new_vec[pos]= at(i,j);
                    pos++;
                }
            }
        }
        delete[]vec;vec=NULL;
        vec=new_vec;
        set_at_ptr(ltri) ;
}

}


template<typename DataType>
void matrix<DataType> ::compress_symmetric(void){
//first dimensions
    if(!is_compressed&&matrix_type==symmetric){
        is_compressed=true;
        //mapping in here
        //size of acutall data in the matrix
        int  size = (rows*(rows+1))/2 ;
        //filling data
        DataType*new_vec =  get_vec<DataType>(size,1) ;
        acutal_size = size;
        int  pos = 0  ;
        for(int  i=  0 ;i<rows;i++){
            for(int  j=i;j<cols;j++){
                new_vec[pos] = at(i,j);
                pos++;
            }
        }
        delete[]vec ;
        vec= new_vec;

        set_at_ptr(symmetric) ;
    }
}

template<typename DataType>
void matrix<DataType> ::compress_anti_symmetric(void){
    matrix_type =symmetric;
    compress_symmetric() ;
    set_feature(anti_symmetric);
}


//here is the compression algorithm for each matrix type
//they are private so the public one is compress(int  matrix type)
//here row_start is filled and pindex aswell
//passed function must be one of those types with zeroes
template<typename DataType>
void matrix<DataType> ::compress_diagonal(void){
    //first dimensions
    if(!is_compressed&&matrix_type==diagonal){
        is_compressed=true;
        acutal_size=rows;
        //mapping in here
        //size of acutall data in the matrix
        //filling data
        DataType*new_vec =  get_vec<DataType>(rows,1) ;
        for(int  i=  0 ;i<rows;i++){
            new_vec[i] = at(i,i);
        }
        empty_vec[0]=0;
        delete[]vec;
        vec= new_vec;
        set_at_ptr(diagonal);
    }
}


template<typename DataType>
void matrix<DataType>::compress_identity(void){
    //first dimensions
    if(!is_compressed &&matrix_type==iden){
        is_compressed=true;
        acutal_size = 1;
        matrix_type =  iden ;
        //mapping in here
        //size of acutall data in the matrix
        //filling data
        delete[]vec;
        vec =  get_vec<DataType>(1,1) ;
        vec[0] =1;
        empty_vec[0] = 0;

        set_at_ptr(iden) ;

    }
}
template<typename DataType>
void matrix<DataType>::compress_const(void){
    if(!is_compressed&&matrix_type==constant){
        //first dimensions
        is_compressed=true;
        acutal_size= 1;
        matrix_type =  constant ;
        //mapping in here
        //size of acutall data in the matrix
        //filling data
        DataType val = vec[0] ;
        delete[]vec;
        vec =  get_vec<DataType>(1,1) ;
        vec[0] =val;
        empty_vec[0]=0;
        set_at_ptr(constant) ;
    }
}

template<typename DataType>
void matrix<DataType> ::compress(void){
    if(matrix_type==general){
        fill_features() ;
    }
    if(!is_compressed){
        switch(matrix_type){
            case symmetric:
                compress_symmetric() ;break;
            case anti_symmetric:
                compress_anti_symmetric() ;break;
            case utri:
                compress_utri();break;
            case ltri :
                compress_ltri() ;break;
            case iden:
                compress_identity() ;break;
            case constant :
                compress_const() ;break;
            case diagonal :
                compress_diagonal() ;break;
        }
    }

}


    //used for matrices that aren't compressed
    //and u want to extract pivots locations
    template<typename DataType>
    matrix<int > matrix<DataType>::get_pindex(void){
        if(pindex==NULL){
            pindex=  get_vec<int >(rows,1) ;
            fill_vec<int >(pindex,rows,-1) ;
        }
        if(matrix_type==utri){
            for(int  i=0;i<rows;i++){
                for(int  j =i ; j<cols; j++){
                    if(at(i,j)>check_tolerance){
                        pindex[i]=j ;
                        break;
                    }
                }
            }
            return matrix<int >(rows,1,pindex,rows)  ;
        }
        else if(matrix_type==ltri){
            for(int  i=rows-1;i>=0;i--){
                for(int  j =i ; j>=0; j--){
                    if(at(i,j)>check_tolerance){
                        pindex[i]=j ;
                        break;
                    }
                }
            }
        return matrix<int >(rows,1,pindex,rows)  ;
        }
        else{
            matrix<int >pivots_indices;
            gauss_down(&pivots_indices) ;
            for(int  i = 0;i<rows;i++){
                pindex[i]=pivots_indices.at(i,0) ;
            }
            return pivots_indices;
        }
    }


    //fill the matrix with its features if its symmetric
    //utri,ltri ,etc
    //check_tol is same as tolerance or check_tolerance
    //for zero or difference like if 1e-6 is zero for the user
    //then the matrix fills the features accordingly
    //by default 1e-6
    //this doesn't check for orthogonality so use is_orthonormal
    template<typename DataType>
    void matrix<DataType>::fill_features(double check_tol){
        /*
        is_utri,is_ltri,is_identity,is_symmetric,is_anti_symmetric
        is_constant,is_orthonormal
        this method also fills pindex

        -if symmetric then it has a probablitiy to be constant
        or diagonal or identity
        -if utri then it has a probability to be diagonal or identity
        -if ltri then it has a probability to be diagonal or identity
        -sadly orthonormal is the least efficient check
        symmetric matrices are common in applications so its checked first
        if its symmetric to check if its constant we just run through main diagonal
            to check if diagonal if symmetric we run utri only
                when running through main diagonal check if its 1 so by now its identity
        */
        matrix_type=general;
        //we walk through each element with an array of bools
        //each representing a feature
        //enum{general=0,utri,ltri,diagonal,symmetric,anti_symmetric,constant,iden,orthonormal};
        bool features_arr[8] ;
        for(int  i =0 ; i<8;i++){
           features_arr[i]=true;
        }
        //used to save processing time if 4 features realated to
        //the upper part of the matrix then cut the search at this area
        DataType val = at(0,0) ;
        bool utri_search =true,ltri_search =true;
        for(int  i=0;i<get_rows()&&(utri_search||ltri_search);i++){
        if(ltri_search){//if there is a chance
            for(int  j= i+1; j<get_cols();j++){
                //utri or symmtery or diagonality or constant
                if(features_arr[ltri-1]&&abs(at(i,j))>check_tol){
                    features_arr[ltri-1]=false;
                    features_arr[diagonal-1]=false;
                    features_arr[iden-1]= false;
                }
                if(features_arr[symmetric-1]&&abs(at(i,j)-at(j,i))>check_tol){
                    features_arr[symmetric-1]=false;
                    features_arr[constant-1]=false;
                    features_arr[iden-1]= false;
                    features_arr[constant-1]=false;
                }
                if(features_arr[constant-1]&&abs(at(i,j)-val)>check_tolerance){
                    features_arr[constant-1]=false;
                }
                if(features_arr[anti_symmetric-1]&&abs(at(i,j)-at(j,i)*DataType(-1))>check_tol){
                    features_arr[anti_symmetric-1]= false ;
                }
            }
            ltri_search= features_arr[ltri-1]||features_arr[symmetric-1]||features_arr[anti_symmetric-1];
            }
            if(utri_search){
                for(int  j= 0; j<i;j++){
                    if(features_arr[utri-1]&&abs(at(i,j))>tolerance){
                        features_arr[utri-1] = false;
                        }
                    if(features_arr[constant-1]&&abs(at(i,j)-val)>check_tolerance){
                        features_arr[constant-1]=false;
                    }
                    }
                    utri_search = features_arr[utri-1]||features_arr[constant-1] ;
                }
            }
        //now we obtained all the info we need efficiently
        if(features_arr[utri-1]){
            if(features_arr[ltri-1]){
                for(int  i = 0 ;i<rows;i++){
                    if(abs(at(i,i)-DataType(1))>check_tol){
                        matrix_type= diagonal;
                        break;
                    }
                }
                matrix_type=(matrix_type==diagonal)?diagonal:iden ;
            }
            else{
                matrix_type= utri;
            }
        }
        else if(features_arr[symmetric-1]){
            if(features_arr[constant-1]){
                matrix_type =constant;
            }
            else{
                matrix_type=symmetric ;
            }
        }
        else if(features_arr[ltri-1]){
            matrix_type=ltri;
        }
        else if(features_arr[anti_symmetric-1]){
            matrix_type=anti_symmetric;
        }
    }

    template<typename DataType>
    void matrix<DataType>::decompress(void) {
        if(is_compressed){
            is_compressed= false;
            acutal_size= rows*cols;
            DataType *new_vec = get_vec<DataType>(rows,cols);
            for(int i = 0 ;i<rows;i++){
                for(int j= 0 ; j<cols;j++){
                    new_vec[i*cols+j] = at(i,j) ;
                }
            }
            delete[]vec;
            vec=new_vec;
            set_at_ptr(general);
        }
    }


    
