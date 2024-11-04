#ifndef _functions_and_known_constants_h_
#define _functions_and_known_constants_h_
    // Uncomment the following line to enable complex mode

    //#define COMPLEX_MODE 1


    //Includes
    #include <iostream>
    #include <string>
    #include <math.h>
    #include <cmath>
    #include <complex>
    #include <limits>
    /*
    you can add a new constant or function following these steps
    1-increment constants_count or functions_count respectively (both in COMPLEX_MODE and normal mode)
    2-add enum value accordingly say you wanna add sigmoid then add the name SIGMOID to functions_codes (both in COMPLEX_MODE and normal mode)
    3-add a string representing that function or constant to the according array (both in COMPLEX_MODE and normal mode)
    4-don't add a function before log
    5-head to the functions_and_known_constants.tpp then add evaluation of it
    6-then head to calculus_tree.cpp
    and add the differeniation of that function in diff_function
    string calculus_tree<DataType>::diff_function(const int fn,node*ptr,const string&var ){

    */

    #ifdef COMPLEX_MODE

        const int functions_count =21 ;
        const int constants_count =5 ;
        const int keywords_count =26;

        enum  functions_codes{
            //don't add functions' codes here
            LOG,
            SQRT,ABS,SIN,COS,TAN,
            SEC,CSC,COTAN,ASIN,ACOS,
            ATAN,EXP,LN,SINH,COSH,
            TANH,ASINH,ACOSH,ATANH,IMG,
            //add new functions' codes here
        };

        enum constants_codes{
            PI,E,I,
            INF_ERR,NAN_ERR
            //add new constants codes here
        }
        /*
        functions must be followed by parenthese
        for log you just attach base to it
        for ex:log2
        by default it's log10

        pi,i,e are known constants no need to write the value explicitly
        */
        const std::string  known_functions[functions_count]={
                "log",
                "sqrt","abs","sin","cos","tan",
                "sec","csc","cotan","asin","acos",
                "atan","exp","ln","sinh","cosh",
                "tanh","asinh","acosh","atanh","img",
                //add new functions here
            };
        const std::string  known_constants[constants_count]={
                                                "pi","e","i",
                                                "inf","nan"
                                                //add new constants here
                                            };

    #else
        //normal mode
        const int functions_count =20 ;
        const int constants_count =4 ;
        const int keywords_count =24;

        enum  functions_codes{
            LOG,
            SQRT,ABS,SIN,COS,TAN,
            SEC,CSC,COTAN,ASIN,ACOS,
            ATAN,EXP,LN,SINH,COSH,
            TANH,ASINH,ACOSH,ATANH,
        };

        enum constants_codes{
            PI,E,
            INF_ERR,NAN_ERR
        };
        /*
        functions must be followed by parenthese
        for log you just attach base to it
        for ex:log2
        by default it's log10

        pi,i,e are known constants no need to write the value explicitly
        */
        const std::string  known_functions[functions_count]={
                                                "log",
                                                "sqrt","abs","sin","cos","tan",
                                                "sec","csc","cotan","asin","acos",
                                                "atan","exp","ln","sinh","cosh",
                                                "tanh","asinh","acosh","atanh",
                                                //add new functions here
                                            };
        const std::string  known_constants[constants_count]={
                                                "pi","e",
                                                "inf","nan"
                                                //add new constants here
                                            };

    #endif
    /*
    extracts operand at pos then returns it's enum value if exists
    else it returns -1
    */
    int is_known_function(const std::string &expression,unsigned int pos ) ;
    /*
    returns true if expression[pos] is an operator
    */
    bool is_op(const std::string &expression,unsigned int pos ) ;
    //checks if var is a number
    //with decimal points and signs
    bool is_num(const std::string  &var);
    //returns enum value if operand starting at pos
    //else -1
    int is_keyword(const std::string &expression,unsigned int  pos);
    //returns enum value if an operand starting at pos if it's a known constant
    //else -1
    int is_known_constant(const std::string &var,unsigned int pos ) ;

    template<typename DataType>
    DataType evaluate_function(const int fn,const DataType var, const  DataType base);
    template<typename DataType>
    DataType evaluate_constant(const std::string&symbol);
    template<typename DataType>
    DataType evaluate_operator(char op,const DataType&left_operand,const DataType&right_operand);

    #include "functions_and_known_constants.tpp"

#endif
