#include "AST_simple_expression.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_simple_expression::AST_simple_expression(AST_node_expression *term1, AST_additive_operator *add_op, AST_node_expression *term2){
    this->term1 = term1;
    this->add_op = add_op;
    this->term2 = term2;
}

AST_simple_expression::~AST_simple_expression(){
    delete term1;
    delete add_op;
    delete term2;
}

void AST_simple_expression::accept(Visitor *visitor){
    visitor->visit(this);
}