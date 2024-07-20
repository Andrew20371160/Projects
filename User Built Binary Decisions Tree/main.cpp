#include "tree_list.h"


void create(tree_list&tree){
    while(1){
        int choice=0;
        cout<<"\n1---Add a new tree\n";
        cout<<"\n2---Edit a tree\n";
        cout<<"\n3---Show list of trees\n";
        cout<<"\n4---Move through the list of trees\n";
        cout<<"\n5---Delete a tree\n";
        cout<<"\n6---Back to main menu\n" ;
        cout<<">>";
        while(!getInput(choice)){
            cout<<"\n>>";
        }
        switch(choice){
        case 1:{
            tree.add();
            tree.engineer_interface();
        } break;
        case 2:{
            if(tree.search()){
               tree.engineer_interface() ;
            }
        }break;
        case 3:{
            tree.print();
        }break;
        case 4:{
            tree.move() ;
        }break ;
        case 5:{
            if(tree.search()){
                char ch ;
                cout<<"\nAre you sure you want to delete current tree(y/n)?\n";
                cout<<tree.get_traverser() ;
                while(!getInput(ch)){
                    cout<<"\n>>";
                }
                if(ch!='n'){
                    tree.del_list_node() ;
                }
            }
        }break;
        case 6:{return ;}
        default:{
            choice= 0;
        }
        }
    }
}

void user(tree_list&tree){
    while(1){
            int choice=0;
            cout<<"\n1---Add a new tree\n";
            cout<<"\n2---Search for a tree\n";
            cout<<"\n3---Show list of trees\n";
            cout<<"\n4---Move through the list of trees\n";
            cout<<"\n5---Delete a tree\n";
            cout<<"\n6---Back to main menu\n" ;
            cout<<">>";
            while(!getInput(choice)){
                cout<<"\n>>";
            }
            switch(choice){
            case 1:{
                tree.add();
                tree.user_interface() ;
            }break;
            case 2:{
                if(tree.search()){
                   tree.user_interface() ;
                }
            }break;
            case 3:{
                tree.print();
            }break;
            case 4:{
                tree.move() ;
            }break ;
            case 5:{
                if(tree.search()){
                    char ch ;
                    cout<<"\nAre you sure you want to delete current tree(y/n)?\n";
                    cout<<tree.get_traverser() ;
                    while(!getInput(ch)){
                        cout<<"\n>>";
                    }
                    if(ch!='n'){
                        tree.del_list_node() ;
                    }
                }
            }break;
            case 6:{return ;}
            default:{
                choice= 0;
            }
        }
    }

}


int main()
{

    tree_list tree;
    int choice ;
    while(1){
        cout<<"\n1---Engineer Mode\n" ;
        cout<<"\n2---User Mode\n";
        cout<<"\n3---Quit\n";
        cout<<">>";
        while(!getInput(choice)){
            cout<<"\n>>";
        }
        switch(choice){
            case 1:{
                create(tree) ;
            }break;
            case 2:{
                user(tree);
            }break;
            case 3:{
                return 0  ;
            }
        }
    }
    return 0;

}


