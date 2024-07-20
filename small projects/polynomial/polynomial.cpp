#include "polynomial.h"

/*


private:
    int exp;
    double coef;
    Node* next;
    friend class Polynomial;  Allow Polynomial Access

*/
float tol = 0.00001 ;
void Polynomial::del_poly(void){

while(head->next){
    Node*temp = head;
    head= head->next ;
    delete temp;
}
head->coef=  0 ;
head->exp =  0 ;
}
void Polynomial:: operator = (const Polynomial &p){
//delete old list and reinitialize it with new data
del_poly() ;
Node *src = p.head ;
while(src){
    add_term(src->coef,src->exp) ;
    src = src->next ;
}
}
Node *get_node(double c,int e ){
    Node *new_node = new Node ;
    new_node->exp =e ;
    new_node->coef = c ;
    new_node->next = NULL ;
    return new_node ;
}
Polynomial::Polynomial(Node* h){
head = new Node ;
if(h){
    head->coef =h->coef;
    head->exp = h->exp;
    }
    else{
    head->coef =0;
    head->exp = 0;
    }
head->next = NULL ;
}


Polynomial::Polynomial(const Polynomial& p)
{
    head = get_node(p.head->coef,p.head->exp) ;
    Node *ptr1 = head;
    Node *ptr2 = p.head;
     while(ptr2->next){
        ptr2 =ptr2->next ;
        ptr1->next = get_node(ptr2->coef,ptr2->exp) ;
        ptr1= ptr1->next ;
     }

}

Polynomial::~Polynomial()
{
while(head){
    Node*temp = head;
    head= head->next ;
    delete temp;
}
}

void Polynomial::print() const
{
if(head){
    Node*ptr= head ;
    cout<<endl<<head->coef;
    if(ptr->exp>tol){
        cout<<"X^"<<ptr->exp ;
    }
    ptr=ptr->next ;
    while(ptr){
        if(ptr->coef>tol){
            cout<<" + ";
        }
        else{
            cout<<" - " ;
        }
        cout<<abs(ptr->coef);
        if(ptr->exp!=0){
            cout<<"X^"<<ptr->exp ;
        }
        ptr=ptr->next ;
    }
}
}

void Polynomial::add_term(const double& c, const int& e)
{
//if its a zero element no need to add it
if(c!=0){
    //if head is 0 initialize it
    if(head->coef<tol&&head->exp==0){
        head->coef= c ;
        head->exp =e ;
    }
else{
    //creating new node
    Node *new_node =get_node(c,e);
    //sorting while insertion
    //if exp is bigger than biggest exponent
    //we add it at beginning
    if(e>head->exp){
        new_node->next = head;
        head=  new_node ;
    }
    else if(e==head->exp){
        head->coef+=c;
        if(head->coef<tol){
            if(head->next!=NULL){
                Node*temp = head ;
                head=head->next;
                delete temp ;
                delete new_node ;
            }
            else{
                head->exp=  0  ; head->coef = 0 ;
                delete new_node ;
            }
        }
    }

    else{
        Node *ptr = head  ;
        //keep moving while e < exp of next element
        while(ptr->next&&e<ptr->next->exp){
            ptr = ptr->next ;
        }
        //if we are still in the list
        if(ptr->next){
            //if exp is same then we just add coef
            if(e==ptr->next->exp){
                ptr->next->coef+=c ;
                //if the coef is zero then we delete next element
                if(ptr->next->coef<tol){
                    Node*temp = ptr->next;
                    ptr->next =temp->next ;
                    delete temp ;
                }
                delete new_node ;
            }
            else{
                //add it normally
                new_node->next = ptr->next ;
                ptr->next = new_node ;
            }
        }
        else{
            //last element then
            ptr->next = new_node ;
        }
    }
    }
}
}

Polynomial Polynomial::p_copy() const
{
    Polynomial ret_poly = *this ;
    return ret_poly ;
}

void Polynomial::remove_term(const int& e)
{
if(e==head->exp){
    head= head->next ;
    Node *temp = head;
    delete temp ;
}
else{
    Node*ptr = head ;
    while(ptr->next){
        if(ptr->next->exp==e){
            Node*temp = ptr->next ;
            ptr->next = ptr->next->next ;
            delete temp ;
            return ;
        }
        ptr=ptr->next ;
    }
}
}

double Polynomial::poly_val(const double& x) const
{
    double ret_val = 0;
    Node *ptr =head ;
    while(ptr){
        ret_val+=ptr->coef*pow(x,ptr->exp);
        ptr= ptr->next;
    }
    return ret_val ;
}

Polynomial Polynomial::mul_term(const double& c, const int& e) const
{
Polynomial ret_poly;
Node *ptr = head ;
while(ptr){
    ret_poly.add_term(ptr->coef*c,ptr->exp+e);
    ptr = ptr->next ;
}
return ret_poly ;
}

bool Polynomial::operator==(const Polynomial& p) const
{
Node *ptr = head ;
Node *ptr2=p.head;
while(ptr&&ptr2){
    if(ptr->exp!=ptr2->exp||ptr->coef!=ptr2->coef){
        return false ;
    }
    ptr= ptr->next ; ptr2=ptr2->next ;
}
return(ptr==NULL&&ptr2==NULL);
}

bool Polynomial::operator!=(const Polynomial& p) const
{

Node*ptr = head ;
Node *ptr2=p.head;
while(ptr&&ptr2){
    if(ptr->exp!=ptr2->exp||ptr->coef!=ptr2->coef){
        return true ;
    }
    ptr= ptr->next ; ptr2=ptr2->next ;
}
return!(ptr==NULL&&ptr2==NULL);
}

Polynomial Polynomial::operator + (const Polynomial& p) const
{
    Polynomial ret_poly = *this ;
    Node*ptr =p.head ;
    while(ptr!=NULL){
        ret_poly.add_term(ptr->coef,ptr->exp) ;
        ptr=  ptr->next ;
    }
    return ret_poly;
}

Polynomial Polynomial::operator - (const Polynomial& p) const
{
    Polynomial ret_poly = *this ;
    Node*ptr =p.head ;
    while(ptr!=NULL){
        ret_poly.add_term(-1*ptr->coef,ptr->exp) ;
        ptr=  ptr->next ;
    }
    return ret_poly  ;
}

Polynomial Polynomial::operator * (const Polynomial& p) const // complexity
{
Polynomial ret_poly ;
Node*ptr = p.head ;
while(ptr){
    ret_poly = ret_poly+mul_term(ptr->coef,ptr->exp) ;
    ptr = ptr->next ;
}
return ret_poly ;
}

Polynomial Polynomial::operator / (const Polynomial& divisor) const
{
if(divisor.head->coef>tol){
Polynomial poly_cpy = *this ;

Polynomial ret_poly ;
Node *pdiv = divisor.head;
Node *ptr = poly_cpy.head;
while(ptr->coef!=0&&ptr->exp>=pdiv->exp){
    double c = ptr->coef/pdiv->coef;
    int e    = ptr->exp-pdiv->exp;
    ret_poly.add_term(c,e) ;
    Polynomial sub =divisor.mul_term(c,e) ;
    poly_cpy = poly_cpy-sub ;
    ptr = poly_cpy.head ;
}

return ret_poly  ;
}
return Polynomial(NULL) ;
}

Polynomial Polynomial::operator % (const Polynomial& divisor) const
{
if(divisor.head->coef>tol){
Polynomial poly_cpy = *this ;

Polynomial ret_poly ;
Node *pdiv = divisor.head;
Node *ptr = poly_cpy.head;
while(ptr->coef!=0&&ptr->exp>=pdiv->exp){
    double c = ptr->coef/pdiv->coef;
    int e    = ptr->exp-pdiv->exp;
    ret_poly.add_term(c,e) ;
    Polynomial sub =divisor.mul_term(c,e) ;
    poly_cpy = poly_cpy-sub ;
    ptr = poly_cpy.head ;
}

return poly_cpy  ;
}
return Polynomial(NULL) ;
}

Polynomial Polynomial::differentiate () const
{
    Polynomial ret_poly ;
    Node*ptr = head ;
    while(ptr){
        if(ptr->exp!=0){
            ret_poly.add_term(ptr->coef*ptr->exp,ptr->exp-1) ;
        }
        ptr= ptr->next ;
    }
    return ret_poly ;
}

Polynomial Polynomial::integrate () const
{
    Polynomial ret_poly ;
    Node*ptr = head ;
    while(ptr){
        ptr->exp+=1 ;
        ret_poly.add_term(ptr->coef/(ptr->exp),ptr->exp) ;
        ptr= ptr->next ;
    }
    return ret_poly   ;
}
