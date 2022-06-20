#pragma once

#include "../Task1_Table-driven_Lexer/lexer.h"

#include "AST/AST_node.h"
#include "AST/AST_node_expression.h"
#include "AST/AST_node_statement.h"
#include "AST/AST_node_operator.h"

//literals
#include "AST/expressions/factors/literals/AST_bool.h"
#include "AST/expressions/factors/literals/AST_int.h"
#include "AST/expressions/factors/literals/AST_float.h"
#include "AST/expressions/factors/literals/AST_char.h"

//factors
#include "AST/expressions/factors/AST_identifier.h"
#include "AST/expressions/factors/AST_function_call.h"
#include "AST/expressions/factors/AST_sub_expression.h"
#include "AST/expressions/factors/AST_unary.h"

//expressions
#include "AST/expressions/AST_actual_params.h"
#include "AST/expressions/AST_expression.h"
#include "AST/expressions/AST_simple_expression.h"
#include "AST/expressions/AST_term.h"

//statements
#include "AST/statements/AST_variable_declaration.h"
#include "AST/statements/AST_assignment.h"
#include "AST/statements/AST_print.h"
#include "AST/statements/AST_if.h"
#include "AST/statements/AST_for.h"
#include "AST/statements/AST_while.h"
#include "AST/statements/AST_return.h"
#include "AST/statements/AST_function_declaration.h"
#include "AST/statements/AST_block.h"

//operators
#include "AST/operators/AST_multiplicative_operator.h"
#include "AST/operators/AST_additive_operator.h"
#include "AST/operators/AST_relational_operator.h"
#include "AST/operators/AST_unary_operator.h"

//others
#include "AST/others/AST_type.h"
#include "AST/others/AST_formal_param.h"
#include "AST/others/AST_formal_params.h"

using namespace std;

class Parser{
    public:
        //constructor
        Parser();

        //class destructor
        ~Parser();

        vector<AST_node*> *parse_AST();

        // void clear_AST(){
        //     AST->clear();
        // }
    
    private:
        Token current_tok;
        Lexer lexer;

        vector<AST_node*> *AST;

        vector<AST_node*> *parse_AST();

        AST_node_statement *parse_statement();

        AST_node_factor *parse_factor();

        //parsing factors
        AST_node_literal *parse_literal();
        AST_identifier *parse_identifier();
        AST_function_call *parse_function_call();
        AST_sub_expression *parse_sub_expression();
        AST_unary *parse_unary();

        //parsing expressions
        AST_actual_params *parse_actual_params(vector<AST_node_expression*> *actual_params);
        //AST_actual_params *parse_actual_params();
        AST_node_expression *parse_term();
        AST_node_expression *parse_simple_expression();
        AST_node_expression *parse_expression();

        //parsing operators
        AST_additive_operator *parse_additive_operator();
        AST_multiplicative_operator *parse_multiplicative_operator();
        AST_unary_operator *parse_unary_operator();
        AST_relational_operator *parse_relational_operator();

        //parsing statements
        AST_variable_declaration *parse_variable_decl();
        AST_assignment *parse_assignment();
        AST_print *parse_print();
        AST_if *parse_if();
        AST_for *parse_for();
        AST_while *parse_while();
        AST_return *parse_return();
        AST_function_declaration *parse_function_decl();
        AST_block *parse_block();

        //parsing others
        AST_type *parse_type();
        AST_formal_param *parse_formal_param();
        AST_formal_params *parse_formal_params(vector<AST_formal_param*> *f_params);
};