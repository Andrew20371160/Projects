#include "functions_and_known_constants.h"

    using namespace std;


    /*
    switches through the known function using function code
    then returns the value
    */
    template<typename DataType>
    DataType evaluate_function(const int fn,const DataType var, const  DataType base) {
        switch(fn){
            case EXP: return exp(var);
            case LN: return log(var);
            case SIN: return sin(var);
            case COS: return cos(var);
            case TAN: return tan(var);
            case SQRT: return pow(var,0.5);
            case ABS : return abs(var);
            case LOG : return log(var) / log(base);
            case SEC: return DataType(1)/cos(var) ;
            case CSC:return DataType(1)/sin(var) ;
            case COTAN: return DataType(1)/tan(var);
            case ASIN: return asin(var);
            case ACOS: return acos(var);
            case ATAN: return atan(var);
            case SINH: return sinh(var);
            case COSH: return cosh(var);
            case TANH: return tanh(var);
            case ASINH: return asinh(var);
            case ACOSH: return acosh(var);
            case ATANH: return atanh(var);
            #ifdef COMPLEX_MODE
                case IMG :return complex<long double>(0,1)*var;
            #endif
        }
    }

    template<typename DataType>
    DataType evaluate_constant(const string&symbol){
        int const_code = is_known_constant(symbol,0);
        switch(const_code){
            case PI :return DataType(M_PI) ;
            case E: return DataType(exp(1)) ;

            case INF_ERR:{
                return DataType(tan(M_PI/2));
            }
            case NAN_ERR:{
                return DataType(tan(M_PI/2))/DataType(tan(M_PI/2));
            }
            #ifdef COMPLEX_MODE
                case I : return DataType(0,1) ;
            #endif

        }
    }

    template<typename DataType>
    DataType evaluate_operator(char op,const DataType&left_operand,const DataType&right_operand){
       switch(op){
            case '+':return left_operand+right_operand ;
            case '-':return left_operand-right_operand ;
            case '*':return left_operand*right_operand ;
            case '/':return left_operand/right_operand ;
            case '^':return pow(left_operand,right_operand);
        }
    }
