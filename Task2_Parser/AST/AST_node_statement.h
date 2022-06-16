#pragma once

#include "AST_node.h"

//#include "../../Tasks3_4_5_Visitors/visitor.h"

class AST_node_statement: public AST_node{
    public:
        //abstract class destructor 
        virtual ~AST_node_statement() = default;
        void accept(Visitor *visitor) override = 0;
};