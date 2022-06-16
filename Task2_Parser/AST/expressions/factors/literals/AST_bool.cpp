#include "AST_bool.h"

#include "../../../../../Tasks3_4_5_Visitors/visitor.h"

AST_bool::AST_bool(bool bool_val){
    this->bool_val = bool_val;
}

void AST_bool::accept(Visitor *visitor){
    visitor->visit(this);
}