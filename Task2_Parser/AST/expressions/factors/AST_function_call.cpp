#include "AST_function_call.h"

#include "../../../../Tasks3_4_5_Visitors/visitor.h"

AST_function_call::AST_function_call(AST_identifier *identifier, AST_actual_params *actual_params){
    this->identifier = identifier;
    this->actual_params = actual_params;
}

AST_function_call::~AST_function_call(){
    delete identifier;
    delete actual_params;
}

void AST_function_call::accept(Visitor *visitor){
    visitor->visit(this);
}
