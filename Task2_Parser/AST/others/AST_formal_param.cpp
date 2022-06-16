#include "AST_formal_param.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_formal_param::AST_formal_param(AST_identifier *identifier, AST_type *type) {
    this->identifier = identifier;
    this->type = type;
}

AST_formal_param::~AST_formal_param() {
    delete identifier;
    delete type;
}

void AST_formal_param::accept(Visitor *visitor) {
    visitor->visit(this);
}