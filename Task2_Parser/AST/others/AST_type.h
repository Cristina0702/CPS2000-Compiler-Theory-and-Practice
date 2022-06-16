#pragma once

#include <iostream>

#include "../AST_node_expression.h"

using namespace std;

enum class Type{
    Float,
    Int,
    Bool,
    Char
};

class AST_type: public AST_node{
    public:
        Type type;

        explicit AST_type(Type t);
        ~AST_type();

        string toString();
        void accept(Visitor *visitor) override;
};