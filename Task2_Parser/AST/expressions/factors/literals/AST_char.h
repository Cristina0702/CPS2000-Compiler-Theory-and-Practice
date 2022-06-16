#pragma once

#include "../AST_node_literal.h"

class AST_char: public AST_node_literal{
    public:
        char char_val;

        explicit AST_char(char char_val);
        ~AST_char() = default;

        void accept(Visitor *visitor) override;
};