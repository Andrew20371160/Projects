#ifndef _node_h_
#define _node_h_
    //Includes
    #include <string>
    #include <iostream>
    /*
    the following class is to abstract linking operations
    of a node from calculus_tree class
    */
    class node
    {
        private:
            template<typename DataType>
            friend class calculus_tree;
            //a symbol can be 3.5515, v1,x,any_name
            std::string  symbol ;
            //links
            node *parent ;
            node *left ;
            node *right ;

            /*
            this function disconects self or this from it's parent
            but it's children are still with him
            */
            bool disconnect_self(void);
            /*
            where (this) must have a parent
            this function adds a new child to parent of (this)
            or a new sibling to (this)
            */
            bool append_next(const std::string &);
            /*
            this function adds a child to (this)
            in the order -> left then right
            if it doesn't have place then it doesn't
            */
            bool append_child(const std::string &);
            /*
                if (this) has a parent then this function
                disconnects (this) from its parent
                then assign a new parent to it
                else it just assigns a new parent to it
            */
            bool append_parent(const std::string &);
            /*
            previous operations but done one nodes or subtrees
            */
            /*
            this function disconnects src_root from it's parent
            then adds it to children of parent of (this)
            if applicable else it doesn't
            */
            bool append_next(node*&src_root);
            /*
            this function disconnects src_root from it's parent
            then adds it to children of (this)
            if applicable else it doesn't
            */
            bool append_child(node*&src_root);
            /*
            this function disconnects (this) from it's parent
            then adds it to children of src_root if applicable
            */
            bool append_parent(node*&src_root);

            /*
            op becomes parent of (this)
            and parent (this) becomes parent of (op)
            check below diagram
            */
            /*
            p1                                p1
            |     ->exchange_parent(p2)->     |
            this                              p2
                                              |
                                            this
            */
            bool exchange_parent(const std::string &op) ;
        public:
            node(const std::string &);
    };
#endif
