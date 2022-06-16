#include "AST_char.h"

#include "../../../../../Tasks3_4_5_Visitors/visitor.h"

AST_char::AST_char(char char_val){
    this->char_val = char_val;
}

void AST_char::accept(Visitor *visitor){
    visitor->visit(this);
}