#include "AST_float.h"

#include "../../../../../Tasks3_4_5_Visitors/visitor.h"

AST_float::AST_float(float float_val){
    this->float_val = float_val;
}

void AST_float::accept(Visitor *visitor){
    visitor->visit(this);
}