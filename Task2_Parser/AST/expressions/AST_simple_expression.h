#pragma once

#include "AST_term.h"
//#include "../AST_node_expression.h"
#include "../operators/AST_additive_operator.h"

class AST_simple_expression: public AST_node_expression{
    public: 
        AST_node_expression *term1;
        AST_node_expression *term2;
        AST_additive_operator *add_op;

        AST_simple_expression(AST_node_expression *term1, AST_additive_operator *add_op, AST_node_expression *term2);
        ~AST_simple_expression();

        void accept(Visitor *visitor) override;
};