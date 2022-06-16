#pragma once

#include <iostream>

#include "../AST_node_operator.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

using namespace std;

enum class Additive_Operators{
    Addition,
    Subtraction,
    OR
};

class AST_additive_operator: public AST_node_operator{
    public:
        Additive_Operators add_op;

        explicit AST_additive_operator(Additive_Operators add_op);
        ~AST_additive_operator();

        string toString();
        void accept(Visitor *visitor) override;
};