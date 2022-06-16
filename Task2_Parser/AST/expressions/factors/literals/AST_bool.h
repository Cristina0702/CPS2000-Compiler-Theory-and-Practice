#pragma once

#include "../AST_node_literal.h"

class AST_bool: public AST_node_literal{
    public:
        bool bool_val;

        explicit AST_bool(bool bool_val);
        ~AST_bool() = default;

        void accept(Visitor *visitor) override;
};