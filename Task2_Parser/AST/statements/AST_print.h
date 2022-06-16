#pragma once

#include "../AST_node_statement.h"
#include "../expressions/AST_expression.h"

class AST_print: public AST_node_statement{
    public:
        AST_node_expression *expr;

        AST_print(AST_node_expression *expr);
        ~AST_print();

        void accept(Visitor *visitor) override;
};