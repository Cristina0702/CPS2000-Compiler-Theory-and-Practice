#include "AST_variable_declaration.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_variable_declaration::AST_variable_declaration(AST_identifier *identifier, AST_type *type, AST_node_expression *expr){
    this->identifier = identifier;
    this->type = type;
    this->expr = expr;
}

AST_variable_declaration::~AST_variable_declaration() {
    delete identifier;
    delete type;
    delete expr;
}

void AST_variable_declaration::accept(Visitor *visitor){
    visitor->visit(this);
}