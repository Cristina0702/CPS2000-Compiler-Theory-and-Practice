#pragma once

#include <vector>

#include "AST_formal_param.h"

using namespace std;

class AST_formal_params: public AST_node{
    public:
        vector<AST_formal_param*> *f_params;

        explicit AST_formal_params(vector<AST_formal_param*> *f_params);
        ~AST_formal_params();

        void accept(Visitor *visitor) override;
};