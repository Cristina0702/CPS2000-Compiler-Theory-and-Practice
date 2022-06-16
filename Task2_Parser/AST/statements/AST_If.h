#pragma once

#include "AST_block.h"
#include "../AST_node_statement.h"
#include "../expressions/AST_expression.h"

class AST_if: public AST_node_statement{
    public:
        AST_node_expression *expr;
        AST_block *if_block;
        AST_block *else_block;

        AST_if(AST_node_expression *expr, AST_block *if_block, AST_block *else_block);
        ~AST_if();

        void accept(Visitor *visitor) override;
};