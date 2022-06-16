#include "AST_unary.h"

#include "../../../../Tasks3_4_5_Visitors/visitor.h"

AST_unary::AST_unary(AST_unary_operator *u_op, AST_node_expression *expr){
    this->u_op = u_op;
    this->expr = expr;
}

AST_unary::~AST_unary(){
    delete u_op;
    delete expr;
}

void AST_unary::accept(Visitor *visitor){
    visitor->visit(this);
}