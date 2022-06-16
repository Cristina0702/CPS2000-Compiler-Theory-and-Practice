#include "AST_sub_expression.h"

#include "../../../../Tasks3_4_5_Visitors/visitor.h"

AST_sub_expression::AST_sub_expression(AST_node_expression *expr){
    this->expr = expr;
}

AST_sub_expression::~AST_sub_expression(){
    delete expr;
}

void AST_sub_expression::accept(Visitor *visitor){
    visitor->visit(this);
}