#ifndef _preprocessor_h_
#define _preprocessor_h_
#include "functions_and_known_constants.h"
//code for each token type
//where operator is +-/*^ only
//error for numbers entered incorrectly like 3.-1 , 3. 2
enum{
    ERROR=-1,VAR_CONST,FUNCTION,OPERATOR,OPEN_BRACKET,CLOSE_BRACKET
};
    //the following class handles preprocessing of an expression and to check if there is an error in the expression or not
    class preprocessor{
        private:
            //returns the code of the extracted token and updates open_brackets_c
            //increments or decrements it if it finds ( or ) respectively
            unsigned int token_type(const std::string &token, int &open_brackets_c)const;
            /*
                based on previous token type
                these functions check based on mathematical expressions rules
                if it's a valied token or not
                for ex: you can't have x+/2 or (expression)2
            */
            /*
            mathematical expression rules and how this class fixes some issues
                1-opening brackets must match closing ones
                2-2x,xsin(x),x(2) , x2 ->left*right
                3-xy is considered a variable name not x*y user must indicate
                4-a function must be followed by ( even if it's one  operand like sinx
                5-operand is a token and operator is another token
                6-(x+y)(z+5)->(x+y)*(z+5)
                7- +- are the only operators that can be used to start an expression
            */
            //they also update ret_exp with operators sometimes
            //for ex: if previous token is x, and the new token is (
            //ret_exp = ret_exp+"*" (it adds the * operator to ret_exp so that tree generation doesn't crash)
            bool valid_var_const_token(unsigned int previous_token, const std::string &token, std::string &ret_exp )const;

            bool valid_function_token(unsigned int previous_token, const std::string &token, std::string &ret_exp )const;

            bool valid_open_bracket_token(unsigned int previous_token, const std::string &token, std::string &ret_exp )const;

            bool valid_close_bracket_token(unsigned int previous_token, const std::string &token, std::string &ret_exp )const;

            bool valid_operator_token(unsigned int previous_token, const std::string &token, std::string &ret_exp )const;
            //skips spaces from starting position and updates start to the new position
            void skip_spaces(const std::string &expression,unsigned int &start)const;
            //extracts an operand at start position and updates start to start of new operand
            std::string  preprocess_extract(const std::string &expression,unsigned int &start)const;


        public :
            //empty constructor
            preprocessor(void) ;
            //takes expression as an input and then preprocesses it and returns the processed expression
            std::string  prepare_exp(const std::string &exp)const;

    };

#endif
