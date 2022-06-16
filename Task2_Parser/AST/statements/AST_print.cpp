#include "AST_print.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_print::AST_print(AST_node_expression *expr){
    this->expr = expr;
}

AST_print::~AST_print() {
    delete expr;
}

void AST_print::accept(Visitor *visitor){
    visitor->visit(this);
}