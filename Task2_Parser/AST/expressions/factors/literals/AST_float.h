#pragma once

#include "../AST_node_literal.h"

class AST_float: public AST_node_literal{
    public:
        float float_val;

        explicit AST_float(float float_val);
        ~AST_float() = default;

        void accept(Visitor *visitor) override;
};