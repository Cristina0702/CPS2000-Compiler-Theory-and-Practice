#pragma once

#include "AST_node_factor.h"
#include "../AST_node_expression.h"
#include "../operators/AST_multiplicative_operator.h"

class AST_term: public AST_node_expression{
    public:
        AST_node_expression *factor1;
        AST_node_expression *factor2;
        AST_multiplicative_operator *multi_op;

        AST_term(AST_node_expression *factor1, AST_multiplicative_operator *multi_op, AST_node_expression *factor2);
        ~AST_term();

        void accept(Visitor *visitor) override;
};