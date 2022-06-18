#pragma once

#include <iostream>

#include "../../Task2_Parser/AST/statements/AST_block.h"
#include "../../Task2_Parser/AST/others/AST_formal_params.h"
#include "../../Task2_Parser/AST/others/AST_type.h"

enum class Variable_Type{
    VAR,
    FUNC
};

class Variable{
    public:
        //keeping track of whether the variable has a value or is a function call
        Variable_Type var_type;

        //to keep track of the variable type: either Float, Int, Bool or Char 
        Type value_type;
        
        //to keep track of data type of parameters
        vector<Type> params_type;

        Variable(Variable_Type var_type, Type value_type, vector<Type> params_type){
            this->var_type = var_type;
            this->value_type = value_type;
            this->params_type = params_type;
        }

        //if no data type of parameters is given 
        Variable(Variable_Type var_type, Type value_type){
            this->var_type = var_type;
            this->value_type = value_type;
            //setting params_type to empty vector
            this->params_type = vector<Type>();
        }


        //for Interpreter Execution Pass:
        float float_val;
        int int_val;
        bool bool_val;

        AST_formal_params *f_params;
        AST_block *func_body;

        string toString(){
            string s;

            if(value_type == Type::Float){
                s = s + "Float";
            }else if (value_type == Type::Int){
                s = s + "Int";
            }else if(value_type == Type::Bool){
                s = s + "Bool";
            }else if(value_type == Type::Char){
                s = s + "Char";
            }

            s = s + " ";
        }
};