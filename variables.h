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
            
            //appending the type to the string
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

            //if the variable is a function
            if(var_type == Variable_Type::FUNC){
                //appending to string
                s = s + "Function";

                s = s + "\t(";
                
                //getting the size of the function's parameters
                int params_size = params_type.size();

                //looping through the function's parameters 
                //and appending the type to the string
                for(int i = 0; i < params_size; i++){
                    if(params_type.at(i) == Type::Float){
                        s = s + "Float";
                    }else if(params_type.at(i) == Type::Int){
                        s = s + "Int";
                    }else if(params_type.at(i) == Type::Bool){
                        s = s + "Bool";
                    }else if(params_type.at(i) == Type::Char){
                        s = s + "Char";
                    }
                    
                    //adding a comma between each type
                    if(i != params_size-1){
                        s = s + ", ";
                    }
                    //addign the close bracket to the string 
                    s = s + ")";
                }
            }else{
                //if the variable is a variable with a value
                s = s + "Variable";
            }

            //returning the string
            return s;
        }
};