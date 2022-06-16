#pragma once

#include <iostream>

#include "../AST_node_operator.h"

using namespace std;

enum class Unary_Operators{
    Subtraction,
    NOT
};

class AST_unary_operator: public AST_node_operator{
    public:
        Unary_Operators u_op;

        explicit AST_unary_operator(Unary_Operators u_oper);
        ~AST_unary_operator();

        string toString();
        void accept(Visitor *visitor) override;
};