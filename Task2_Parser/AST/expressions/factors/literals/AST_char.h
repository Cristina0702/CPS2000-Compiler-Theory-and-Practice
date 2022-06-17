#pragma once

#include <iostream>

#include "../AST_node_literal.h"

using namespace std;

class AST_char: public AST_node_literal{
    public:
        string val;

        explicit AST_char(string val);
        ~AST_char() = default;

        void accept(Visitor *visitor) override;
};