#pragma once 

#include <vector>

#include "AST_expression.h"

using namespace std;

class AST_actual_params: public AST_node_expression{
    public:
        vector<AST_node_expression*> *actual_params;

        explicit AST_actual_params(vector<AST_node_expression*> *actual_params);
        ~AST_actual_params();

        void accept(Visitor *visitor) override;
};