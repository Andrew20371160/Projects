    #include "tv_receiver.h"

    doubly_list ::doubly_list(){
        tail = NULL;
        ch_count = 0;
    }

    doubly_list ::doubly_list(node*data_set,unsigned int size){
        tail=NULL ;
        if(data_set){
            ch_count=  size ;
            for(unsigned int i =0 ; i<size; i++){
                add_at_end(data_set[i].ch_name) ;
            }
        }
    }
    doubly_list ::~ doubly_list (){
        while(tail){
            del_at_beg();
        }
    }
    node* doubly_list::get_tail(void){
        return tail ;
    }
    unsigned int doubly_list::get_count(){
        return ch_count ;
    }
//allocate memory for a new node (channel)
node * doubly_list ::get_node(unsigned int ch_number ,string & name ){
    node * new_node = new node ;
    new_node->ch_num = ch_number ;
    new_node->ch_name =name ;
    new_node->next = new_node ;
    new_node->prev = new_node  ;
    ch_count++ ;
    return new_node ;
}

void doubly_list ::add_at_end(string&name){
    if(tail ==NULL){
        tail = get_node(ch_count+1,name) ;
    }
    else {
    node * new_node =get_node(ch_count+1,name) ;
    new_node->prev = tail ;
    new_node->next = tail->next ;
    tail->next->prev = new_node ;
    tail->next = new_node ;
    tail = new_node ;
    }
}

void doubly_list :: add_at_beg(string& name){
    if(tail ==NULL){
        tail = get_node(1,name) ;
    }
    else {
       node * new_node = get_node(1,name) ;
       new_node->next = tail->next ;
       new_node->prev = tail;
       tail->next->prev = new_node;
       tail->next = new_node;
       inc_from(new_node->next,0);
    }
}
void doubly_list ::inc_from(node*starting_ptr,bool decrement =false){
    if(starting_ptr){
        node*ptr = starting_ptr;
        if(decrement){
            do{
                ptr->ch_num-- ;
                ptr=ptr->next;
            }while(ptr!=tail->next) ;
        }
        else{
            do{
                ptr->ch_num++ ;
                ptr=ptr->next;
            }while(ptr!=tail->next) ;
    }
}
}
node * doubly_list ::search(unsigned int ch_num ){
    if(ch_num<1||ch_num>ch_count){
        cout<<"\n denied ";
        return NULL;
    }
    node  * ptr = tail->next;
    do{
        if(ptr->ch_num==ch_num){
            return ptr ;
        }
        ptr= ptr->next ;
     }while(ptr!=tail->next) ;

    return NULL ;
}

void doubly_list :: show(){
    cout<<endl ;
    if(tail){
        node * ptr = tail->next ;
        do{
            cout<<"Channel : "<<ptr->ch_num<<" "<<ptr->ch_name<<endl;
            ptr =ptr->next ;
        }while(ptr !=tail->next ) ;
    }
}

void doubly_list ::add_at_pos(unsigned int pos,string&name){

    if(pos<=0 || pos>ch_count+1){
        cout<<endl<<"denied ";
    }
    else if(pos ==1){
        add_at_beg(name) ;
    }
    else if (pos ==ch_count+1){
        add_at_end(name) ;
    }
    else {
       node *new_node = get_node(pos,name) ;
       node*ptr = tail->next;
       while(ptr->ch_num!=pos){
            ptr=ptr->next;
       }
       new_node->next=ptr;
       new_node->prev=ptr->prev ;
       ptr->prev->next= new_node;
       ptr->prev= new_node;
    }

}

void doubly_list ::del_at_beg(){

    if(tail){
        if(tail->next==tail){
            delete tail ;
            tail = NULL ;
        }
        else {
            node * temp  = tail->next ;
            tail->next = temp->next;
            temp->next->prev = tail ;
            delete temp ;
            temp = NULL ;
            inc_from(tail->next,1) ;
        }
        ch_count--;
    }
}
void doubly_list ::del_at_end(){
    if(tail){
        if(tail->next==tail){
            delete tail ;
            tail = NULL ;
        }
        else {
            node * temp = tail ;

            tail = tail ->prev ;

            tail->next = temp->next ;

            temp->next->prev = tail ;
            delete temp ;
            temp = NULL ;
        }
        ch_count-- ;
    }
}
void doubly_list ::del_at_pos(unsigned int pos ){
    if(pos<=0 || pos >ch_count){
        cout<<endl<<"denied ";
    }
    else if(pos ==1){
       del_at_beg() ;
    }
    else if (pos ==ch_count+1){
        del_at_end() ;
    }
    else {
        node*ptr = tail->next ;
        while(ptr->ch_num!=pos){
            ptr=ptr->next ;
        }
        ptr->prev->next= ptr->next;
        ptr->next->prev = ptr->prev;
        inc_from(ptr->next,1) ;
        delete ptr ;
        ptr = NULL ;
        ch_count-- ;
    }
}

void doubly_list::del_all(){
    while(tail!=NULL){
        del_at_beg() ;
    }
}
void doubly_list :: switch_nodes(node * ptr1 , node * ptr2 ){
    if(ptr1&&ptr2){
        if(ptr1==tail){
            tail = ptr2 ;
        }
        if(ptr2==tail){
            tail= ptr1 ;
        }
        //adjust nodes links before and after ptr1
        ptr1->prev->next = ptr2 ;
        ptr1->next->prev = ptr2;
        //adjust nodes links before and after ptr2
        ptr2->prev->next= ptr1 ;
        ptr2->next->prev= ptr1 ;
        //save location of ptr1->next and ptr1->next

        node*pn = ptr1->next ;
        node*pp = ptr1->prev;
        //adjust ptr1 links
        ptr1->next = ptr2->next ;
        ptr1->prev = ptr2->prev ;
        //adjust ptr2 links using previous locations of links
        ptr2->next = pn ;
        ptr2->prev = pp ;
    }
}
void doubly_list ::sort() {
    if(tail ==NULL||tail->next ==tail ){
        cout<<"not enough channels to sort " ;
    }
    else{
        node * ptr1 = tail->next ;
        node * ptr2 = ptr1->next ;
        do{
            do{
                if(ptr1->ch_name>ptr2->ch_name){
                    swap(ptr1->ch_name,ptr2->ch_name) ;
                }
                    ptr2 = ptr2->next ;
            }while(ptr2!=tail->next);

            ptr1= ptr1->next;
            ptr2= ptr1->next ;
        }while(ptr1!=tail);
}
}

    receiver::receiver():doubly_list(){
        string empty_ch="Empty receiver";
        doubly_list::add_at_beg(empty_ch);
        channel_ptr = tail;
        empty_receiver =true ;
    }

    receiver ::receiver(node*data_set,unsigned int size):doubly_list(data_set,size){
        channel_ptr = tail->next ;
        empty_receiver =false;
    }

    receiver ::~receiver(void){
        doubly_list::del_all();
    }
    void receiver ::operator++(void){
        channel_ptr=channel_ptr->next ;
    }
    void receiver ::operator--(void){
        channel_ptr=channel_ptr->prev ;
    }

    void receiver::show_cur(void){
        cout<<"channel number : "<<channel_ptr->ch_num<<setw(280)<<channel_ptr->ch_name <<endl;
    }
    void receiver ::change_location(void){
        if(!is_empty()){
            unsigned int n1 ,n2 ;
            node *c1 ,*c2 ;
            cout<<"\n enter channel number " ; cin>>n1 ;
            cout<<"\n enter the other channel number ";cin>>n2;
            if(n1==n2){
                cout<<"\n denied";
            }
            else{
                c1= search(n1) ;
                c2= search(n2) ;
                swap(c1->ch_name,c2->ch_name) ;
            }
    }
    }
    bool receiver ::is_empty(void){
        return empty_receiver==true ;
        }
    void receiver ::helper(void){
        cout<<"\n a--add a channel \n ";
        cout<<"(w/s)--to transfer \n ";
        cout<<"d--delete the current channel ";
        cout<<"\n c--change channel location \n";
        cout<<"n--transfer to a channel through unsigned integers \n ";
        cout<<"x--delete all channels ";
        cout<<"\n r--sort channels by alphabetical order\n ";
        cout<<"g--show all channels \n ";
        cout<<"q--quit";
    }

    void receiver ::get_to(void){
        if(!is_empty()){
            unsigned int n ;
            cout<<"\n enter channel's number ";
            cin>>n ;
            node*ptr =search(n);
            if(ptr){
                channel_ptr =ptr ;
            }
            else{
                cout<<"Not found";
            }
        }
    }
    void receiver ::del_cur(void){
        if(!is_empty()){
            if(ch_count==1){
                channel_ptr->ch_name = "\nEmpty receiver";
                empty_receiver=true ;
            }
            else{
                if(channel_ptr==tail->next){
                    del_at_beg() ;
                }
                else if(channel_ptr==tail){
                    del_at_end() ;
                }
                else{
                    channel_ptr->prev->next = channel_ptr->next;
                    channel_ptr->next->prev = channel_ptr->prev;
                    delete channel_ptr  ;
                }
                    channel_ptr = tail->next ;
            }
            }
    }
    void receiver ::del_all(void){
        doubly_list::del_all() ;
        string empty_str ="\nEmpty receiver";
        add_at_beg(empty_str);
        channel_ptr = tail ;
        empty_receiver =true ;
    }
    void receiver ::sort(void){
        doubly_list::sort() ;
    }
    void receiver ::show(void){
        doubly_list::show() ;
    }
    void receiver::add(){
        if(is_empty()){
            cout<<"\n enter the channel name ";
            cin>>channel_ptr->ch_name ;
            empty_receiver = false ;
        }
        else{
            string name ="";
            cout<<"\n enter the channel name ";
            cin>>name;
            add_at_end(name) ;
        }
    }
    void receiver:: del_at_pos(void){
        if(!is_empty()){
            if(ch_count>1){
                unsigned int ch_n ;
                cout<<"\nEnter the channel's number";
                cin>>ch_n ;
                if(ch_n==channel_ptr->ch_num){
                    channel_ptr=tail->next;
                }
                doubly_list::del_at_pos(ch_n) ;
        }
        else{
            channel_ptr ->ch_name = "Empty receiver" ;
            empty_receiver=true ;
        }
    }
    }
int main()
{
    receiver rec ;
    cout<<setw(300)<<"Loading";
    cout<<endl;
    system("pause") ;
    char ch ;
    cout<<"\n press 'h' for help" ;
    while(1){
        rec.show_cur();
        ch= getch() ;
        switch(ch){
        case  'w' :  ++rec; break ;
        case  's':  --rec; break  ;
        case  'c':{
            rec.change_location() ;
        }break ;
        case 'g': rec.show() ;break  ;
        case 'd': rec.del_cur() ;break ;
        case 'x' : rec.del_all();break;
        case 'h': rec.helper();break ;
        case 'r' : rec.sort(); break ;
        case 'a' : rec.add();break ;
        case 'q' : cout<<"\n                                   Software made by : Andrew karam \n";
        system("pause");cout<<endl<<setw(300)<<"Loading";    exit(0) ;
        case 'n' :rec.get_to();break;
        default:{
            rec.show_cur();
        }

        }

    }
return 0;
}
