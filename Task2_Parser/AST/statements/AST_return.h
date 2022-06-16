#pragma once

#include "../AST_node_statement.h"
#include "../expressions/AST_expression.h"

class AST_return: public AST_node_statement{
    public:
        AST_node_expression *expr;

        AST_return(AST_node_expression *expr);
        ~AST_return();

        void accept(Visitor *visitor) override;
};