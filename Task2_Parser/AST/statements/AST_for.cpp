#include "AST_for.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_for::AST_for(AST_variable_declaration *var, AST_node_expression *expr, AST_assignment *assignment, AST_block *block){
    this->var = var;
    this->expr = expr;
    this->assignment = assignment;
    this->block = block;
}

AST_for::~AST_for() {
    delete var;
    delete expr;
    delete assignment;
    delete block;
}

void AST_for::accept(Visitor *visitor){
    visitor->visit(this);
}