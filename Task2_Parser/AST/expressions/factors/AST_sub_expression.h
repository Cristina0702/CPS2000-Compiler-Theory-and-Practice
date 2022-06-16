#pragma once

#include "../AST_node_factor.h"
#include "../AST_expression.h"

class AST_sub_expression: public AST_node_factor{
    public:
        AST_node_expression *expr;

        explicit AST_sub_expression(AST_node_expression *expr);
        ~AST_sub_expression();

        void accept(Visitor *visitor) override;
};