#include "AST_relational_operator.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_relational_operator::AST_relational_operator(Relational_Operators rel_op) {
    this->rel_op = rel_op;
}

AST_relational_operator::~AST_relational_operator() = default;

string AST_relational_operator::toString() {
    if (rel_op == Relational_Operators::Less_than) {
        return "<";
    } else if (rel_op == Relational_Operators::Greater_than) {
        return ">";
    } else if (rel_op == Relational_Operators::Equal_to) {
        return "==";
    } else if (rel_op == Relational_Operators::Not_equal_to) {
        return "!=";
    } else if (rel_op == Relational_Operators::Less_than_equal_to) {
        return "<=";
    } else if (rel_op == Relational_Operators::Greater_than_equal_to) {
        return ">=";
    }
}

void AST_relational_operator::accept(Visitor *visitor) {
    visitor->visit(this);
}