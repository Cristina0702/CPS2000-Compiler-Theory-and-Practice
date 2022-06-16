#pragma once

#include "../Task1_Table-driven_Lexer/lexer.h"

#include "AST/AST_node.h"

//literals
#include "AST/expressions/factors/literals/AST_bool.h"
#include "AST/expressions/factors/literals/AST_int.h"
#include "AST/expressions/factors/literals/AST_float.h"
#include "AST/expressions/factors/literals/AST_char.h"

//factors
#include "AST/expressions/factors/AST_identifier.h"
#include "AST/expressions/factors/AST_function_call.h"
#include "AST/expressions/factors/AST_sub_expression.h"
#include "AST/expressions/factors/AST_unary.h"

//expressions


//statements
#include "AST/statements/AST_assignment.h"
#include "AST/statements/AST_print.h"
#include "AST/statements/AST_if.h"
#include "AST/statements/AST_for.h"
#include "AST/statements/AST_while.h"
#include "AST/statements/AST_return.h"
#include "AST/statements/AST_function_declaration.h"
#include "AST/statements/AST_block.h"

//operators
#include "AST/operators/AST_multiplicative_operator.h"
#include "AST/operators/AST_additive_operator.h"
#include "AST/operators/AST_relational_operator.h"

//others
#include "AST/others/AST_formal_param.h"
#include "AST/others/AST_formal_params.h"

using namespace std;

class Parser{
    public:
        // explicit Parser(Lexer *lexer);

        vector<AST_node*> *create_AST();
    
    private:
        // Lexer *lexer;
        Token current_tok;
        Token next_tok;

        // void next_tok();

        // AST_node_statement *parse();
}