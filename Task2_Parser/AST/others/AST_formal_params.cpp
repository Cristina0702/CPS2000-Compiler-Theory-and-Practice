#include "AST_formal_params.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_formal_params::AST_formal_params(vector<AST_formal_param*> *f_params) {
    this->f_params = f_params;
}

AST_formal_params::~AST_formal_params() {
    f_params->clear();
}

void AST_formal_params::accept(Visitor *visitor) {
    visitor->visit(this);
}