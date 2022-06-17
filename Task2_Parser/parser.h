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

        void clear_AST(){
            AST->clear();
        }
    
    private:
        Token current_tok;

        vector<AST_node*> *AST;

        vector<AST_node*> *Parser::parse_AST();

        AST_node_statement *Parser::parse_statement();

        //parsing factors
        AST_node_literal *Parser::parse_literal();
        AST_identifier *Parser::parse_identifier();
        AST_function_call *Parser::parse_function_call();
        AST_sub_expression *Parser::parse_sub_expression();
        AST_unary *Parser::parse_unary();

        //parsing expressions
        AST_actual_params *Parser::parse_actual_params();
        AST_term *Parser::parse_term();
        AST_simple_expression *Parser::parse_simple_expression();
        AST_expression *Parser::parse_expression();

        //parsing operators
        AST_additive_operator *Parser::parse_additive_operator();
        AST_multiplicative_operator *Parser::parse_multiplicative_operator();
        AST_unary_operator *Parser::parse_unary_operator();
        AST_relational_operator *Parser::parse_relational_operator();

        //parsing statements
        AST_variable_declaration *Parser::parse_variable_decl();
        AST_assignment *Parser::parse_assignment();
        AST_print *Parser::parse_print();
        AST_if *Parser::parse_if();
        AST_for *Parser::parse_for();
        AST_while *Parser::parse_while();
        AST_return *Parser::parse_return();
        AST_function_declaration *Parser::parse_function_decl();
        AST_block *Parser::parse_block();

        //parsing others
        AST_type *Parser::parse_type();
        AST_formal_param *Parser::parse_formal_param();
        AST_formal_params *Parser::parse_formal_params(vector<AST_formal_param*> *f_params);
};