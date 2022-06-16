#pragma once

#include <vector>

#include "../AST_node_statement.h"

using namespace std;

class AST_block: public AST_node_statement{
    public:
        vector<AST_node_statement*> *block;

        explicit AST_block(vector<AST_node_statement*> *block);
        ~AST_block();

        void accept(Visitor *visitor) override;
};