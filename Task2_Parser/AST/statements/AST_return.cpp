#include "AST_return.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_return::AST_return(AST_node_expression *expr){
    this->expr = expr;
}

AST_return::~AST_return() {
    delete expr;
}

void AST_return::accept(Visitor *visitor){
    visitor->visit(this);
}