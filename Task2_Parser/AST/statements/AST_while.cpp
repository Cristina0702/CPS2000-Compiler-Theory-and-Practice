#include "AST_while.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_while::AST_while(AST_node_expression *expr, AST_block *block){
    this->expr = expr;
    this->block = block;
}

AST_while::~AST_while() {
    delete expr;
    delete block;
}

void AST_while::accept(Visitor *visitor){
    visitor->visit(this);
}