#pragma once

#include "../AST_node_statement.h"
#include "../expressions/AST_expression.h"
#include "../expressions/factors/AST_identifier.h"
#include "../others/AST_type.h"

class AST_variable_declaration: public AST_node_statement{
    public:
        AST_identifier *identifier;
        AST_type *type;
        AST_node_expression *expr;

        AST_variable_declaration(AST_identifier *identifier, AST_type *type, AST_node_expression *expr);
        ~AST_variable_declaration();

        void accept(Visitor *visitor) override;
};