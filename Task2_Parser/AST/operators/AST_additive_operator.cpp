#include "AST_additive_operator.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_additive_operator::AST_additive_operator(Additive_Operators add_op) {
    this->add_op = add_op;
}

AST_additive_operator::~AST_additive_operator() = default;

string AST_additive_operator::toString() {
    if (add_op == Additive_Operators::Addition){
        return "+";
    } else if(add_op == Additive_Operators::Subtraction) {
        return "-";
    } else if (add_op == Additive_Operators::OR) {
        return "or";
    }
}

void AST_multiplicative_operator::accept(Visitor *visitor) {
    visitor->visit(this);
}