#include "AST_expression.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_expression::AST_expression(AST_node_expression *s_expr1, AST_relational_operator *rel_op, AST_node_expression *s_expr2) {
    this->s_expression1 = s_expr1;
    this->rel_op = rel_op;
    this->s_expression2 = s_expr2;
}

AST_expression::~AST_expression() {
    delete s_expression1;
    delete rel_op;
    delete s_expression2;
}

void AST_expression::accept(Visitor *visitor) {
    visitor->visit(this);
}