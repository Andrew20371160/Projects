    #include "graph.h"

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
    const uint16_t gate_count =8 ;

    const string gates[8] {"NOT" ,"BUFFER","NAND" ,"AND","NOR" ,"OR" ,"XNOR","XOR"};

    void print_gates(uint16_t start= 0){
        for(uint16_t i = start ; i <gate_count ; i++){
            cout<<"\n("<<i<<":"<<gates[i]<<")";
        }
    }


    bool is_valid_gate(const uint16_t&g_type,const uint32_t&in_size){
        return(g_type>=NOT&&g_type<=XOR&&in_size>=0);
    }



    //allocate memory for a new gate
    gate* gate:: get_gate(const uint16_t&g_type,const uint32_t&in_size){
        gate*new_gate = NULL;
        if(is_valid_gate(g_type,in_size)){
            new_gate=new gate ;
            if(new_gate){
                new_gate->gate_type=g_type;
                new_gate->output = 0 ;


                //array of booleans
                new_gate->input=NULL ;
                new_gate->resize_input(in_size);
                //links
                new_gate->parent = NULL ;
                new_gate->next=NULL;
                new_gate->prev=NULL ;
                new_gate->children=NULL;
                new_gate->children_count=0;
                //lists for wiring system
                new_gate->wire_input=list<gate*>();
                new_gate->wire_output=list<gate*>();

                return new_gate;
            }
        }
        return NULL;
    }

    void gate::remove_all(gate*&root){
        while(root){
            queue<gate*>q ;
            q.push(root);
            root=root->next;
            while(!q.empty()){
                gate*temp = q.front() ;
                q.pop();
                if(temp->children){
                    gate*ch_ptr=  temp->children;
                    while(ch_ptr){
                        q.push(ch_ptr) ;
                        ch_ptr=ch_ptr->next;
                    }
                }
                if(temp->input){
                    delete[]temp->input;
                    temp->input=NULL;
                }
                delete temp;
                temp = NULL ;
            }
        }
    }

    bool gate::buffer_not_condition(const gate*ptr){
        if(ptr){
            if(ptr->gate_type==NOT||ptr->gate_type==BUFFER){
                return ptr->children==NULL&&ptr->wire_input.size()==0 ;
            }
            return true ;
        }
        return false ;
    }

    //append a gate into the right
    bool gate::append_right(const uint16_t&g_type,const uint32_t&in_size) {

        if(is_valid_gate(g_type,in_size)){
            /*
                if no parent
                or if there is parent and the parent is eligibale
                where if it's not or buffer it must have no other source of input
                or it's not buffer or not
            */
             if(parent==NULL||buffer_not_condition(parent)){
                gate*new_gate= get_gate(g_type,in_size) ;
                if(new_gate){
                    new_gate->next=this->next ;
                    new_gate->prev=this ;
                    if(this->next){
                        this->next->prev=new_gate;
                    }
                    this->next =new_gate;

                    new_gate->parent = this->parent;

                    if(new_gate->parent){
                        new_gate->parent->children_count++;
                    }

                    return true ;
                }
             }
         }
         return false ;
    }

    //append a gate as a child
    bool gate::append_child(const uint16_t&g_type,const uint32_t &in_size) {
        if(is_valid_gate(g_type,in_size)){
            if(buffer_not_condition(this)){
                //if first child then delete input
                if(children==NULL){

                    children = get_gate(g_type,in_size) ;
                    children->parent=this ;
                    resize_input(0);
                    children_count++;
                    return true;
                }
                else{
                    gate*ptr = children ;
                    while(ptr->next){
                        ptr=ptr->next ;
                    }
                    ptr->append_right(g_type,in_size);
                    return true;
                }
            }
        }
        return false ;
    }




    bool gate::resize_input(const uint32_t new_in){
         if(new_in>=0){
             //delete old memory
             if(input){
                delete[]input ;
                input=NULL;
                input_size=0 ;
             }
             if(gate_type==NOT||gate_type==BUFFER){
                if(new_in>0){
                    input_size =1 ;
                    input = new bool[1] ;
                    input[0] = 0 ;
                }
             }
             //set new input
             else{
                if(new_in>0){
                    input_size =new_in ;
                    input = new bool[new_in];
                    for(uint32_t i = 0 ; i<new_in;i++){
                        input[i] = 0 ;
                    }
                }
             }
            return true;
         }
        return false ;
    }
    /*
    Wiring system
    */
    bool gate::connect_wire(gate*&src_input){
        if(src_input){
            if(buffer_not_condition(this)){
                resize_input(0);

                wire_input.push_back(src_input);
                src_input->wire_output.push_back(this);
                return true ;
            }
        }
        return false;
    }
    bool gate::disconnect_wire(gate*&src_input){
        if(src_input){
            wire_input.remove(src_input);
            src_input->wire_output.remove(this);
            return true ;
        }
        return false;
    }

    bool gate::disconnect_wires_in(void) {
        if(wire_input.size()){
            /*
                wire_input contains all addresses of gates that phantom takes input from
                go into each one of them disconnect this from wire_output
                then disconnect them from wires in
            */
            for(list<gate*>::iterator wire_in_iter =wire_input.begin(); wire_in_iter!=wire_input.end();++wire_in_iter){
                (*wire_in_iter)->wire_output.remove(this);
            }
            //now this is removed from each wire_output
            wire_input.clear();
            return true;
        }
        return false;
    }
    bool gate::disconnect_wires_out(void) {
        /*
            wire_output contains all addresses of gates that phantom gives output to
            go into each one of them disconnect this from wire_input
            then disconnect them from wires out
        */
        if(wire_output.size()){
            /*
                wire_input contains all addresses of gates that phantom takes input from
                go into each one of them disconnect this from wire_output
                then disconnect them from wires in
            */
            for(list<gate*>::iterator wire_out_iter =wire_output.begin(); wire_out_iter!=wire_output.end();++wire_out_iter){
                (*wire_out_iter)->wire_input.remove(this);
            }
            //now this is removed from each wire_output
            wire_output.clear();
            return true;
        }
        return false;
    }

    //returns pointer to first gate without any source of input
    //no wires attatched to it as an input , no input , no children
    gate* gate::first_no_input(void){
        queue<gate*>q ;
        q.push(this);
        while(!q.empty()){
            gate*temp = q.front() ;
            q.pop();
            if(temp->input==NULL&&temp->children==NULL&&temp->wire_input.size()==0){
                return temp;
            }
            if(temp->children){
                gate*trav= temp->children ;
                while(trav){
                    q.push(trav);
                    trav =trav->next;
                }
            }
        }
        return  NULL ;
    }
    //returns a list of all gates without any source of input
    list<gate*> gate::all_no_input(void){
        list<gate*> ret_list ;
        queue<gate*>q ;
        q.push(this);
        while(!q.empty()){
            gate*temp = q.front() ;
            q.pop();
            if(temp->input==NULL&&temp->children==NULL&&temp->wire_input.size()==0){
                ret_list.push_back(temp);
            }
            if(temp->children){
                gate*trav= temp->children ;
                while(trav){
                    q.push(trav);
                    trav =trav->next;
                }
            }
        }
        return  ret_list ;
    }

    /*printing section*/
    void  gate::print_input_logic(void){
        if(input){
            for(uint32_t i =0 ;i<input_size;i++){
                cout<<input[i]<<" ";
            }
        }
        if(children){
            gate *ptr =children;
            while(ptr){
                cout<<ptr->output<<" ";
                ptr=ptr->next ;
            }
        }
        if(wire_input.size()){
            for(list<gate*>::iterator wire_in_iter =wire_input.begin(); wire_in_iter!=wire_input.end();++wire_in_iter){
                cout<<(*wire_in_iter)->output<<" ";
            }
        }
    }
    void  gate::print_input_sticks(void){
        if(input){
            for(uint32_t i =0 ;i<input_size;i++){
                cout<<"| ";
            }
        }
        if(children){
            gate *ptr =children;
            while(ptr){
                cout<<"| ";
                ptr=ptr->next;
            }
        }
        if(wire_input.size()){
            for(list<gate*>::iterator wire_in_iter =wire_input.begin(); wire_in_iter!=wire_input.end();++wire_in_iter){
                cout<<"| ";
            }
        }
    }
    void gate:: print_input_gates(void){

        if(input){
            for(uint32_t i =0 ;i<input_size;i++){
                cout<<"  ";
            }
        }
        if(children){
            gate *ptr =children;
            while(ptr){
                cout<<gates[ptr->gate_type]<<" ";
                ptr=ptr->next;
            }
        }
        if(wire_input.size()){
            for(list<gate*>::iterator wire_in_iter =wire_input.begin(); wire_in_iter!=wire_input.end();++wire_in_iter){
                cout<<gates[(*wire_in_iter)->gate_type]<<" ";
            }
        }
    }
    void gate:: print(void){
        cout<<"\n"<<output;
        cout<<"\n|";
        cout<<"\n"<<gates[gate_type];
        cout<<"\n";
        print_input_logic();
        cout<<endl;
        print_input_gates();
    }
    /*
    graph section
    */


    graph ::graph(void){
        root=NULL;
        traverser=NULL;
    }

    void graph::remove_graph(void){
        traverser=NULL;
    //when root is removed it goes to next pointer check remove gate for more context
        while(root){
            remove_gate(root);
        }
        root =NULL;
    }

    graph:: ~graph(void){
        while(root){
            remove_gate(root);
        }
    }

    //adjust all the links related to this to others
    void graph::remove_links(gate*component){
        if(component){
            if(component==root){
                root = root->next ;
                traverser= root ;
            }
            //if it's the head of the parent
            //move the children pointer to next child
            if(component->parent){
                if(component->parent->children==component){
                    component->parent->children=component->next;
                }
                component->parent->children_count--;
            }

            if(component->next){
                component->next->prev=component->prev;
            }

            if(component->prev){
                component->prev->next=component->next;
            }
            component->parent=NULL;
        }
    }
    void graph ::remove_gate(gate*component){
        if(component){
            //update the links around it
            remove_links(component);
            //bfs and delete each element of that subtree
            queue<gate*>q ;
            q.push(component) ;
            while(!q.empty()){
                gate *temp= q.front() ;
                q.pop();
                //disconnect self from all gates in wire_output/input
                temp->disconnect_wires_out();
                temp->disconnect_wires_in();

                //push each child
                if(temp->children){
                    gate*child_ptr = temp->children ;
                    while(child_ptr){
                        q.push(child_ptr) ;
                        child_ptr=child_ptr->next;
                    }
                }
                if(temp->input){
                    delete[]temp->input ;
                    temp->input= NULL;
                }
                delete temp ;
                temp= NULL;
            }
        }
    }

    bool graph:: remove(void){
        if(move()){
            uint16_t choice;
            cout<<"\nThis action will remove : "<<gates[traverser->gate_type];
            cout<<"\nand all it's children and disconnect all the wires related to them";
            cout<<"\n(0:Cancel)\n(1:Confirm)\n>>";
            cin>>choice;
            if(choice==1){
                remove_gate(traverser);
                traverser=root;
                return true ;
            }
        }
        return false ;
    }

   bool graph::move(void){
        if(root){
            traverser=root;

            while(1){

                traverser->print();
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

    void graph::insert(void){
        //specify gate type and input size
        //memory isn't allcated
        //untill you move() to the gate and append the new gate
        uint16_t gate_type ;
        cout<<"\nChoose gate type";

        print_gates(NOT);

        cin>>gate_type ;
        cin.ignore()  ;
        uint32_t in_size ;
        cout<<"\nEnter size of the new gate(No. of input pins)";
        cin>>in_size  ;
        //make sure it's within the range of gates
        if(is_valid_gate(gate_type,in_size)){
            if(root==NULL){
                root = root->get_gate(gate_type,in_size) ;
            }

        else{
            cout<<"\nMove to the gate where you want to insert the child either on the right or as an input to that gate\n" ;
            if(move()){
                uint32_t choice ;
                cout<<"\n(1:append gate to the right)\n(2:append gate as an input to the current gate)\n(3:quit)\n>>";
                cin>>choice ;
                if(choice==1||choice==2){
                    if(choice==1){
                        traverser->append_right(gate_type,in_size);
                    }
                    else{
                        traverser->append_child(gate_type,in_size);
                        }
                    }
                }
            }
        }
    }





    //logic is read from left to right and leaves are assigned only with that logic
    //if size of input logic isn't sufficient to No. of input pins
    //rest are filled with zeroes
    void graph::set_input(const string&input_logic){
        uint32_t logic_counter = 0 ;
        gate*temp = root ;
        while(temp){
            set_input(input_logic,logic_counter,temp) ;
            temp=temp->next;
        }
    }


    void graph::set_input(const string&input_logic ,uint32_t &logic_counter,gate*ptr){
        if(ptr){
            if(ptr->children){
                gate*temp = ptr->children;
                while(temp){
                    set_input(input_logic,logic_counter,temp) ;
                    temp=temp->next;
                }
            }
            else{
                if(ptr->input){
                    if(logic_counter<input_logic.size()){
                        uint32_t i =0 ;
                        for(i = 0 ; i<ptr->input_size&&logic_counter<input_logic.size();i++){
                            if(input_logic[logic_counter]=='1'||input_logic[logic_counter]=='0'){
                                ptr->input[i] = input_logic[logic_counter]-'0' ;
                            }
                            else{
                                i--;
                            }
                            logic_counter++ ;
                        }
                        while(i<ptr->input_size){
                            ptr->input[i]=0 ;
                            i++;
                        }
                    }
                    else{
                        if(ptr->input){
                            for(uint32_t i =0 ; i <ptr->input_size;i++){
                                ptr->input[i]=0 ;
                            }
                        }
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
            else if(ptr->gate_type==XOR||ptr->gate_type==XNOR){
                evaluate_xor_xnor(ptr) ;
            }
            else {
                evaluate_buffer_not(ptr);
            }
        }
    }

    void graph::evaluate_and_nand(gate*ptr) {
        if(ptr){
           bool found_zero=false;
           if(ptr->input){
                for(uint32_t i = 0 ; i<ptr->input_size;i++){
                    if(ptr->input[i]==0){
                        //if zero is found and it's nand then o/p is true
                        //else it's false
                        found_zero =true;
                    }
                }
                //if all are ones then if and it's true
                //else it's false
           }
           else if(ptr->children){
                gate*temp=ptr->children ;
                    while(temp){
                        if(temp->output==0){
                            //if zero is found and it's nand then true
                            //else it's false
                            found_zero =true;
                        }
                        temp=temp->next ;
                    }
                //if all are ones then if and it's true
                //else it's false
                }
            else if(ptr->wire_input.size()){
                for(list<gate*>::iterator i = ptr->wire_input.begin() ; i!=ptr->wire_input.end();++i){
                    if((*i)->output==0){
                        found_zero =true;
                    }
                }
            }
            ptr->output = found_zero? ptr->gate_type==NAND:ptr->gate_type==AND ;
        }
    }
    void graph::evaluate_or_nor(gate*ptr) {
        if(ptr){
           bool found_one =false;
           if(ptr->input){
                for(uint32_t i = 0 ; i<ptr->input_size;i++){
                    if(ptr->input[i]==1){
                        //if one is found and it's or then o/p is true
                        //else it's false
                        found_one =true;
                    }
                }
           }
           else if(ptr->children){
                gate*temp=ptr->children ;
                    while(temp){
                        if(temp->output==1){
                            found_one=true   ;
                        }
                        temp=temp->next ;
                    }
                }
            else if(ptr->wire_input.size()){
                for(list<gate*>::iterator i = ptr->wire_input.begin() ; i!=ptr->wire_input.end();++i){
                    if((*i)->output==1){
                        found_one =true;
                    }
                }
            }
            ptr->output=(found_one)?ptr->gate_type==OR: ptr->gate_type==NOR ;
        }
    }

    void graph::evaluate_xor_xnor(gate*ptr) {
        if(ptr){
           uint32_t ones_counter = 0;
           if(ptr->input){
                for(uint32_t i = 0 ; i<ptr->input_size;i++){
                    if(ptr->input[i]==1){
                        ones_counter++ ;
                    }
                }
           }
           else if(ptr->children){
                gate*temp=ptr->children ;
                    while(temp->next){
                        if(temp->output==1){

                            ones_counter++ ;
                        }
                        temp=temp->next ;
                    }
                }
            else if(ptr->wire_input.size()){
                for(list<gate*>::iterator i = ptr->wire_input.begin() ; i!=ptr->wire_input.end();++i){
                    if((*i)->output==1){
                        ones_counter++;
                    }
                }
            }
            ptr->output=(ptr->gate_type==XOR)?ones_counter&1:!(ones_counter&1);
        }
    }
    //BUFFER isn't used to connect gates or anything
    //you can just extend the input of the gate if it has children gates
    void graph::evaluate_buffer_not(gate*ptr) {
        if(ptr){
           if(ptr->input){
                ptr->output =(ptr->gate_type==BUFFER)?ptr->input[0]:!ptr->input[0] ;
           }
           else if(ptr->children){
                    ptr->output =(ptr->gate_type==BUFFER) ?ptr->children->output:!ptr->children->output ;
                }
            else if(ptr->wire_input.size()){
                ptr->output =(ptr->gate_type==BUFFER) ?ptr->wire_input.front()->output:!ptr->wire_input.front()->output;
            }
            else{
                ptr->output=0 ;
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

    /*
    saving , loading , wiring section
    */
    /*
    get_path returns a string representing path leading to wanted gate
    made by a simulation on a piece of paper :)
    */
        bool graph::connect(void){
        traverser =root ;
        cout<<"\nConnect Output of :";
        if(move()){
            gate*from = traverser;
            cout<<"\nTo Input of :";
            if(move()){
                traverser->connect_wire(from);
                return true;
            }
        }
        return false;
    }
    bool graph::disconnect(void){
        traverser =root ;
        cout<<"\nDisconnect wire from Output of :";
        if(move()){
            gate*from = traverser;
            cout<<"\nFrom Input of :";
            if(move()){
                traverser->disconnect_wire(from);
                return true;
            }
        }
        return false ;
    }
    //it worked XD
    string graph::get_path(gate* wanted){
        if(wanted){
            string node_path ="";
            if(wanted==root){
                return "";
            }
            else{
                /*
                first which major tree is wanted in? so go max up then count how many lefts leading to root
                then which less major tree it belongs to do same again recursively or by iteration
                */
                gate *level = NULL ;

                gate *dest =root  ;
                while(1){

                    gate *ptr = wanted ;
                    while(ptr->parent!=level){
                        ptr=ptr->parent;
                    }
                    gate*temp = ptr ;//save that location i'm returning to it

                    while(ptr!=dest){
                        ptr=ptr->prev ;
                        node_path+='r';
                    }

                    level = temp ;

                    if(level==wanted){
                        return node_path;
                    }

                    if(temp->children){
                    //now we go down a level so add c (children)
                        dest = temp->children;
                        node_path+='c';
                    }
                }
            }
            //repeat again
        }
    }

    void graph::get_path(void){
        if(root){
            if(move()){
                cout<<get_path(traverser);
            }
        }
    }
    /*
    returns a pointer following a binary path of left (supposed to be next but will fix it later)
    or children
    just like user goes down the tree with w,a,s,d this function does this automation(used in wiring the system when loading from a file)
    */
    gate* gate::get_to(string gate_path){
        if(gate_path==""){
            return this ;
        }
        gate *ptr = this;
        for(uint32_t i = 0 ; i <gate_path.size();i++){
            if(ptr){
                if(gate_path[i]=='r'){
                    ptr = ptr->next;
                }
                else if(gate_path[i]=='c'){
                    ptr=ptr->children;
                }
            }
            else{
                return NULL  ;
            }
        }
        return ptr;
    }
    /*
     returns a string of the whole wiring in the system
     in this format
     lcl:ll
     lc:llc
     where l,c indicate path leading to a node
     l is next (not left )
     c is down or children
    */
    string graph::get_wiring(void){
        if(root){
           string str = "" ;
           gate*ptr = root ;
           //for each major tree in the graph
           while(ptr){
                queue<gate*>q ;
                q.push(ptr);
                while(!q.empty()){
                    gate*temp = q.front() ;
                    q.pop();
                    //push each children into the queue
                    if(temp->children){
                        gate*ch_ptr = temp->children ;
                        while(ch_ptr){
                            q.push(ch_ptr) ;
                            ch_ptr=ch_ptr->next;
                        }
                    }
                    /*
                        if temp's output is connected to other gates

                    */
                    if(temp->wire_output.size()){
                        //save current path
                        string current_path = get_path(temp);
                        for(list<gate*>::iterator i = temp->wire_output.begin();i!=temp->wire_output.end();++i){
                            //for each gate current's output is connected to as an input
                            //get the path and append it in the string in that format
                            /*
                            from:to
                            from:to
                            .....
                            */
                            str+=current_path+":"+get_path(*i)+"\n";
                        }
                    }
                }
                //go to next major tree and repeat
                ptr=ptr->next;
            }
            return str;
        }
        return "";
    }
    /*
    after loading the component and its wiring (if exists)
    this functino wires the loaded component (not the current tree)
    makes sense since if i load multiple components the wiring is same for the component itself
    but surely not for the whole graph
    */
    void gate::wire_system(string wiring){
        string from = "";
        string to = "" ;
        uint32_t i= 0;
        //if there is wiring
        while(i<wiring.size()){
            //first get path of src of input
            //or output to other gate
            if(wiring[i]!=':'&&wiring[i]!='\n'){
                from+=wiring[i] ;
                i++;
            }
            else{
                i++; // Skip the ':' character
                //then get the gate that's taking an input from current "from" or wired to it
                while(i<wiring.size() && wiring[i]!='\n'){
                    to+=wiring[i];
                    i++;
                }

                gate*from_ptr= get_to(from);
                gate*to_ptr =get_to(to);
                //if both are valid paths
                if(from_ptr != NULL && to_ptr != NULL) {

                    to_ptr->connect_wire(from_ptr);
                }
                //empty the strings
                from="";
                to="";
                if(i<wiring.size() && wiring[i]=='\n') {
                    i++; // Skip the '\n' character
                }
                //repeat
            }
        }
    }

    /*
    saving mechanism is simple you just type path and the component's name without extension
    for ex : path\half_adder
    and this function saves each major tree of the component into a file and each file is indexed from 0 to n-1
    then the wiring of the component (if exists) is saved into another file with wiring appended to component's name
    for ex: path\half_adderwiring
    */
    void graph::save(void){
        if(root){
            //get file path
            string file_path="";
            cout << "\nEnter file's path without extensions(.txt,.bin...etc)\n";
            cout<<">>";
            getline(cin,file_path);
            //first file for first major subtree
            file_path+="0.txt";
            //if file is oppened successfully
            if (openFileForWriting(file_path)){ //if file exists
                //for each major tree in the graph
                gate*current = root ;
                uint32_t counter = 0  ;
                while(current){
                    //append file index
                    file_path = file_path.substr(0, file_path.size()-5) + std::to_string(counter) + ".txt";
                    ofstream file(file_path, std::ios::trunc); // Open file in write mode, which clears it
                    //breadth first
                    queue<gate*> q;
                    q.push(current);
                    while (!q.empty()) {
                        gate* ptr = q.front();
                        q.pop();
                        file << ptr->gate_type << ":";
                        if(ptr->children){
                            file<<ptr->children_count;
                        }
                        else{
                            file<<ptr->input_size;
                         // Write the line directly to the file
                        }
                        if(ptr->children){
                            gate*ch_ptr = ptr->children ;
                            //push each child
                            while(ch_ptr){
                               q.push(ch_ptr);
                               ch_ptr= ch_ptr->next ;
                            }
                            //then write the status
                            file<<":"<<not_leaf <<"\n";
                        }
                        else{
                            file<<":"<<leaf<<"\n" ;
                        }
                    }
                    //close current file then open a new one if current isn't null
                    file.close(); // Close the file when done
                    cout<<"\nSaved!";
                    current=current->next ;
                    counter++;
                }
                //then save the wiring if exists
                file_path = file_path.substr(0, file_path.size()-5);
                file_path += "wiring.txt";
                ofstream file(file_path, std::ios::trunc);
                file << get_wiring();
                file.close();
                }
            }
        }
        /*
        loads a component ,it's children wires them with same wiring
        then asks user to append whole component into the tree if it's not empty
        */
    void graph::load(void){

        gate*component = NULL;
        gate*current = NULL;
        gate*trav  = NULL ;
        bool file_found = false;
        int file_counter = 0;

        string file_path ="" ;
        string currnet_gate="";

        cout<<"\nEnter file path witout indexing or extension: ";
        getline(cin,file_path);
        file_path+="0.txt";
        while(openFileForReading(file_path)){
            cout<<"\noppened: "<<file_path;
            //current file
            ifstream file(file_path);
            file_found=true;
            //read first line
            getline(file, currnet_gate);
            //if not empty
            if(currnet_gate.size()){
                //current root (of major tree)
                current= current->get_gate(currnet_gate[0]-'0',currnet_gate[2]-'0') ;

                if(currnet_gate[4]-'0'==not_leaf){
                    //if it's not leaf remove allocated memory for the input
                    current->resize_input(0) ;
                    //save value of current parent's children count
                    current->children_count=currnet_gate[2] -'0';
                    //for each gate in the tree
                    queue<gate*>q;
                    q.push(current);

                    while(!q.empty()){
                        gate *temp = q.front() ;
                        q.pop() ;
                        //save value of ch_chount
                        uint32_t ch_count = temp->children_count;
                        for (uint32_t i = 0; i <ch_count; ++i)
                        {
                            getline(file, currnet_gate);
                            //append the child
                            //note when appendign temp's children count increase so
                            //the value of ch_count was saved to append
                            //current count of children
                            temp->append_child(currnet_gate[0]-'0',currnet_gate[2]-'0') ;
                            if(i==0){
                                //traverser always points to max left of the tree
                                traverser = temp->children;
                            }
                            else{
                                traverser=traverser->next;
                            }
                            //if current gate isn't a leaf
                            //push it in the queue
                            //we are only interseted with nodes with children
                            if(currnet_gate[4]-'0'==not_leaf){
                                //remove allocated memory for the array
                                traverser->resize_input(0) ;
                                //save children count of traverser
                                traverser->children_count =currnet_gate[2]-'0' ;
                                q.push(traverser) ;
                            }
                        }
                        //by now children count of temp increased by double
                        //so remove ch_count from it
                        temp->children_count-=ch_count;
                    }
                }
            }
            //close current file
            file.close() ;
            file_counter++;
            file_path = file_path.substr(0, file_path.size()-5) +to_string(file_counter) + ".txt";

            //component is treated as a root
            if(component==NULL){
                component=current;
            }
            else{
                //go max left and append current major tree
                trav = component;
                while(trav->next){
                    trav=trav->next;
                }
                current->prev=trav;
                trav->next = current ;
            }
        }
        if(file_found){
            file_path = file_path.substr(0, file_path.size()-5) +"wiring.txt";
            if(openFileForReading(file_path)){
                ifstream file(file_path); // Open file in read mode
                string wiring="";
                string temp = "" ;
                while(getline(file, temp)){
                    wiring += temp+'\n';
                }
                component->wire_system(wiring);
                file.close();
            }
            if(root==NULL){
                root =component;
                traverser=root;
            }
            else{
                while(1){
                    if(move()){
                        int choice ;
                        cout<<"\n1--append to the right";
                        cout<<"\n2--append as a child";
                        cout<<"\n3--cancel";
                        cin>>choice;
                        if(choice==1){

                            if(append_right(component)){
                                return ;
                            }
                        }
                        else if(choice==2){
                            if(append_child(component)){
                                return ;
                            }
                        }
                        else{

                            component->remove_all(component);
                            component=NULL;
                            return ;
                        }
                    }
                }
            }
        }
    }
    uint32_t graph::count_list(gate*head){
        gate*ptr = head;
        uint32_t counter=  0 ;
        while(ptr){
            counter++;
            ptr=ptr->next;

        }
        return counter  ;
    }

    bool graph:: assign_parent(gate*head,gate*parent) {
        gate*ptr=  head ;
        while(ptr){
            ptr->parent = parent ;
            ptr=ptr->next ;

        }
        return true  ;
    }
    bool graph::append_child(gate*component) {
        //if it's first child
        if(component){
            //count number of children
            uint32_t ch_counter = count_list(component);

            if(traverser->children==NULL){
                assign_parent(component,traverser) ;

                //then parent or traverser was a leaf
                //so we delete allocated memory for the array of booleans
                traverser->resize_input(0) ;

                traverser->children= component;

                traverser->children_count=ch_counter;
                return true  ;
            }
            else{
                //if the gate is "not" you can't put another input gate to it
                //short circuit
                if(traverser->buffer_not_condition(traverser)){
                        assign_parent(component,traverser) ;

                       gate*ptr = traverser->children;
                        //go to max right then append the new gate
                        while(ptr->next){
                            ptr = ptr->next ;
                        }
                        component->prev= ptr;

                        ptr->next= component ;

                        traverser->children_count+=ch_counter;
                        return true  ;

                    }
                    else{
                        return false;
                    }
                }
            }
        }

    bool graph::append_right(gate*component) {
        if((traverser->parent==NULL)||traverser->buffer_not_condition(traverser->parent)){
            assign_parent(component,traverser->parent);

            component->prev = traverser ;

            gate*trav = component ;
            while(trav->next){
                trav = trav->next ;
            }
            trav->next = traverser->next ;

            if(traverser->next){
                traverser->next->prev = trav;
            }

            traverser->next = component ;

            if(traverser->parent){
                uint32_t ch_counter = count_list(component) ;

                traverser->parent->children_count+=ch_counter ;
            }
            return true ;
        }
        else{
            return false;
        }
    }
int main(){

    graph board;

    int choice ;
    while(1){
        cout<<"\n1-Insert\n2-Connect\n3-Disconnect\n4-test\n5-remove\n6-remove graph\n7-save\n8-load\n9-move\n10-quit";
        cin>>choice ;
        switch(choice){
            case 1:board.insert() ; break ;
            case 2:board.connect() ; break ;
            case 3:board.disconnect() ; break ;

            case 4:{
                cin.ignore() ; //what caused the bug is that when i hit enter
                //no input is set and yeah cin.ignore should solve it
                string input = "";
                cin>>input;
                board.set_input(input);
                board.view_logic() ;
            }break ;
            case 5:board.remove() ; break ;
            case 6:board.remove_graph() ; break ;
            case 7:{
                cin.ignore();
                board.save() ;
            }break ;
            case 8:{

                cin.ignore();
                board.load();
            }break;
            case 9:{

                cin.ignore();
                board.move();
            }break;
            case 10:return 0;

        }
    }

    return 0  ;

}
