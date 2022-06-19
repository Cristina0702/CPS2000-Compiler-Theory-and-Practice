#pragma once

#include <iostream>
#include <typeinfo>

#include "../visitor.h"
#include "symbol_table.h"

class SA_Visitor: public Visitor{
    private:
        Symbol_Table *symbol_table;

        //flag to make sure that every function has a retun statement
        bool flag;

        //to store the type of current variable
        Val_Type current_type;
        //to store the return type of the current function
        Val_Type return_type;

        //map used to store function declaration parameters 
        map<string, Value*> params;

    public:
        //constructor
        SA_Visitor();

        ~SA_Visitor();

        //to visit every node in the AST
        void visit_AST(vector<AST_node*> *AST);
        
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