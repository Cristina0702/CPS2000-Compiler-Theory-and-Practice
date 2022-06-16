#pragma once

#include "AST_variable_declaration.h"
#include "AST_assignment.h"
#include "AST_block.h"
#include "../AST_node_statement.h"
#include "../expressions/AST_expression.h"

class AST_for: public AST_node_statement{
    public:
        AST_variable_declaration *var;
        AST_node_expression *expr;
        AST_assignment *assignment;
        AST_block *block;

        AST_for(AST_variable_declaration *var, AST_node_expression *expr, AST_assignment *assignment, AST_block *block);
        ~AST_for();

        void accept(Visitor *visitor) override;
};