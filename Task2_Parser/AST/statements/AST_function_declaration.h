#pragma once

#include "AST_block.h"
#include "../AST_node_statement.h"
#include "../expressions/factors/AST_identifier.h"
#include "../others/AST_formal_params.h"

class AST_function_declaration: public AST_node_statement{
    public:
        AST_identifier *identifier;
        AST_formal_params *f_params;
        AST_type *type;
        AST_block *block;

        AST_function_declaration(AST_identifier *identifier, AST_formal_params *f_params, AST_type *type, AST_block *block);
        ~AST_function_declaration();

        void accept(Visitor *visitor) override;
};