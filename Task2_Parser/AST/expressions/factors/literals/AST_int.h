#pragma once

#include "../AST_node_literal.h"

class AST_int: public AST_node_literal{
    public:
        int int_val;

        explicit AST_int(int int_val);
        ~AST_int() = default;

        void accept(Visitor *visitor) override;
};