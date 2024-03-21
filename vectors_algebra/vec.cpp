#include "vec.h"
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
    //mat.copy(mat_src) ->mat = mat_src
    //we only fix vector and its void
    //then do copying mechanism
    for(int i =0 ; i <rows; i++){
        for(int j = 0 ; j<cols ; j++){
            if(abs(mat.vec[i][j])>=tolerance){
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
    if(rows ==mat.cols){
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

bool matrix ::is_symmetric(void)const{
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
                if (i != j &&vec[i][j]!= 0) {
                    return false;
                }
            else{
                //zero flag checks for diagonal elements so that it makes sure they aren't all zeroes
                zero_flag &=vec[i][j]==0;
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

bool matrix ::is_perp(matrix&mat) {
    return abs(theta(mat)-90)<=tolerance ;
}

bool matrix :: is_parallel(matrix&mat){
    return  abs(theta(mat))<=tolerance||abs(theta(mat)-180)<=tolerance ;
}

bool matrix ::operator == (matrix&mat)const{
    if(same_shape(mat)){
       for (int i = 0; i < rows; i++){
            for (int j = 0; j <cols; j++) {
             if(vec[i][j]!=mat.vec[i][j]){
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

matrix matrix ::utri(void) {
        matrix ret_mat =*this;
        for(int up_r = 0;up_r<rows-1; up_r++){
            for(int low_r = up_r+1; low_r<rows; low_r++){
                //check first if upper element is not zero
                if(ret_mat.vec[up_r][up_r]==0){
                    //switch the rows
                    ret_mat.switch_rows(up_r,low_r);
                }
                else{
                    float c = -1*(ret_mat.vec[low_r][up_r]/ret_mat.vec[up_r][up_r]);
                    for(int i =0 ; i<cols;i++){
                        ret_mat.vec[low_r][i]+=c*ret_mat.vec[up_r][i] ;
                    }
                }
            }
        }
        return ret_mat ;
}

matrix matrix ::ltri(void){
    matrix ret_mat = *this ;
    for(int low_r = rows-1 ; low_r>0;low_r--){
        for(int up_r = low_r-1;up_r>=0;up_r--){
            if(ret_mat.vec[low_r][low_r]!=0){
                float c = -1 * (ret_mat.vec[up_r][low_r] /ret_mat.vec[low_r][low_r]);
                    for(int col_c = 0 ; col_c<cols ; col_c++){
                        ret_mat.vec[up_r][col_c]+= c*ret_mat.vec[low_r][col_c];
                    }
            }
            else{
                //switch the rows
                ret_mat.switch_rows(up_r,low_r);
            }
        }
    }
    return ret_mat ;
}


/*
matrix* matrix::lower_fact(void){
matrix*ret_mat = new matrix() ;
ret_mat->identity() ;
    for(int  = get_rows()-1 ; row_counter>0; row_counter--){
        //for each row
        for(int low_row_counter=row_counter-1;low_row_counter>=0;low_row_counter--){
            //do -1*(arr[i+1,i]/arr[i,i])
           if(vec[get_index(row_counter,row_counter,get_cols())]!=0){
            float scalar = (vec[get_index(low_row_counter,row_counter,get_cols())]
                            /vec[get_index(row_counter,row_counter,get_cols())])*-1;
            ret_mat->vec[get_index(low_row_counter,)];
        for(int col_counter =0 ; col_counter<get_cols();col_counter++){
        vec[get_index(lower_row,col_counter,get_cols())]+= vec[get_index(upper_row,col_counter,get_cols())]*scalar;
        }
            }


        }
    }
}
matrix* matrix::upper_fact(void){
matrix*ret_mat = new matrix() ;
ret_mat->identity() ;
    for(int col_counter = 0 ; col_counter<get_cols()-1; col_counter++){
        //for each row
        for(int low_row_counter=row_counter-1;low_row_counter>=0;low_row_counter--){
            //do -1*(arr[i+1,i]/arr[i,i])
           if(vec[get_index(row_counter,row_counter,get_cols())]!=0){
            float scalar = (vec[get_index(low_row_counter,row_counter,get_cols())]
                            /vec[get_index(row_counter,row_counter,get_cols())])*-1;
            ret_mat->vec[get_index(low_row_counter,)];
        for(int col_counter =0 ; col_counter<get_cols();col_counter++){
        vec[get_index(lower_row,col_counter,get_cols())]+= vec[get_index(upper_row,col_counter,get_cols())]*scalar;
            }
         }


    }
    }

}
void matrix ::lu_fact(matrix**l,matrix**u){
//create 2 new matrices
matrix * ret_l = new matrix();
matrix * ret_u =new matrix();
//both are identity
ret_l->identity(get_rows()) ;
ret_u->identity(get_rows()) ;
}
*/
bool matrix ::switch_rows(int r1 ,int r2 ){
    if(r1>=0&&r1<get_rows()&&r2>=0&&r2<get_rows()){
    for(int i = 0 ; i <get_cols();i++){
        swap(vec[r1][i],vec[r2][i]);
    }
    return true ;
}
    return false  ;
}

float matrix:: back_sub(int row_index,matrix&sol_mat){
    float sum  = vec[row_index][get_cols()-1];
    for(int col_counter = row_index+1  ;col_counter<get_cols()-1; col_counter++){
        sum-=vec[row_index][col_counter]*sol_mat.vec[col_counter][0];
    }
    return sum/vec[row_index][row_index] ;
}

float matrix:: fwd_sub(int row_index,matrix&sol_mat){
    float sum  = vec[row_index][get_cols()-1];
    for(int col_counter = 0  ;col_counter<row_index;col_counter++){
        sum-=vec[row_index][col_counter]*sol_mat.vec[col_counter][0];
    }
    return sum/vec[row_index][row_index] ;
}

//pass an appended matrix
matrix matrix:: solve(void) {
    //turns the system into uppertriangular system
    matrix mat_cpy=utri();
    //the new matrix in which the answer will be returned
    matrix sol_mat(get_rows(),1,0) ;
    for(int i = get_rows()-1; i>=0;i--){
        sol_mat.vec[i][0] = mat_cpy.back_sub(i,sol_mat) ;
    }
    return sol_mat ;
}

float matrix::det(){
    if(is_square()){
        matrix mat_cpy =utri();
        float det_val = 1 ;
        for(int i =0 ; i <rows; i++){
            det_val*=mat_cpy.vec[i][i]  ;
        }
        return det_val ;
}
    cout<<square_error ;
    return -1 ;
}

float& matrix ::at(int r_ind,int c_ind){
    if(r_ind>=0&&r_ind<rows&&c_ind>=0&&c_ind<cols){
        return vec[r_ind][c_ind] ;
    }
    cout<<"out of bounds";
}

matrix matrix ::inverse(void){
    if(is_square()&&det()!=0){
        //copying the m matrix into mat_cpy
        matrix mat_cpy =*this ;
        //creating return matrix which at first will be identity
        matrix ret_mat(rows,cols) ;
        ret_mat.identity() ;
        //first do Gaussian elimination downward
        for(int up_r = 0 ; up_r<rows-1;up_r++){
                for(int low_r = up_r+1;low_r<rows;low_r++){
                    float c = -1 * (mat_cpy.vec[low_r][up_r]/mat_cpy.vec[up_r][up_r]);
                    for(int col_c = 0 ; col_c<cols ; col_c++){
                        mat_cpy.vec[low_r][col_c]+= c*mat_cpy.vec[up_r][col_c] ;
                        ret_mat.vec[low_r][col_c] += c*ret_mat.vec[up_r][col_c];
                    }
                }
            }
        //then do Gaussian elimination upward
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
    cout<<"determinant of the passed matrix is zero or not squre matrix to begin with";
    matrix error_matrix(1,1,-1);
    return error_matrix ;
}

matrix matrix::operator/(matrix& m)const
{
    if(m.det()!=0){
        matrix ret_mat = m.inverse() ;
        return *this * ret_mat;
    }
        cout<<"determinant of the denum is zero";
        matrix error_matrix(1,1,-1);
        return error_matrix ;
}
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
            //reallocate for copying
            rows = mat.rows;
            cols = mat.cols ;
            vec= get_vec(mat.get_rows(),mat.get_cols()) ;
        }
        //copying mechanism
        for(int i = 0 ; i <rows;i++){
            for(int j= 0 ; j<cols ;j++){
                vec[i][j] = mat.vec[i][j] ;
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

bool matrix::is_upper_tri(void) {
    if(is_square()){
     bool zero_flag= true ;
        for(int i =0 ; i <rows;i++){
            for(int j=  0 ; j<cols; j++){
                if(j<i){
                    if(vec[i][j]!=0){
                        return false ;
                    }
                }
                else{
                    //check for rest of elements so that they aren't all zeroes
                    zero_flag&=(vec[i][j]!=0)?false:true ;
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
                if(vec[i][j]!=0){
                    return false ;
                }
            }
            else{
                //check for rest of elements so that they aren't all zeroes
                zero_flag&=(vec[i][j]!=0)?false:true ;
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
//first check if its a square matrix
    if(is_square()){
        //first perform gaussian elimination downward
        matrix temp_mat = utri() ;
        int counter = 0;
        //then count number of rows that has atleast one non zero element
        for(int i = 0 ; i<rows; i++){
            //since its upper triangular matrix
            //no need to check for all elements from 0 to cols for each row
            //so for first row we check from zero
            //and for 2nd row we check from 1 and so on and so forth
            //we check for elements from 0 index else from i+1
            for(int j =i; j<cols ; j++){
                if(abs(temp_mat.vec[i][j])>tolerance){
                    counter++;
                    break  ;
                }
            }
        }
        return counter ;
    }
    cout<<square_error ;
    return -1 ;
}//tested
