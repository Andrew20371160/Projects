    #include "node.h"

    using namespace std;
    node::node(const string &_symbol){
        symbol = _symbol ;
        parent = NULL;
        left =NULL ;
        right = NULL;
    }
    //appends symbol as a new sibling to this
    //and a new child to parent of this
    //must have a parent to do the operation
    //so that the tree structure isn't ruined
    bool node::append_next(const string &symbol){
        if(parent&&parent->right==NULL){
            node*new_node = new node(symbol);
            if(new_node){
                new_node->parent= parent;
                parent->right = new_node ;
                return true;
            }
        }
        return false;
    }
    /*
    appends symbol as a new child to this
    */
    bool node::append_child(const string &symbol){
        if(left==NULL||right==NULL){
            node*new_node = new node(symbol);
            if(new_node){
                if(left==NULL){
                    left= new_node ;
                }
                else{
                    right= new_node ;
                }
                new_node->parent= this ;
                return true ;
            }
        }
        return false ;
    }
    /*
    disconnects this from his parent and his siblings
    not from his children
    */
    bool node::disconnect_self(void) {
        if(parent){
            if(parent->left==this){
                parent->left=NULL;
            }
            else{
                parent->right=NULL ;
            }
            parent=NULL ;
            return true ;
        }
        return false;
    }
    /*
    symbol is a new parent and his first child becomes this
    this function disconnects this from its sibling and assign a new parent
    to it which is symbol
    */
    bool node::append_parent(const string&symbol){
        node*new_parent = new node(symbol);
        if(new_parent){
            //disconnect this from its parent and its sibling
            this->disconnect_self();
            //then append this as the new child of symbol
            this->parent = new_parent ;
            new_parent->left= this ;
            return true;
        }
        return false ;
    }

    /*
    previous operations but on pointers
    */
    /*
    append src_root as a sibling to this
    and a child of its parent
    so first disconnect src_root from his parent and siblings
    assign his new parent as parent of this
    */
    bool node::append_next(node*&src_root){
        if(parent&&parent->right==NULL&&src_root){
            src_root->disconnect_self() ;
            //then connect src_root as a new sibling of this
            src_root->parent= parent ;
            parent->right = src_root ;
            return true ;
        }
        return false ;
    }
    /*
    append src_root as a child to this
    so first disconnect src_root from his parent and siblings
    then does the connections
    */
    bool node::append_child(node*&src_root){
        if(src_root&&(left==NULL||right==NULL)){
            src_root->disconnect_self() ;
            if(left==NULL){
                left= src_root ;
            }
            else{
                right= src_root ;
            }
            src_root->parent= this ;
            return true ;
        }
        return false ;
    }
    //this function separates this from his parent's list
    //and put this into the childrent of src_root
    //if null then its new parent is null
    bool node::append_parent(node*&src_root){
        if(src_root==NULL){
            this->disconnect_self() ;
        }
        else if(src_root->left==NULL||src_root->right==NULL){
            this->disconnect_self();
            node*temp = this ;
            src_root->append_child(temp) ;
        }
        return true ;
    }
    /*
    //where op is new parent of last op
    //and op is new children to parent of last op
    //and then last op becomes parent of last op
    last_op->exchange_parent(op);
    */
    bool node::exchange_parent(const string&op) {
         if(parent==NULL){
            return this->append_parent(op) ;
         }
         else{
            node*new_parent = new node(op);
            if(new_parent){
                node*gparent  =parent ;
                this->disconnect_self();
                gparent->append_child(new_parent);
                node*temp = this;
                new_parent->append_child(temp) ;
                return true ;
            }
        }
         return false;
    }
