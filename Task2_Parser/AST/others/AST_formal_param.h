#pragma once

#include "AST_type.h"
#include "../expressions/factors/AST_identifier.h"

class AST_formal_param: public AST_node{
    public:
        AST_identifier *identifier;
        AST_type *type;

        AST_formal_param(AST_identifier *identifier, AST_type *type);
        ~AST_formal_param();

        void accept(Visitor *visitor) override;
};