#include "AST_if.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_if::AST_if(AST_node_expression *expr, AST_block *if_block, AST_block *else_block){
    this->expr = expr;
    this->if_block = if_block;
    this->else_block = else_block;
}

AST_if::~AST_if() {
    delete expr;
    delete if_block;
    delete else_block;
}

void AST_if::accept(Visitor *visitor){
    visitor->visit(this);
}