#pragma once

#include <iostream>

#include "../AST_node_operator.h"

using namespace std;

enum class Multiplicative_Operators{
    Multiplication,
    Division,
    AND
};

class AST_multiplicative_operator: public AST_node_operator{
    public:
        Multiplicative_Operators mult_op;

        explicit AST_multiplicative_operator(Multiplicative_Operators mult_op);
        ~AST_multiplicative_operator();

        string toString();
        void accept(Visitor *visitor) override;
};