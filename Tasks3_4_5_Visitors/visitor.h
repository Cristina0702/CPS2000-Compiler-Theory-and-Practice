#pragma once

#include "../Task2_Parser/AST/AST_node.h"
#include "../Task2_Parser/AST/AST_node_expression.h"
#include "../Task2_Parser/AST/AST_node_statement.h"
#include "../Task2_Parser/AST/AST_node_operator.h"

//literals
#include "../Task2_Parser/AST/expressions/factors/literals/AST_bool.h"
#include "../Task2_Parser/AST/expressions/factors/literals/AST_int.h"
#include "../Task2_Parser/AST/expressions/factors/literals/AST_float.h"
#include "../Task2_Parser/AST/expressions/factors/literals/AST_char.h"

//factors
//#include "../Task2_Parser/AST/expressions/factors/AST_identifier.h"
#include "../Task2_Parser/AST/expressions/factors/AST_function_call.h"
#include "../Task2_Parser/AST/expressions/factors/AST_sub_expression.h"
#include "../Task2_Parser/AST/expressions/factors/AST_unary.h"

//expressions
#include "../Task2_Parser/AST/expressions/AST_actual_params.h"
#include "../Task2_Parser/AST/expressions/AST_expression.h"
// #include "../Task2_Parser/AST/expressions/AST_simple_expression.h"
// #include "../Task2_Parser/AST/expressions/AST_term.h"

//statements
// #include "../Task2_Parser/AST/statements/AST_variable_declaration.h"
#include "../Task2_Parser/AST/statements/AST_assignment.h"
#include "../Task2_Parser/AST/statements/AST_print.h"
#include "../Task2_Parser/AST/statements/AST_if.h"
#include "../Task2_Parser/AST/statements/AST_for.h"
#include "../Task2_Parser/AST/statements/AST_while.h"
#include "../Task2_Parser/AST/statements/AST_return.h"
#include "../Task2_Parser/AST/statements/AST_function_declaration.h"
#include "../Task2_Parser/AST/statements/AST_block.h"

//operators
#include "../Task2_Parser/AST/operators/AST_multiplicative_operator.h"
#include "../Task2_Parser/AST/operators/AST_additive_operator.h"
#include "../Task2_Parser/AST/operators/AST_relational_operator.h"
#include "../Task2_Parser/AST/operators/AST_unary_operator.h"

//others
// #include "../Task2_Parser/AST/others/AST_type.h"
#include "../Task2_Parser/AST/others/AST_formal_param.h"
#include "../Task2_Parser/AST/others/AST_formal_params.h"

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