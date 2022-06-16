#pragma once

#include "AST_identifier.h"
#include "../AST_node_factor.h"
#include "../AST_actual_params.h"

class AST_function_call: public AST_node_factor{
    public:
        AST_identifier *identifier;
        AST_actual_params *actual_params;

        AST_function_call(AST_identifier *identifier, AST_actual_params *actual_params);
        ~AST_function_call();

        void accept(Visitor *visitor) override; 
};