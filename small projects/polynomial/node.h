#ifndef NODE_H
#define NODE_H
#include <math.h>
class Node
{
private:
    int exp;
    double coef;
    Node* next;
    friend class Polynomial; /* Allow Polynomial Access */
    friend Node *get_node(double,int) ;
};


#endif // NODE_H
