#pragma once

#include <iostream>

#include "../visitor.h"

using namespace std;

class XML_Visitor: public Visitor{
    private:
        string indentation;
    
    public:
        XML_Visitor();
        
        //literals
        void visit(AST_float *AST_node) override;
        void visit(AST_int *AST_node) override;
        void visit(AST_bool *AST_node) override;
        void visit(AST_char *AST_node) override;

        //factors
        void visit(AST_identifier *AST_node) override;
        void visit(AST_function_call *AST_node) override;
        void visit(AST_sub_expression *AST_node) override;
        void visit(AST_unary *AST_node) override;
        
        //expressions
        void visit(AST_term *AST_node) override;
        void visit(AST_simple_expression *AST_node) override;
        void visit(AST_expression *AST_node) override;
        void visit(AST_actual_params *AST_node) override;

        //statements
        void visit(AST_variable_declaration *AST_node) override;
        void visit(AST_assignment *AST_node) override;
        void visit(AST_print *AST_node) override;
        void visit(AST_if *AST_node) override;
        void visit(AST_for *AST_node) override;
        void visit(AST_while *AST_node) override;
        void visit(AST_return *AST_node) override;
        void visit(AST_function_declaration *AST_node) override;
        void visit(AST_block *AST_node) override;

        //operators
        void visit(AST_multiplicative_operator *AST_node) override;
        void visit(AST_additive_operator *AST_node) override;
        void visit(AST_relational_operator *AST_node) override;
        void visit(AST_unary_operator *AST_node) override;

        //others
        void visit(AST_formal_param *AST_node) override;
        void visit(AST_formal_params *AST_node) override;
        void visit(AST_type *AST_node) override;
};