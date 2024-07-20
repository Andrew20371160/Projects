#include "tree_list.h"

//allocate memory for a new node in the list
list_node* tree_list:: get_list_node(string&tree_name){
    //allocate for list node
    list_node*new_tree =new list_node ;
    //assign the name
    new_tree->name= tree_name ;
    //allocate memory for the new tree
    new_tree->dtree=new decision_tree;
    //links of the list
    new_tree->next=new_tree ;
    new_tree->prev=new_tree ;
    return new_tree ;
}

    tree_list::tree_list(){
        tail=NULL;
        traverser =NULL;
    }

//move through list of nodes
//move is used here as a search mechanism if the user desires this tree
//then true is returned and so the tree can be used
bool tree_list::move(void){
    if(tail){
        if(traverser==NULL){
            traverser= tail->next;
        }
        char curser;
            while(1){
                cout<<"\n(Enter->stops at current)\n(a->previous)\n(d->next)\n(s->show the whole list of trees)\n(q->quit)\n>>";
                char curser = getch();
                fflush(stdin);
                switch(curser){
                    case 'a' :{
                            traverser= traverser->prev;
                        }break;

                    case 'd' :{
                            traverser=traverser->next;
                        }break;

                    case 's':{
                        print();
                    }break;

                    case 'q' :{
                        traverser=tail->next;
                        return false;
                    }
                    case '\r':
                        return true;
                    }
                    cout<<"current : "<<(traverser)->name;
                }
            }
        else{
            cout<<"\nCan't move in an empty list\n";
            return 0;
        }
    }
    //destructor
    tree_list::~tree_list(){
        if(tail){
            list_node *ptr1 = tail->next ;
            tail->next=NULL ;
            list_node *ptr2 = ptr1->next ;
            while(ptr1){
                //first delete tree inside the node
                //printing the tree's name so that if user wants to save it in a file
                //check destructor of decision tree to know more
                cout<<"\nTree's Name : \n"<<ptr1->name;
                //delete ptr1->dtree ;
                delete ptr1->dtree;
                ptr1->dtree =NULL;
                delete ptr1 ;
                ptr1 =NULL;
                ptr1= ptr2 ;
                if(ptr2){
                   //stop moving when ptr2 is null
                   ptr2 = ptr2->next;
                }
            }
        }
    }
    //add a new tree
    //for engineer afterwards the engineer's interface is called
    //for user the user's interface is called
    void tree_list::add(void){
        string tree_name;
        cout<<"\nEnter the new tree's name\n";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin,tree_name);
        if(tail==NULL){
            tail = get_list_node(tree_name);
        }
        else{
            list_node*new_tree=get_list_node(tree_name);
            new_tree->next= tail->next;
            new_tree->prev=tail;
            tail->next->prev=new_tree;
            tail->next=new_tree;
            tail = new_tree;
        }
        traverser =tail;
    }

    //user can't alter the tree
    void tree_list::user_interface(void){
        if(tail){
            if(traverser){
                while(1){
                    int choice;
                    cout<<"\n1---Interface with the decision tree\n";
                    cout<<"\n2---load a tree\n";
                    cout<<"\n3---Move Through the tree\n" ;
                    cout<<"\n4---Search for a node in the tree\n" ;
                    cout<<"\n5---Show the tree\n" ;
                    cout<<"\n6---Quit the current tree\n";
                    cout<<"\n>>";
                    while(!getInput(choice)){
                        cout<<"\n>>";
                    }
                    switch(choice){
                        case 1:{
                            traverser->dtree->interface();
                        }break;
                        case 2:{
                            traverser->dtree->load();
                        }break;
                        case 3:{
                            traverser->dtree->move();
                        }break;
                        case 4:{
                            traverser->dtree->search();
                        }break;
                        case 5:{
                            traverser->dtree->print();
                        }break;
                        case 6:{
                            return ;
                        }break;
                        default:{
                            choice= 0 ;
                        }
                    }
                }
            }
        }
    }
    //search for first match
    bool tree_list::search_by_text(void){
        if(tail){
            string tree_name;
            cout<<"\nEnter the tree's name\n";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
getline(cin,tree_name);
            traverser = tail->next;
            do{
                if(is_related(tree_name,traverser->name)){
                    cout<<"\nFound!\n" ;
                    return 1;
                }
                traverser =traverser->next;
            }while(traverser!=tail->next);
            cout<<"\nNot found\n";

            traverser=tail;
            return 0;
        }
        return 0 ;
    }
    //search mechanism if found it returns true
    bool tree_list::search(void){
        if(tail){
            int choice2 =0;
            cout<<"\n1---search by text\n";
            cout<<"\n2---search manually\n";
            cout<<"\n3---Back to main menu\n";
            while(!getInput(choice2)){
                cout<<"\n>>";
            }
            switch(choice2){
                case 1:{
                    return search_by_text();
                }break;
                case 2:{
                    return move() ;
                }break;
                default:{
                    return 0;
                }
                }
            }
            return 0;
        }
    //delete a tree from the list of trees
    void tree_list::del_list_node(void){
        if(tail){
            if(traverser){
                if(traverser->next==traverser){
                    delete tail;
                    tail= NULL ;
                    traverser=NULL;
                }
                else{
                    list_node*ptr =tail->next;
                    while(ptr->next!=traverser){
                        ptr = ptr->next;
                    }
                    list_node*temp= traverser;
                    if(traverser==tail){
                        ptr->next=traverser->next;
                        tail= ptr->next;
                    }
                    cout<<"\nTree Name : "<<temp->name<<endl;
                    delete temp->dtree;
                    delete temp;
                }
             }
            else{
                cout<<"\nTree doesn't exist\n";
            }
            traverser =tail;
        }
    }

    //engineer is more privileged and can alter delete or do anything
    void tree_list::engineer_interface(void){
        if(tail){
            if(traverser){
                while(1){
                    int choice;
                    cout<<"\nTree's name : "<<traverser->name<<"\n";
                    cout<<"\n1---insert multiple Questions/Answers\n";
                    cout<<"\n2---Insert one Questions/Answers only\n";
                    cout<<"\n3---Save the tree\n";
                    cout<<"\n4---Load a tree from a file\n";
                    cout<<"\n5---Update Questions/Answers\n";
                    cout<<"\n6---Delete Questions/Answers\n";
                    cout<<"\n7---Test user interface\n";
                    cout<<"\n8---Move Through the tree\n" ;
                    cout<<"\n9---Search for a node in the tree\n" ;
                    cout<<"\n10---Show the tree\n" ;
                    cout<<"\n11---Switch subtrees of a node\n";
                    cout<<"\n12---Switch Answers/Questions of a node\n";
                    cout<<"\n13---Quit engineering current tree\n";
                    cout<<"\n\n>>";
                    while(!getInput(choice)){
                        cout<<"\n>>";
                    }
                    switch(choice){
                        case 1:{
                            traverser->dtree->construct();
                        }break;
                        case 2:{
                            traverser->dtree->insert();
                        }break;
                        case 3:{
                            traverser->dtree->save();
                        }break;
                        case 4:{
                            traverser->dtree->load();
                        }break;
                        case 5:{
                            traverser->dtree->update();
                        }break;
                        case 6:{
                            traverser->dtree->remove();
                        }break;
                        case 7:{
                            traverser->dtree->interface();
                        }break;
                        case 8:{
                            traverser->dtree->move();
                        }break;
                        case 9:{
                            traverser->dtree->search();
                        }break;
                        case 10:{
                            traverser->dtree->print();
                        }break;
                        case 11:{
                            traverser->dtree->switch_nodes();
                        }break;

                        case 12:{
                            traverser->dtree->switch_answers();
                        }break;

                        case 13:{
                            return ;
                        }break;
                        default:{
                            choice= 0 ;
                        }
                    }
                }
            }
        }
    }

    //display names of each tree
    void tree_list::print() {
        if(tail){
            traverser=tail->next;
            cout<<endl  ;
            do{
                cout<<traverser->name;
                traverser=traverser->next;
                if(traverser!=tail->next){
                    cout<<" -> ";
                }
            }while(traverser!=tail->next);
        }
    }
    //returns name of the tree traverser is pointing at
    string tree_list::get_traverser(void){
        return traverser->name;
    }
