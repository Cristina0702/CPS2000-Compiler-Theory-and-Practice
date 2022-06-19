#include "AST_unary_operator.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_unary_operator::AST_unary_operator(Unary_Operators u_oper) {
    this->u_op = u_oper;
}

AST_unary_operator::~AST_unary_operator() = default;

string AST_unary_operator::toString() {
    if (u_op == Unary_Operators::Subtraction) {
        return "-";
    } else if (u_op == Unary_Operators::NOT) {
        return "not";
    }
}

void AST_unary_operator::accept(Visitor *visitor) {
    visitor->visit(this);
}