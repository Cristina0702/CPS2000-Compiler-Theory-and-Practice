#pragma once

#include "../AST_node_factor.h"

class AST_node_literal: public AST_node_factor{
    public:
        //abstract class destructor 
        virtual ~AST_node_literal() = default; 
        void accept(Visitor *visitor) override = 0;
};