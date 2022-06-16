#pragma once
#include <iostream>

#include "../AST_node_factor.h"

using namespace std;

class AST_identifier: public AST_node_factor{
    public:
        string identifier;

        explicit AST_identifier(string identifier);
        ~AST_identifier();

        void accept(Visitor *visitor) override;
};