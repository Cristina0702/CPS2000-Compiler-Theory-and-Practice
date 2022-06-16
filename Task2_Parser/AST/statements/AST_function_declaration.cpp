#include "AST_function_declaration.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_function_declaration::AST_function_declaration(AST_identifier *identifier, AST_formal_params *f_params, AST_type *type, AST_block *block){
    this->identifier = identifier;
    this->f_params = f_params;
    this->type = type;
    this->block = block;
}

AST_function_declaration::~AST_function_declaration(){
    delete identifier;
    delete f_params;
    delete type;
    delete block;
}

void AST_function_declaration::accept(Visitor *visitor){
    visitor->visit(this);
}