#pragma once

#include "../AST_node_factor.h"
#include "../AST_expression.h"
#include "../../operators/AST_unary_operator.h"

class AST_unary: public AST_node_factor{
    public:
        AST_unary_operator *u_op;
        AST_node_expression *expr;

        AST_unary(AST_unary_operator *u_op, AST_node_expression *expr);
        ~AST_unary();

        void accept(Visitor *visitor) override;
};