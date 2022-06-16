#pragma once

#include <iostream>

#include "../AST_node_operator.h"

using namespace std;

enum class Relational_Operators{
    Less_than,
    Greater_than,
    Equal_to,
    Not_equal_to,
    Less_than_equal_to,
    Greater_than_equal_to
};

class AST_relational_operator: public AST_node_operator{
    public:
        Relational_Operators rel_op;

        explicit AST_relational_operator(Relational_Operators rel_op);
        ~AST_relational_operator();

        string toString();
        void accept(Visitor *visitor) override;
};