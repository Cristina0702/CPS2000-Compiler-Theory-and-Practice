#include "AST_term.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_term::AST_term(AST_node_expression *factor1, AST_multiplicative_operator *multi_op, AST_node_expression *factor2){
    this->factor1 = factor1;
    this->multi_op = multi_op;
    this->factor2 = factor2;
}

AST_term::~AST_term(){
    delete factor1;
    delete multi_op;
    delete factor2;
}

void AST_term::accept(Visitor *visitor){
    visitor->visit(this);
}