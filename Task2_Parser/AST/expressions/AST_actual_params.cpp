#include "AST_actual_params.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_actual_params::AST_actual_params(vector<AST_node_expression*> *actual_params){
    this->actual_params = actual_params;
}

AST_actual_params::~AST_actual_params(){
    actual_params->clear();
}

void AST_actual_params::accept(Visitor *visitor){
    visitor->visit(this);
}
