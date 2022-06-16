#pragma once

#include "AST_block.h"
#include "../AST_node_statement.h"
#include "../expressions/AST_expression.h"

class AST_while: public AST_node_statement{
    public:
        AST_node_expression *expr;
        AST_block *block;

        AST_while(AST_node_expression *expr, AST_block *block);
        ~AST_while();

        void accept(Visitor *visitor) override;
};