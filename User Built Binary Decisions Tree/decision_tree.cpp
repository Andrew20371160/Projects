
#include "decision_tree.h"


bool getInput(int& choice) {
    cin>>choice;
    if(cin.fail()) {
        cin.clear(); // clear the error state
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the bad input

        return false;
    }
    return true;
}

bool getInput(char& choice) {
    cin>>choice;
    if(cin.fail()) {
        cin.clear(); // clear the error state
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the bad input
        return false;
    }
    return true;
}


enum{False=0,True,no_answer=-1} ;

//a string that indicates that this node is empty so won't be added into the tree
//used in saving/loading from a file in breadth-first
string filling_string="This is a filling slot and won't be put into the tree";


//allocate memory for a node
node*decision_tree::get_node(string _text,bool p_answer){
    node*new_node = new node ;

    new_node->text =_text;

    new_node->parent_answer = p_answer;

    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node ;
}

//empty tree
decision_tree ::decision_tree(void){
    root = NULL;
    traverser= NULL;
}

/*
fill the tree with an array inialized in breadth first fashion
into the tree for empty values use ""
*/
decision_tree::decision_tree(string*arr,int size){
        if(!arr[0].empty()){
            root = get_node(arr[0]);
            traverser = root ;
            int i=1;
            queue<node*>q;
            q.push(root);
            while (i<size-1&&!q.empty()) {
                node* ptr = q.front();
                q.pop();
                if (!arr[i].empty()) {
                    while(ptr==NULL){
                        ptr = q.front();
                        q.pop() ;
                    }
                    ptr->left = get_node(arr[i]);
                    ptr->left->parent = ptr;
                    q.push(ptr->left);
                }
                else{
                    q.push(NULL) ;
                }
                i++;
                if (!arr[i].empty()) {
                    while(ptr==NULL){
                        ptr = q.front();
                        q.pop() ;
                    }
                    ptr->right = get_node(arr[i]);
                    ptr->right->parent = ptr;
                    q.push(ptr->right);
                }
                else{
                    q.push(NULL) ;
                }
                i++;
            }

        }
        else{
            cout<<"\nProvided array doesn't have a root (first entry of the array is empty)\n";
            cout<<"\nTree is empty" ;
            root= NULL;
            traverser=NULL;
        }
    }

    //destructor before deleteing the tree it gives option to save current tree
    decision_tree::~decision_tree(void){
        if(root){
            char answer;
            cout<<"\nDo you want to save current tree?(y/n)\n";
            while(!getInput(answer) ){
                cout<<"\n>>";
            }
            if(answer!='n'){
                save();
            }
            del_tree(root) ;
            root =NULL ;
            traverser = NULL ;
        }
    }

    //delete a tree from the heap
    void del_tree(node*ptr){
        if(ptr){
            if(ptr->left){
                del_tree(ptr->left) ;
            }
            if(ptr->right){
                del_tree(ptr->right) ;
            }
            if(ptr){
                delete ptr ;
                ptr= NULL;
            }
        }
    }

//move using traverser in the tree
bool decision_tree::move(void){
    if(root){
        traverser= root;
        char curser;
            while(1){
                cout<<"\n(Enter->stops at current)\n(w->go up)\n(a->go left(false part))\n(d->go right(true part))\n(s->show the whole tree)\n(q->quit)\n>>";
                char curser = getch();
                fflush(stdin);
                switch(curser){
                    case 'w' :{
                        if(traverser->parent)
                            traverser= traverser->parent;
                        }break;

                    case 'a' :{
                        if((traverser)->left)
                            (traverser)= (traverser)->left;
                        }break;
                    case 'd' :{
                        if((traverser)->right)
                            (traverser)=(traverser)->right;
                        }break;

                    case 's':{
                        print();
                    }break;

                    case 'q' :{
                        traverser= root;
                        return 0;
                    }
                    case '\r':
                        return 1;
                    }
                    cout<<"current : "<<traverser->text;
                }
            }
        else{
            cout<<"Can't move in an empty tree";
        }
        return 0 ;
    }

//link a new question to node pointed at by traverser
void decision_tree::promt_question(void){
    if(root==NULL){
        //first check if root is empty
        cout<<"\nEnter the root question/answer\n";
        cout<<">>";
        root =get_node("");
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin,root->text);
        traverser= root ;
    }
    else{
        int answer;
        cout<<"\nIs it true or false answer?(1/0)(3-quit)\n>>";
        while(!getInput(answer)){
            cout<<"\n>>";
        }
        if(answer==0||answer==1){
            if(answer==0){
                if(traverser->left==NULL){
                    traverser->left=get_node("",answer) ;
                    traverser->left->parent= traverser;
                    traverser=traverser->left ;
                }
                else{
                    //can't update or add a node on a non empty link
                    cout<<"use update to update the question" ;
                    return ;
                 }
            }
            else if(answer==1){
                if(traverser->right==NULL){
                    traverser->right=get_node("",answer) ;
                    traverser->right->parent= traverser;
                    traverser=traverser->right ;
                }
                else{
                    //can't update or add a node on a non empty link
                    cout<<"use update to update the question" ;
                    return ;
                }
            }
            cout<<"\nEnter the question/answer\n>>";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(cin, traverser->text );
            traverser = traverser->parent;

            }
            else{
                cout<<"\nNot added\n";
            }
        }
    }




//iterface with the user to enter new nodes into the tree
void decision_tree ::construct(void){
    char outer_choice = 'y';
    char inner_choice;
    while(outer_choice!='n'){
        cout<<"Enter new node?(y/n)\n>>";
        while(!getInput(outer_choice)){
            cout<<"\n>>" ;
        }
        if(outer_choice!='n'){
            if(root==NULL){
                root = get_node("",no_answer) ;
                cout<<"\nEnter the question/answer\n>>";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin,root->text) ;
                traverser= root ;
            }
            else{
                while(1){
                    cout<<"is it related to current question?(y/n)\n(hit q to quit)\n" ;
                    cout<<"\ncurrent : "<<traverser->text<<"\n>>";
                    while(!getInput(inner_choice)){
                        cout<<"\n>>" ;
                    }
                    if(inner_choice=='q'){
                        return  ;
                    }
                    else if(inner_choice!='n'){
                            promt_question() ;
                            break;
                        }
                    else{
                        if(move()){
                           promt_question();
                        }
                        break;
                        }
                    }
                }
            }
        }
    }

    bool is_power_of_two(int num) {
        return num > 0 && (num & (num - 1)) == 0;
    }
//print the tree elegantly using breadth first

void decision_tree::print(void){
    queue<node*>q ;
    if(root){
        q.push(root) ;
        int current_level_nodes = 1;//keep track of current level nodes
        int next_level_nodes = 0;//keep track of next nodes
        while(!q.empty()){
            node*ptr = q.front()  ;
            q.pop() ;
            cout<<ptr->text<<" , ";
            if(ptr->left){
                q.push(ptr->left);
                next_level_nodes++;
            }
            if(ptr->right){
                q.push(ptr->right) ;
                next_level_nodes++;
            }
            current_level_nodes--;
            if(current_level_nodes == 0){
                cout<<endl  ;
                current_level_nodes = next_level_nodes;
                next_level_nodes = 0;
            }
        }
    }
}
    //checks if user_input is a portion of a question (helper function)
    bool is_related(string&user_input,string&tree_node_text){
        int user_input_counter =  0 ;
        int tree_node_counter  =  0 ;
        bool logic ;
        while(tree_node_text[tree_node_counter]!='\0'){
            if(user_input[0]==tree_node_text[tree_node_counter]){
                logic= true ;
                user_input_counter = 0;
                int i  = 0;
                while(user_input[user_input_counter]!='\0'&&tree_node_text[tree_node_counter+i]!='\0'){
                    if(user_input[user_input_counter]!=tree_node_text[tree_node_counter+i]){
                        logic =false;
                        break ;
                    }
                    user_input_counter++;
                    i++;
                }
                if(logic&&user_input[user_input_counter]=='\0'){
                    return 1;
                }
            }
            tree_node_counter++;
        }
        return false ;
    }

    //search by writing whole question or portion of it O(N)
    bool decision_tree::search_by_text(string&t){
        queue<node*>q ;
        if(root){
            q.push(root) ;
            while(!q.empty()){
                node*ptr = q.front()  ;
                q.pop() ;
                if(ptr){
                    if(is_related(t,ptr->text)){
                        traverser = ptr ;
                        cout<<"\nFound : "<<traverser->text<<"\n" ;
                        return 1;
                    }
                    if(ptr->left){
                        q.push(ptr->left);
                    }
                    if(ptr->right){
                        q.push(ptr->right) ;
                    }
                }
            }
        }
        traverser =root ;
        return false ;
    }
    //search by the pattern leading to the quesion O(log2(N))
    bool decision_tree::search_by_pattern(string&pattern) {
        if(root){
            traverser= root;
            int i =0;
            while(i<pattern.size()){
                if((pattern[i]=='0'||pattern[i]=='1')){
                    if(pattern[i]=='0'){
                       if(traverser->left){
                            traverser=traverser->left ;
                       }
                       else{
                           traverser =root ;
                           return 0 ;
                       }
                    }
                    else{
                       if(traverser->right){
                            traverser=traverser->right ;
                       }
                       else{
                           traverser =root ;
                           return 0;
                       }
                    }
                }
                else{
                    cout<<"Invalid pattern" ;
                    traverser= root ;
                    return  0;
                }
                i++ ;
            }
            cout<<"\nFound : "<<traverser->text<<"\n" ;
            return 1 ;
        }
        return 0;
    }


    void clear_file(const std::string& filename) {
        std::ofstream file(filename, std::ios::out);
        // No need to write anything, opening the file in write mode clears it
    }

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

    //when saving a tree since is can be incomplete we have to keep track of nulls
    //so that logic of the decision tree isn't altred
    //when finding an empty node we add 2 nulls into the queue
    //to keep track of the nulls but this could lead to open loop
    //so tree is done saving when the queue is full of nulls
    //draw an incomplete tree and it will be understood why its used
    bool is_null_queue(queue<node*>&q){
        bool logic=false ;
        queue<node*> temp ;
        node*ptr =NULL;
        while(ptr==NULL&&!q.empty()){
            ptr =q.front();
            temp.push(ptr);
            q.pop();
        }
        if(ptr==NULL&&q.empty()){
            logic=true;
        }
        while(!q.empty()){
            ptr =q.front();
            temp.push(ptr);
            q.pop();
        }
        while(!temp.empty()){
            ptr =temp.front();
            q.push(ptr);
            temp.pop();
        }
        return logic;
    }
//save a tree in a file in breadth first fashion
void decision_tree::save(void) {
    if(root){
        string file_path;
        cout << "\nEnter file's path please make sure the file is created\n";
        cout<<">>";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
getline(cin,file_path);
        if (openFileForWriting(file_path)){ //if file exists
            std::ofstream file(file_path, std::ios::trunc); // Open file in write mode, which clears it
            queue<node*> q;
            if (root) {
                q.push(root);
        //when saving a tree since is can be incomplete we have to keep track of nulls
        //so that logic of the decision tree isn't altred
        //when finding an empty node we add 2 nulls into the queue
        //to keep track of the nulls but this could lead to open loop
        //so tree is done saving when the queue is full of nulls
        //draw an incomplete tree and it will be understood why its used
                while (!q.empty()&&!is_null_queue(q)) {
                    node* ptr = q.front();
                    q.pop();
                    if(ptr){
                        file << ptr->text << "\n"; // Write the line directly to the file
                        q.push(ptr->left);
                        q.push(ptr->right);
                    }
                    else {
                        //if null then 2 children are null
                        q.push(NULL);
                        q.push(NULL);
                        file << filling_string << "\n"; // Write the filling string directly to the file
                    }
                }
            }
            file.close(); // Close the file when done
            cout<<"\nSaved!";
            }
    }
    }

    //loads a tree from a file (the tree must be in breadth first fasion)
    //for empty nodes fill_string is put in the file but it won't be put into the tree
    //when loading from the file
    void decision_tree::load(void) {
        if(root){
            //if current tree isn't empty delete it first
            char choice;
            cout<<"\nCurrent tree contains data do you want to save it first?(y/n)\n>>" ;
            while(!getInput(choice)){
                cout<<"\n>>";
            }
            if(choice!='n'){
                save();
            }
            del_tree(root) ;
            root= NULL;
            traverser= NULL ;
        }
        //must provide complete file path and it must exist
        string file_path;
        cout << "\nEnter file's path please make sure the file is created\n";
        cout<<">>";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin,file_path);
        std::ifstream file(file_path); // Open file in read mode
        if (file.is_open()) { //if file exists
            string str;
            getline(file, str);
            if (str.empty()) {
                cout << "\nEmpty File\n";
                file.close(); // Close the file when done
                traverser= NULL;
                root =NULL;
                return;
            }
            root = get_node(str);
            queue<node*> q;
            q.push(root);
            while (!q.empty()) {
                node* ptr = q.front();
                q.pop();
                //the first empty line means that tree is loaded
                if (!getline(file, str)) {
                    cout << "\nFinished loading\n";
                    file.close(); // Close the file when done
                    return;
                }
                //if its a filling string its not added into the tree
                //note that instead the queue is filled with nulls so find first non-null item
                //and then the text found in the file is its left child
                if (str != filling_string) {
                    while(ptr==NULL){
                        ptr = q.front();
                        q.pop() ;
                    }
                    ptr->left = get_node(str);
                    ptr->left->parent = ptr;
                    q.push(ptr->left);
                }
                else{
                    q.push(NULL) ;
                }
                if (!getline(file, str)) {
                    cout << "\nFinished loading\n";
                    file.close(); // Close the file when done
                    return;
                }
                //same thing here but for right child
                if (str != filling_string) {
                    while(ptr==NULL){
                        ptr = q.front();
                        q.pop() ;
                    }
                    ptr->right = get_node(str);
                    ptr->right->parent = ptr;
                    q.push(ptr->right);
                }
                else{
                    //push null so that logic of decisions isn't altred
                    q.push(NULL) ;
                }
            }
            file.close(); // Close the file when done
            traverser= root;
        }
        else {
            cout << "\nFile doesn't exist";
            root= NULL;
            traverser=NULL;
        }

    }

    //interface for user to search
    bool decision_tree::search(void){
        int answer ;
        string input;
        cout<<"\ndo you want to look it up using text or by the pattern(aka 010001)\n" ;
        cout<<"\n(1:text)(2:pattern leading to the question/answer)(3:manually)\n>>";
        while(!getInput(answer)){
            cout<<"\n>>";
        }
        if(answer==1||answer==2||answer==3){
            if(answer==1){
                cout<<"\nEnter : ";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin,input) ;
                return search_by_text(input) ;
            }
            else if(answer==2){
                cout<<"\nEnter : ";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin,input) ;
                return search_by_pattern(input) ;
            }
            else if(answer==3){
                return move() ;
            }
            }
        else{
            cout<<"\nWrong input\n";

        }
        return 0 ;
    }

    //update a question in the tree
    void decision_tree::update(void) {
        if(search()){
            cout<<"\nquestion/answer is : ";
            cout<<"\nupdate the question/answer\nEnter :" ;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(cin,traverser->text) ;
            cout<<"\nsuccess!\n" ;
        }
        else{
            cout<<"\nnot found\n";
        }
        traverser= root;
    }

    //switch 2 subtrees or links
    void decision_tree::switch_nodes(void){
        char answer ;
        if(search()){
            cout<<"\nFound!\nthe question/answer : ";
            cout<<traverser->text;
            cout<<"\nAre you sure you want to switch the nodes(y/n)?"
                "\n(note that the subtree of each child will be switched aswell)\n>>";
            while(!getInput(answer)){
                cout<<"\n>>";
            }
            if(answer=='y'){
                node* temp = traverser->left ;
                traverser->left= traverser->right ;
                traverser->right = temp ;
                cout<<"\nSwitched successfully!\n" ;
            }
        }
        point_to_root() ;
    }

    //a node's decisions are switched
    void decision_tree::switch_answers(void){
        char answer ;
        if(search()){
            cout<<"\nFound!\nthe question/answer : ";
            cout<<traverser->text;
            cout<<"\nAre you sure you want to switch the Answers(y/n)?"
                "\n(note that the subtree of each child won't be switched)\n>>";
                while(!getInput(answer)){
                    cout<<"\n>>";
                }

            if(answer=='y'){
                if(traverser->left==NULL||traverser->right==NULL){
                        cout<<"\ncurrent node contains only one question";
                        cout<<"\nTo switch in this case use switch nodes\ndenied!";
                }
                else{
                    swap(traverser->left->text,traverser->right->text);
                }
            }
        }
        point_to_root() ;
    }

    //puts traverser on the root node
    void decision_tree::point_to_root(void){
        traverser= root ;
    }

    //insert one question only into the tree
    void decision_tree::insert(void) {
        if(root==NULL){
            promt_question();
        }
        else{
        int answer;
        cout<<"Search by text"
              "or traverse by yourself(1/2)?\n?";
        cout<<">>";
        while(!getInput(answer)){
            cout<<"\n>>";
        }
        if(answer==1){
            if(search()){
               promt_question();
            }
        }
        else if(answer==2){
            if(move()){
               promt_question();
            }
        }
        else{
            cout<<"\nNot added\n";
        }
    }
            traverser = root;
}


void decision_tree::interface(void){//interface for the user not designer of the tree (to interact with)
//move using traverser in the tree
    if(root){
        traverser= root;
        char curser;
            while(1){
                cout<<"current : "<<(traverser)->text;
                cout<<"\n(t:true)\n(f:false)\n(b:back to previous question)\n(r:back to root question)\n(q:quit)\n>>";
                char curser = getch();
                fflush(stdin);
                switch(curser){
                    case 'b' :{
                        if((traverser)->parent)
                            (traverser)= (traverser)->parent;
                        }break;

                    case 'f' :{
                        if((traverser)->left)
                            (traverser)= (traverser)->left;
                        }break;

                    case 't' :{
                        if((traverser)->right)
                            (traverser)=(traverser)->right;
                        }break;

                    case 'q' :{
                        traverser= root;
                        return;
                    }

                    case 'r' :{
                        traverser= root;
                    }break;

                    case '\r':
                        return ;
                    }

                }
            }
        else{
            cout<<"Can't move in an empty tree";
        }
    }

    //to be tested when i get free time
    bool decision_tree::is_left(void){
        return(traverser->parent&&traverser->parent->left==traverser);
    }

    void  decision_tree::change_parent_child(node*other){
        if(is_left()){
            traverser->parent->left=other;
         }
         else if(traverser->parent){
            traverser->parent->right=other;
         }
    }

    void decision_tree::del_traverser_with_children(void){
        if(traverser){
            del_tree(traverser->left) ;
            traverser->left=NULL ;
            del_tree(traverser->right) ;
            traverser->right=NULL;
            if(traverser==root){
                delete root ;
                root = NULL;
                traverser=NULL;
            }
            else{
                change_parent_child(NULL) ;
                delete traverser ;
                traverser= NULL;
                traverser= root;
            }
        }
    }
/*
    bool decision_tree::is_same_subtree(node*subtree_root){
        node*p = traverser;
        while(p){
            if(p==subtree_root){
                return true ;
            }
            p=p->parent ;
        }
        return false ;
    }
*/
    void decision_tree::move_left_subtree(node*pleft){
        if(pleft){
            cout<<"\nnow you hold left subtree\ncurrent :";
            cout<<pleft->text;
            do{
                cout<<"\nwhere to insert it?\n" ;
                cout<<"\nif you see this message again it means\n"
                    "that either question/answer doesn't exist or the left child of it is full\n";
            }while(!search()||traverser->left!=NULL);
            traverser->left=pleft;
            pleft->parent= traverser;
        }

    }
    void decision_tree::move_right_subtree(node*pright){
        if(pright){
            cout<<"\nnow you hold right subtree\ncurrent :";
            cout<<pright->text;
            do{
                cout<<"\nwhere to insert it?\n" ;
                cout<<"\nif you see this message again it means\n"
                    "that either question/answer doesn't exist or the right child of it is full\n";
            }while(!search()||traverser->right!=NULL);
            traverser->right=pright;
            pright->parent= traverser;
        }

    }

    void  decision_tree::remove(void) {
        if(search()){
            if(traverser==root){
                int choice ;
                cout<<"\nThis is the root node\n";
                cout<<"\nnew root can only be left or right child\n";
                cout<<"(1-left)(2-right)(3-quit)(4-delete whole tree)";
                while(!getInput(choice)){
                    cout<<"\n>>";
                }
                if(cin.fail()) {
                    cin.clear(); // clear the error state
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the bad input
                }
                switch(choice){
                case 1:{
                    if(traverser->left!=NULL){
                        node *temp = root;
                        node*pright = root->right ;
                        root = root->left;
                        delete temp ;
                        temp= NULL;
                        root->parent= NULL ;
                        int choice ;
                        if(pright){
                            cout<<"\nRoot has right child\n";
                            cout<<"Right : "<<pright->text<<"\n(1-move to another node)(2-delete the whole subtree)";
                            cout<<">>";
                            while(!getInput(choice)){
                                cout<<"\n>>";
                            }
                            if(choice==1){
                                move_right_subtree(pright) ;
                            }
                            else{
                                del_tree(pright);
                            }
                        }

                    }
                    else{
                        cout<<"root can't be NULL(left child doesn't exist to be a root)";
                    }
                 }break;
                 case 2:{
                 if(traverser->right!=NULL){
                        node *temp = root;
                        node*pleft = root->left ;
                        root = root->right;
                        delete temp ;
                        temp =NULL;
                        root->parent= NULL ;
                        int choice ;
                        if(pleft){
                            cout<<"Root has left child\n";
                            cout<<"Right : "<<pleft->text<<"\n(1-move to another node)(2-delete the whole subtree)";
                            cout<<">>";
                            while(!getInput(choice)){
                                cout<<"\n>>";
                            }
                            if(choice==1){
                                move_left_subtree(pleft) ;
                            }
                            else{
                                del_tree(pleft);
                            }
                        }

                    }
                    else{
                        cout<<"root can't be NULL(right child doesn't exist to be a root)";
                    }
                 }break;
                 case 3:{
                    return ;
                 }break;
                 case 4:{
                    del_tree(root);
                    root =NULL ;
                    traverser= NULL ;
                 }break;
                 default:{
                    return ;
                 }
            }
            return ;
            }
            if(traverser->left||traverser->right){
                int choice ;
                cout<<"\nThe question/answer you want't to remove has children\n";
                cout<<"(1-remove both)\n(2-add them separately to other nodes of your choice)" ;
                while(!getInput(choice)){
                    cout<<"\n>>";
                }
                if(choice==1){
                    del_traverser_with_children();
                }
                else if(choice==2){
                    node*pleft=traverser->left;
                    node*pright =traverser->right;
                    change_parent_child(NULL) ;
                    delete traverser;
                    traverser=root;
                    move_left_subtree(pleft);
                    move_right_subtree(pright);
                }
            }
            else{
                change_parent_child(NULL) ;
                delete traverser;
                traverser=root;
            }
        }
        else{
            cout<<"\nquestion/answer doesn't exist in the tree\n" ;
        }

    }//remove a question from the tree (we'll see )


