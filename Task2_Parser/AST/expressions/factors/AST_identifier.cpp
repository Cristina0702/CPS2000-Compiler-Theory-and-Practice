#include "AST_identifier.h"

#include "../../../../Tasks3_4_5_Visitors/visitor.h"

AST_identifier::AST_identifier(string identifier){
    this->identifier = identifier;
}

AST_identifier::~AST_identifier() = default;

void AST_identifier::accept(Visitor *visitor){
    visitor->visit(this);
}
