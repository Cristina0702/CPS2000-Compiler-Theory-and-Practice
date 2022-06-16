#include "AST_int.h"

#include "../../../../../Tasks3_4_5_Visitors/visitor.h"

AST_int::AST_int(int int_val){
    this->int_val = int_val;
}

void AST_int::accept(Visitor *visitor){
    visitor->visit(this);
}