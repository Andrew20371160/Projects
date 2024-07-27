#include "logic_gates.h"
 // Function to open a file for writing
    bool openFileForWriting(const std::string& filePath) {
        std::ofstream file(filePath);
        if (!file) {
            return false;  // Failed to open the file
        }

        // File is now open for writing
        return true;
    }

    // Function to open a file for reading
    bool openFileForReading(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file) {
            return false;  // Failed to open the file
        }
        // File is now open for reading
        return true;
    }


    /*
    array of strings where each gate is mapped to its enum value
    */
    const int gate_count =8 ;

    const string gates[8] {"NOT","BUFFER","AND" ,"OR" ,"NOR" , "NAND" ,"XNOR","XOR"};

    void print_gates(int start= 0){
        for(int i = start ; i <gate_count ; i++){
            cout<<"\n("<<i<<":"<<gates[i]<<")";
        }
    }

    gate *graph::get_gate(short g_type,int in_size){

        if(in_size>0&&g_type>=NOT&&g_type<=XOR){
            //allocate memory
           gate *new_gate = new gate ;

            //set links to null
           new_gate->parent = NULL ;
           new_gate->next = NULL ;
           new_gate->prev = NULL ;
           new_gate->children =NULL ;

           new_gate->self_input=NULL ;

           new_gate->output = false ;

           //assign gate type and input size
           new_gate->gate_type = g_type ;
           if(new_gate->gate_type==NOT||new_gate->gate_type==BUFFER){
                new_gate->input_size = 1 ;
                new_gate->self_input = new bool[1] ;
                new_gate->self_input[0] = 0;

           }
           else{
               new_gate->input_size = in_size ;

               new_gate->self_input = new bool[in_size] ;
               for(int i = 0 ;  i<in_size;i++){
                    new_gate->self_input[i]  = 0  ;
                }
           }
            return new_gate  ;
        }
        return NULL ;
    }

    bool graph::is_leaf(gate*g){
        if(g){
           return g->children==NULL;
        }
        return  false ;
    }



    graph ::graph(void){
        root = NULL ;
        traverser=NULL;
        size = 0 ;
    }

   graph :: ~graph(void){
        remove_graph()  ;
        root=NULL ;
        traverser=NULL ;
        size=0 ;
   }


    void graph::edit_input_size(gate*ptr) {

         if(ptr&&is_leaf(ptr)){
            //if it's a gate other than not,buffer
            if(!(ptr->gate_type==NOT||ptr->gate_type==BUFFER)){

                cout<<"\n"<<gates[ptr->gate_type]<<" is a leaf gate and you must specify the number of input pins\n>>" ;

                if(ptr->self_input){
                    delete[]ptr->self_input ;
                    ptr->self_input=NULL;
                }

                //while user input is less than or equal to zero
                ptr->input_size =-1 ;
                while(ptr->input_size<=0){
                    cout<<"\nEnter No. of input pins\n>>" ;
                    cin>>ptr->input_size;
                }
                //allocate memory and initialize with zeroes
                ptr->self_input= new bool[ptr->input_size] ;
                for(int i =0;  i <ptr->input_size; i++){
                    ptr->self_input[i]=0;
                }
            }
            else{
                if(ptr->self_input==NULL){
                    ptr->self_input=new bool[1] ;
                    ptr->input_size =1 ;
                    ptr->self_input[0] = 0 ;
                }
            }
        }
    }

    bool graph::move(void)const{
        if(root){
            traverser=root;

            while(1){
                cout<<"\n"<<traverser->output;
                cout<<"\n|";
                cout<<"\n"<<gates[traverser->gate_type];
                cout<<"\n";
                if(traverser->children){
                    gate*trav = traverser->children ;
                    while(trav){
                        cout<<"| ";
                        trav=trav->next;
                    }
                    trav =traverser->children ;
                    cout<<endl ;
                    while(trav){
                        cout<<trav->output<<" ";
                        trav=trav->next;
                    }
                }
                else{
                    for(int i = 0 ;  i<traverser->input_size;i++){
                        cout<<"| ";
                    }
                    cout<<endl ;
                    for(int i = 0 ;  i<traverser->input_size;i++){
                        cout<<traverser->self_input[i]<<" ";
                    }
                }
                cout<<"\n>>";
                char input= getch() ;
                cout<<"\n(w:go up)\n(s:go down)\n(a:previous gate)\n(d:next gate)\n(enter:access gate)\n(r:go to root)\n(q:quit)\n>>" ;
                switch(input){
                    case 'w' :{
                        if(traverser->parent){
                            traverser=traverser->parent ;
                        }
                    }break;

                    case 's' :{
                        if(traverser->children){
                            traverser=traverser->children;
                        }
                    }break;

                    case 'a' :{
                        if(traverser->prev){
                            traverser= traverser->prev ;
                        }
                    }break;

                    case 'd' :{
                        if(traverser->next){
                            traverser= traverser->next;
                        }
                    }break;

                    case '\r' :{
                        return true;
                    }break;

                    case 'r':{
                        traverser=root ;
                    }break;

                    case 'q':{
                        traverser= root ;
                        return false;
                    }break ;
                }
            }
        }
        return false ;
    }

    void graph::print(void)const{

        if(root){
            queue<gate*>q ;
            q.push(root)  ;

            while(!q.empty()){
                gate*temp = q.front() ;
                q.pop() ;

                while(temp){
                    //if it has children push it
                    if(temp->children){
                        q.push(temp->children) ;
                    }
                    //and print the elements of the current list (level)
                    cout<<gates[temp->gate_type]<<" " ;
                    temp=temp->next;
                }
            }
        }
    }

    void graph::remove(void){
        if(root){
            if(move()){
                //if it's the root go right
                if(traverser==root){
                    root = root->next;
                }
                //if traverser is the head of the children list
                //update the head to point to right child
                if(traverser->parent){

                    traverser->parent->input_size--;

                    //if head of the children list is traverser
                    if(traverser->parent->children==traverser){
                        traverser->parent->children= traverser->next ;
                    }
                    //if last node or child is deleted
                    if(traverser->parent->children==NULL){
                        edit_input_size(traverser->parent) ;
                    }
                    traverser->parent=NULL;
                }

                if(traverser->next){
                    traverser->next->prev=traverser->prev;
                }
                if(traverser->prev){
                    traverser->prev->next  =traverser->next;
                }

                traverser->prev=NULL;
                traverser->next=NULL;

                remove_graph(traverser) ;
            }
        }
        traverser= root;
    }

    void graph::remove_graph(gate*ptr ){
        if(root){
           bool is_root=(ptr==root);// bool to check if root is deleted to update it to null after deletion
            queue<gate*>q ;

            if(ptr==NULL){
                q.push(root)  ;
                is_root=true ;
            }
            else{
                q.push(ptr) ;
            }

            while(!q.empty()){
                gate*temp = q.front() ;
                q.pop() ;
                //for every node in the current list
                while(temp){
                    //if it has children push it
                    if(temp->children){
                        q.push(temp->children) ;
                    }
                    //keep track of prev pointer
                    //and move temp to next ptr
                    gate* prev_temp = temp ;
                    temp=temp->next;
                    //then delete prev temp array of booleans (if exists)
                    if(prev_temp->self_input){
                        delete[]prev_temp->self_input ;
                        prev_temp->self_input=NULL ;
                    }
                    //then delete prev_temp and set it to null
                    delete prev_temp ;
                    size-- ;
                    prev_temp= NULL ;
                }
            }
            if(is_root){
                root=NULL ;
                traverser=NULL ;
            }
        }
    }

    void graph::append_right(short gate_type,int gate_size) {

        if(traverser->parent==NULL||!(traverser->parent->gate_type==NOT||traverser->parent->gate_type==BUFFER)){
            gate*new_gate = get_gate(gate_type,gate_size) ;
            //if allocation worked
            //link the links
            if(new_gate){
                size++;

                new_gate->prev = traverser ;
                new_gate->next= traverser->next ;

                if(traverser->next){
                    traverser->next->prev = new_gate;
                }

                traverser->next = new_gate ;

                new_gate->parent= traverser->parent ;

                if(new_gate->parent){
                    new_gate->parent->input_size++;
                }
            }
        }
    }
    bool graph::append_right(gate*component) {

        if(component&&traverser->parent==NULL||!(traverser->parent->gate_type==NOT||traverser->parent->gate_type==BUFFER)){
                size++;

                component->prev = traverser ;
                component->next= traverser->next ;

                if(traverser->next){
                    traverser->next->prev = component;
                }

                traverser->next = component ;

                component->parent= traverser->parent ;

                if(component->parent){
                    component->parent->input_size++;
                }
                return true  ;
            }
            else{
                return false;
            }
        }

    void graph::append_child(short gate_type,int gate_size) {
        //if it's first child
        if(traverser->children==NULL){
            //then parent or traverser was a leaf
            //so we delete allocated memory for the array of booleans
            if(traverser->self_input){
                delete[]traverser->self_input;
                traverser->self_input=NULL ;
                traverser->input_size= 0 ;
            }

            traverser->children= get_gate(gate_type,gate_size);

            if(traverser->children){
                traverser->children->parent=traverser ;
                size++;
                traverser->input_size++;
            }
        }
        else{
            //if the gate is "not" you can't put another input gate to it
            //short circuit
            if(!(traverser->gate_type==NOT||traverser->gate_type==BUFFER)){

                gate*new_gate= get_gate(gate_type,gate_size) ;

                if(new_gate){
                   size++ ;
                   gate*ptr = traverser->children;
                    //go to max right then append the new gate
                    while(ptr->next){
                        ptr = ptr->next ;
                    }
                    new_gate->prev= ptr;

                    new_gate->parent= ptr->parent;

                    ptr->next= new_gate ;

                    traverser->input_size++;
                    }
                }
            }
        }
    bool graph::append_child(gate*component) {
        //if it's first child
        if(component){
            if(traverser->children==NULL){
                //then parent or traverser was a leaf
                //so we delete allocated memory for the array of booleans
                if(traverser->self_input){
                    delete[]traverser->self_input;
                    traverser->self_input=NULL ;
                    traverser->input_size= 0 ;
                }

                traverser->children= component;

                if(traverser->children){
                    traverser->children->parent=traverser ;
                    size++;
                    traverser->input_size++;
                }
                                return true  ;

            }
            else{
                //if the gate is "not" you can't put another input gate to it
                //short circuit
                if(!(traverser->gate_type==NOT||traverser->gate_type==BUFFER)){

                       size++ ;
                       gate*ptr = traverser->children;
                        //go to max right then append the new gate
                        while(ptr->next){
                            ptr = ptr->next ;
                        }
                        component->prev= ptr;

                        component->parent= ptr->parent;

                        ptr->next= component ;

                        traverser->input_size++;
                        return true  ;

                    }
                    else{
                        return false;
                    }
                }
            }
        }

    void graph::insert(void){
        //specify gate type and input size
        //memory isn't allcated
        //untill you move() to the gate and append the new gate
        short gate_type ;
        cout<<"\nChoose gate type";

        print_gates(NOT);

        cin>>gate_type ;
        cin.ignore()  ;
        int gate_size ;
        cout<<"\nEnter size of the new gate(No. of input pins)";
        cin>>gate_size  ;
        //make sure it's within the range of gates
        if(gate_type>=NOT&&gate_type<=XOR&&gate_size>0){
            if(root==NULL){
                root = get_gate(gate_type,gate_size) ;
            }

        else{
            cout<<"\nMove to the gate where you want to insert the child either on the right or as an input to that gate\n" ;
            if(move()){
                int choice ;
                cout<<"\n(1:append gate to the right)\n(2:append gate as an input to the current gate)\n(3:quit)\n>>";
                cin>>choice ;
                if(choice==1||choice==2){
                    if(choice==1){
                        append_right(gate_type,gate_size);
                    }
                    else{
                        append_child(gate_type,gate_size);

                        }
                    }
                }
            }
        }
    }
    /*
    edit gate type or number of pins if it's a leaf gate
    if you want to remove a child gate then use remove
    */
    void graph:: edit(void){
        cout<<"\nNote : you can't change a gate type to NOT/BUFFER since NOT/BUFFER only has 1 input";
        if(move()){
            int choice = 0 ;
            cin.ignore() ;
            cout<<"\n(1:chage gate's type)(2:change input size)(3:quit)\n>>" ;
            cin>>choice;
            switch(choice){
                case 1:{
                    short gate_type ;
                    cout<<"\nChoose gate type";
                    print_gates(AND);
                    cin.ignore() ;
                    cin>>gate_type ;
                    if(gate_type>=AND&&gate_type<=XOR){
                        traverser->gate_type = gate_type ;
                    }
                }break;
                case 2:{
                    if(is_leaf(traverser)){
                        edit_input_size(traverser) ;
                    }
                }break;

            }
        }
        traverser= root ;
    }

    //logic is read from left to right and leaves are assigned only with that logic
    //if size of input logic isn't sufficient to No. of input pins
    //rest are filled with zeroes
    void graph::set_input(const string&input_logic){
        int logic_counter = 0 ;
        gate*temp = root ;
        while(temp){
            set_input(input_logic,logic_counter,temp) ;
            temp=temp->next;
        }
    }


    void graph::set_input(const string&input_logic ,int &logic_counter,gate*ptr){
        if(root){

            if(ptr->children){
                gate*temp = ptr->children;
                while(temp){
                    set_input(input_logic,logic_counter,temp) ;
                    temp=temp->next;
                }
            }
            else{
                if(logic_counter<input_logic.size()){
                    int i =0 ;
                    for(i = 0 ; i<ptr->input_size&&logic_counter<input_logic.size();i++){
                        if(input_logic[logic_counter]=='1'||input_logic[logic_counter]=='0'){
                            ptr->self_input[i] = input_logic[logic_counter]-'0' ;
                        }
                        else{
                            i--;
                        }
                        logic_counter++ ;
                    }
                    while(i<ptr->input_size){
                        ptr->self_input[i]=0 ;
                        i++;
                    }
                }
                else{
                    for(int i =0 ; i <ptr->input_size;i++){
                        ptr->self_input[i]=0 ;
                    }
                }
            }
        }
    }


    /*
    evalutaion functions (for a single tree)
    in view logic it's called on each node or gate next to the root
    */
    void graph::evaluate(gate*ptr) {
        if(root){
            if(ptr==NULL){
                ptr  =root;
            }
            /*
                visit kids and evaluate them first then their parents
            */
            gate*trav = ptr->children ;
            while(trav){
                evaluate(trav) ;
                trav=trav->next ;
            }

            if(ptr->gate_type==AND||ptr->gate_type==NAND){
                evaluate_and_nand(ptr) ;
            }
            else if(ptr->gate_type==OR||ptr->gate_type==NOR){
                evaluate_or_nor(ptr) ;
            }
            else if(ptr->gate_type==XOR){
                evaluate_xor_xnor(ptr) ;
            }
            else {
                evaluate_buffer_not(ptr);
            }
        }
    }

    void graph::evaluate_and_nand(gate*ptr) {
        if(ptr){
           if(is_leaf(ptr)){
                for(int i = 0 ; i<ptr->input_size;i++){
                    if(ptr->self_input[i]==0){
                        //if zero is found and it's nand then o/p is true
                        //else it's false
                        ptr->output = ptr->gate_type==NAND ;
                        return ;
                    }
                }
                //if all are ones then if and it's true
                //else it's false
                ptr->output =  ptr->gate_type==AND ;
           }
           else{
                gate*temp=ptr->children ;
                if(temp){
                    while(temp){
                        if(temp->output==0){
                            //if zero is found and it's nand then true
                            //else it's false
                            ptr->output = ptr->gate_type==NAND ;
                            return ;
                        }
                        temp=temp->next ;
                    }
                //if all are ones then if and it's true
                //else it's false
                ptr->output =  ptr->gate_type==AND ;
                }
           }
        }
    }

    void graph::evaluate_or_nor(gate*ptr) {
        if(ptr){
           if(is_leaf(ptr)){
                for(int i = 0 ; i<ptr->input_size;i++){
                    if(ptr->self_input[i]==1){
                        //if one is found and it's or then o/p is true
                        //else it's false
                        ptr->output = ptr->gate_type==OR ;
                        return ;
                    }
                }
                //if all are ones then if "or" it's true
                //else it's false
                ptr->output =  ptr->gate_type==NOR ;
           }
           else{
                gate*temp=ptr->children ;
                if(temp){
                    while(temp){
                        if(temp->output==1){

                            ptr->output = ptr->gate_type==OR ;
                            return ;

                        }
                        temp=temp->next ;
                    }

                ptr->output =  ptr->gate_type==NOR ;
                }
           }
        }
    }

    void graph::evaluate_xor_xnor(gate*ptr) {
        if(ptr){
           int ones_counter = 0;
           if(is_leaf(ptr)){
                for(int i = 0 ; i<ptr->input_size;i++){
                    if(ptr->self_input[i]==1){
                        ones_counter++ ;
                    }
                }
                ptr->output =  (ptr->gate_type==XOR)?ones_counter&1:!(ones_counter&1) ;
           }
           else{
                gate*temp=ptr->children ;
                if(temp){
                    while(temp->next){
                        if(temp->output==1){

                            ones_counter++ ;
                        }
                        temp=temp->next ;
                    }
                ptr->output =  (ptr->gate_type==XOR)?ones_counter&1:!(ones_counter&1) ;
                }
            }
        }
    }
    //BUFFER isn't used to connect gates or anything
    //you can just extend the input of the gate if it has children gates
    void graph::evaluate_buffer_not(gate*ptr) {
        if(ptr){
           if(is_leaf(ptr)){
                ptr->output =(ptr->gate_type==BUFFER)?ptr->self_input[0]:!ptr->self_input[0] ;
           }
       else{
            gate*temp=ptr->children ;
            if(temp){
                ptr->output =(ptr->gate_type==BUFFER) ?ptr->children->output:!ptr->children->output ;

                }
            }
        }
    }


    void graph::view_logic(void) {
        if(root){
            gate*ptr = root ;
            while(ptr){
                evaluate(ptr) ;
                ptr=ptr->next;
            }
            move() ;
        }
    }

    void graph::save(void)const{
         if(root){
            string file_path="";
            cout << "\nEnter file's path please make sure the file is created\n";
            cout<<">>";
            getline(cin,file_path);
            file_path+="0.txt";
            if (openFileForWriting(file_path)){ //if file exists
                gate*current = root ;
                int counter = 0  ;
                while(current){
                    file_path[file_path.size()-5]=counter+'0';

                    std::ofstream file(file_path, std::ios::trunc); // Open file in write mode, which clears it
                    queue<gate*> q;
                    if (current) {
                        q.push(current);
                //when saving a tree since is can be incomplete we have to keep track of nulls
                //so that logic of the decision tree isn't altred
                //when finding an empty node we add 2 nulls into the queue
                //to keep track of the nulls but this could lead to open loop
                //so tree is done saving when the queue is full of nulls
                //draw an incomplete tree and it will be understood why its used
                        while (!q.empty()) {
                            gate* ptr = q.front();
                            q.pop();
                            while(ptr){
                                file << ptr->gate_type << ":"<<ptr->input_size; // Write the line directly to the file

                                if(ptr->children){
                                    q.push(ptr->children);
                                    file<<":"<<not_leaf <<"\n";
                                }
                                else{
                                    file<<":"<<leaf<<"\n" ;
                                }
                                ptr = ptr->next ;
                            }
                        }
                    }
                    file.close(); // Close the file when done
                    cout<<"\nSaved!";
                    current = current->next ;
                    counter++;
                    }
                }
            }
        }

        void graph::load(void){
            gate*component = NULL ;
            string file_path;
            cout << "\nEnter file's path please make sure the file is created\n";
            cout<<">>";
            getline(cin,file_path);
            if (openFileForReading(file_path)){ //if file exists
                std::ifstream file(file_path);
                string current_gate;
                getline(file, current_gate);
                if(!current_gate.empty()){
                    component = get_gate(current_gate[0]-'0',current_gate[2]-'0') ;
                    size  =1;
                    if(current_gate[2]-'0'!=leaf){
                        delete[]component->self_input ;
                        component->self_input=NULL;
                        queue<gate*>q  ;
                        q.push(component)  ;
                        while(!q.empty()){
                            gate*current_parent = q.front() ;
                            q.pop() ;
                            for(int i = 0 ; i<current_parent->input_size;i++){
                                //read current child
                                getline(file, current_gate);
                                if(current_gate.empty()){
                                    traverser= root ;
                                }
                                if(current_parent->children==NULL){
                                    current_parent->children=get_gate(current_gate[0]-'0',current_gate[2]-'0');
                                    current_parent->children->parent=current_parent ;
                                    traverser = current_parent->children ;
                                }
                                else{
                                    traverser->next=get_gate(current_gate[0]-'0',current_gate[2]-'0') ;
                                    traverser->next->prev=traverser ;
                                    traverser->next->parent = traverser->parent ;
                                    traverser =traverser->next ;
                                }
                                size++ ;
                                if(current_gate[4]-'0'==not_leaf){
                                    q.push(traverser) ;
                                    delete[]traverser->self_input ;
                                    traverser->self_input = NULL;
                                    }
                                }
                            }
                        }
                    }
                file.close(); // Close the file when done
                cout<<"\nloaded!";
                if(root){
                    traverser =root;
                    cout<<"\nMove to the gate where you want to insert the child either on the right or as an input to that gate\n" ;
                    if(move()){
                        int choice ;
                        cout<<"\n(1:append gate to the right)\n(2:append gate as an input to the current gate)\n(3:quit)\n>>";
                        cin>>choice ;
                        if(choice==1||choice==2){
                            if(choice==1){
                                while(!append_right(component)){
                                    cout<<"\nInsertion failed retry again!\n" ;
                                }
                            }
                            else{
                                while(!append_child(component)){
                                    cout<<"\nInsertion failed retry again!\n" ;
                                }
                            }
                        }
                    }
                    else{
                        remove_graph(component);
                        component=NULL;
                    }
                    }
                else{
                    root= component ;
                    traverser=root;
                }
            }
        }
int main(){

    graph board;

    char choice ='y';

    while(choice!='n'){
        board.insert();

        cout<<"\nagain?(y/n)";

        cin>>choice;
        cin.ignore() ;
    }

    return 0  ;
}
