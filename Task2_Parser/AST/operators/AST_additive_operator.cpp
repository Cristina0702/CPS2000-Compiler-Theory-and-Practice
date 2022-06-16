#include "AST_additive_operator.h"

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
        return "OR";
    }
}

void AST_additive_operator::accept(Visitor *visitor) {
    visitor->visit(this);
}