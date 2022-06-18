#pragma once

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
//#include "AST/expressions/factors/AST_identifier.h"
#include "AST/expressions/factors/AST_function_call.h"
#include "AST/expressions/factors/AST_sub_expression.h"
#include "AST/expressions/factors/AST_unary.h"

//expressions
#include "AST/expressions/AST_actual_params.h"
// #include "AST/expressions/AST_expression.h"
// #include "AST/expressions/AST_simple_expression.h"
// #include "AST/expressions/AST_term.h"

// //statements
// #include "AST/statements/AST_variable_declaration.h"
#include "AST/statements/AST_assignment.h"
#include "AST/statements/AST_print.h"
#include "AST/statements/AST_if.h"
#include "AST/statements/AST_for.h"
#include "AST/statements/AST_while.h"
#include "AST/statements/AST_return.h"
#include "AST/statements/AST_function_declaration.h"
#include "AST/statements/AST_block.h"

// //operators
#include "AST/operators/AST_multiplicative_operator.h"
#include "AST/operators/AST_additive_operator.h"
#include "AST/operators/AST_relational_operator.h"
#include "AST/operators/AST_unary_operator.h"

// //others
// #include "AST/others/AST_type.h"
#include "AST/others/AST_formal_param.h"
#include "AST/others/AST_formal_params.h"

class Visitor{
    public:
        //literals
        virtual void visit(AST_float *AST_node) = 0;
        virtual void visit(AST_int *AST_node) = 0;
        virtual void visit(AST_bool *AST_node) = 0;
        virtual void visit(AST_char *AST_node) = 0;

        //factors
        virtual void visit(AST_identifier *AST_node) = 0;
        virtual void visit(AST_function_call *AST_node) = 0;
        virtual void visit(AST_sub_expression *AST_node) = 0;
        virtual void visit(AST_unary *AST_node) = 0;
        
        //expressions
        virtual void visit(AST_term *AST_node) = 0;
        virtual void visit(AST_simple_expression *AST_node) = 0;
        virtual void visit(AST_expression *AST_node) = 0;
        virtual void visit(AST_actual_params *AST_node) = 0;

        //statements
        virtual void visit(AST_variable_declaration *AST_node) = 0;
        virtual void visit(AST_assignment *AST_node) = 0;
        virtual void visit(AST_print *AST_node) = 0;
        virtual void visit(AST_if *AST_node) = 0;
        virtual void visit(AST_for *AST_node) = 0;
        virtual void visit(AST_while *AST_node) = 0;
        virtual void visit(AST_return *AST_node) = 0;
        virtual void visit(AST_function_declaration *AST_node) = 0;
        virtual void visit(AST_block *AST_node) = 0;

        //operators
        virtual void visit(AST_multiplicative_operator *AST_node) = 0;
        virtual void visit(AST_additive_operator *AST_node) = 0;
        virtual void visit(AST_relational_operator *AST_node) = 0;
        virtual void visit(AST_unary_operator *AST_node) = 0;

        //others
        virtual void visit(AST_formal_param *AST_node) = 0;
        virtual void visit(AST_formal_params *AST_node) = 0;
        virtual void visit(AST_type *AST_node) = 0;
};