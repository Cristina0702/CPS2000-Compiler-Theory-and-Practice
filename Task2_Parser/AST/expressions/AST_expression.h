#pragma once

#include "AST_simple_expression.h"
//#include "../AST_node_expression.h"
#include "../operators/AST_relational_operator.h"

class AST_expression: public AST_node_expression{
    public:
        AST_node_expression *s_expression1;
        AST_node_expression *s_expression2;
        AST_relational_operator *rel_op;

        AST_expression(AST_node_expression *s_expr1, AST_relational_operator *rel_op, AST_node_expression *s_expr2);
        ~AST_expression();

        void accept(Visitor *visitor) override; 
};