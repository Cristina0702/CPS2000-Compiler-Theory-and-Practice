#pragma once

#include "../AST_node_statement.h"
#include "../expressions/AST_expression.h"
#include "../expressions/factors/AST_identifier.h"

class AST_assignment: public AST_node_statement{
    public:
        AST_identifier *identifier;
        AST_node_expression *expression;

        AST_assignment(AST_identifier *identifier, AST_node_expression *expression);
        ~AST_assignment();

        void accept(Visitor *visitor) override; 
};