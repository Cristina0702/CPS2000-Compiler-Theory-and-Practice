#pragma once

#include "AST_node.h"

class AST_node_operator: public AST_node{
    public:
        //abstract class destructor 
        virtual ~AST_node_operator() = default;
        void accept(Visitor *visitor) override = 0;
};