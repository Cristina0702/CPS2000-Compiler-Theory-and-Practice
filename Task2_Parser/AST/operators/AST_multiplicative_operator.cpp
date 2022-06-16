#include "AST_multiplicative_operator.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_multiplicative_operator::AST_multiplicative_operator(Multiplicative_Operators mult_op) {
    this->mult_op = mult_op;
}

AST_multiplicative_operator::~AST_multiplicative_operator() = default;

string AST_multiplicative_operator::toString() {
    if (mult_op == Multiplicative_Operators::Multiplication){
        return "*";
    } else if(mult_op == Multiplicative_Operators::Division) {
        return "/";
    } else if (mult_op == Multiplicative_Operators::AND) {
        return "AND";
    }
}

void AST_multiplicative_operator::accept(Visitor *visitor) {
    visitor->visit(this);
}