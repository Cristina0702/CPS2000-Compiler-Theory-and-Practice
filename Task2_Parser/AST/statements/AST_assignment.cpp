#include "AST_assignment.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_assignment::AST_assignment(AST_identifier *identifier,AST_node_expression *expression) {
    this->identifier = identifier;
    this->expression = expression;
}

AST_assignment::~AST_assignment() {
    delete identifier;
    delete expression;
}

void AST_assignment::accept(Visitor *visitor) {
    visitor->visit(this);
}