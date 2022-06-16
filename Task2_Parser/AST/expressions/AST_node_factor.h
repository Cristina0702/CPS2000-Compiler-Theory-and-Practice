#pragma once

#include "../AST_node_expression.h"

//#include "../../../Tasks3_4_5_Visitors/visitor.h"

class AST_node_factor: public AST_node_expression{
    public:
        //abstract class destructor 
        virtual ~AST_node_factor() = default; 
        void accept(Visitor *visitor) override = 0;
};