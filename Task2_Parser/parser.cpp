#include "parser.h"

using namespace std;

Parser:: Parser(){
   AST = new vector<AST_node*>();
}

Parser:: ~Parser(){
    AST->clear();
}

vector<AST_node*> *Parser::parse_AST(){
    next_tok = Lexer::see_next_token().t_id 
    while(next_tok != Token_ID::EOF_TOK){
        current_tok = Lexer::return_next_token();

        AST->push_back(parse_statement());

        next_tok = Lexer::see_next_token().t_id 
    }  
   return AST;
}

AST_node_statement *Parser::parse_statement(){
    if(current_tok.t_id == keyword_TOK){
        if(current_tok.lexeme == "let"){
            //parsing variable declaration statement
            return parse_variable_decl();
        }else if(current_tok.lexeme == "print"){
            //parsing print statement
            return parse_print();
        }else if(current_tok.lexeme == "return"){
            //parsing return statement
            return parse_return();
        }else if(current_tok.lexeme == "if"){
            //parsing if statement
            return parse_if();
        }else if(current_tok.lexeme == "for"){
            //parsing for statement
            return parse_for();
        }else if(current_tok.lexeme == "while"){
            //parsing while statement
            return parse_while();
        }else if(current_tok.lexeme == "fn"){
            //parsing function declaration statement
            return parse_function_decl();
        }
    }else if(current_tok.t_id == identifier_TOK){
        //parsing assignment statement
        return parse_assignment();
    }else if (current_tok.t_id == punctuation_TOK && current_tok.lexeme == "{"){
        //parsing block statement
        return parse_block();
    }else{
        //returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected statement!" <<endl;
        exit(1);
    }
}


//parsing literals
AST_node_literal *Parser::parse_literal(){
    if(current_tok.t_id == bool_literal_TOK){
        if(current_tok.lexeme == "true"){
            return new AST_bool(true);
        }else if(curren_tok.lexeme == "false"){
            return new AST_bool(false);
        }else{
            //returning error
            cout << "Error at line: " << Lexer::line_index << ". Expected boolean literal!" <<endl;
            exit(1);
        }
    }else if(current_tok.t_id == int_literal_TOK){
        return new AST_int(stoi(current_tok.lexeme));
    }else if(current_tok.t_id == float_literal_TOK){
        return new AST_float(stof(current_tok.lexeme));
    }else if(current_tok.t_id == char_literal_TOK){
        return new AST_char(current_tok.lexeme);
    }else{
        //returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected literal!" <<endl;
        exit(1);
    }
}

AST_identifier *Parser::parse_identifier(){
    if(current_tok.t_id == identifier_TOK){
        return new AST_identifier(current_tok.lexeme);
    }else{
        //returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected identifier!" <<endl;
        exit(1);
    }
}

AST_function_call *Parser::parse_function_call(){}

AST_sub_expression *Parser::parse_sub_expression(){}

AST_unary *Parser::parse_unary(){}


//parsing expressions
AST_actual_params *Parser::parse_actual_params(){}

AST_term *Parser::parse_term(){}

AST_simple_expression *Parser::parse_simple_expression(){}

AST_expression *Parser::parse_expression(){}


//parsing operators
AST_additive_operator *Parser::parse_additive_operator(){
    if (current_tok.t_id == additive_op_TOK){
        if (current_tok.lexeme == "+"){
            //returning add_op addition
            return new AST_additive_operator(Additive_Operators::Addition);
        }else if(current_tok.lexeme == "-"){
            //returning add_op subtration
            return new AST_additive_operator(Additive_Operators::Subtraction);
        }else if(current_tok.lexeme == "or"){
            //returning add_op or
            return new AST_additive_operator(Additive_Operators::OR);
        }else{
            //otherwise returning error
            cout << "Error at line: " << Lexer::line_index << ". Expected additive operator!" <<endl;
            exit(1);
        }
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected additive operator!" <<endl;
        exit(1);
    }
}

AST_multiplicative_operator *Parser::parse_multiplicative_operator(){
    if (current_tok.t_id == multiplicative_op_TOK){
        if (current_tok.lexeme == "*"){
            //returning mult_op multiplication
            return new AST_multiplicative_operator(Multiplicative_Operators::Multiplication);
        }else if(current_tok.lexeme == "/"){
            //returning mult_op division
            return new AST_multiplicative_operator(Multiplicative_Operators::Division);
        }else if(current_tok.lexeme == "and"){
            //returning mult_op and
            return new AST_multiplicative_operator(Multiplicative_Operators::AND);
        }else{
            //otherwise returning error
            cout << "Error at line: " << Lexer::line_index << ". Expected multiplicative operator!" <<endl;
            exit(1);
        }
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected multiplicative operator!" <<endl;
        exit(1);
    }
}

AST_relational_operator *Parser::parse_relational_operator(){
    if (current_tok.t_id == relational_op_TOK){
        if (current_tok.lexeme == "<"){
            //returning rel_op <
            return new AST_relational_operator(Relational_Operators::Less_than);
        }else if(current_tok.lexeme == ">"){
            //returning rel_op >
            return new AST_relational_operator(Relational_Operators::Greater_than);
        }else if(current_tok.lexeme == "=="){
            //returning rel_op ==
            return new AST_relational_operator(Relational_Operators::Equal_to);
        }else if(current_tok.lexeme == "!="){
            //returning rel_op !=
            return new AST_relational_operator(Relational_Operators::Not_equal_to);
        }else if(current_tok.lexeme == "<="){
            //returning rel_op <=
            return new AST_relational_operator(Relational_Operators::Less_than_equal_to);
        }else if(current_tok.lexeme == ">="){
            //returning rel_op >=
            return new AST_relational_operator(Relational_Operators::Greater_than_equal_to);
        }else{
            //otherwise returning error
            cout << "Error at line: " << Lexer::line_index << ". Expected relational operator!" <<endl;
            exit(1);
        }
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected relational operator!" <<endl;
        exit(1);
    }
}

AST_unary_operator *Parser::parse_unary_operator(){
    if (current_tok.t_id == additive_op_TOK && current_tok.lexeme == "-"){
        //returning unary_op subtraction 
        return new AST_unary_operator(Unary_Operators::Subtraction);
    }else if(current_tok.t_id == keyword_TOK && current_tok.lexeme == "not"){
        //returning unary_op not 
        return new AST_unary_operator(Unary_Operators::NOT);
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected unary operator!" <<endl;
        exit(1);
    }
}


//parsing statements
AST_variable_declaration *Parser::parse_variable_decl(){
    AST_identifier *identifier;
    AST_type *type;
    AST_node_expression *expr;

    current_tok = Lexer::return_next_token();
    identifier = parse_identifier();

    current_tok = Lexer::return_next_token();
}

AST_assignment *Parser::parse_assignment(){
    AST_identifier *identifier;
    AST_node_expression *expr;

    if(current_tok.t_id == identifier_TOK){
        //parsing identifier
        identifier = parse_identifier();
    
        //setting current_tok to be the next token
        current_tok = Lexer::return_next_token();

        //checking for =
        if(current_tok.t_id == equals_TOK){
            //setting current_tok to be the next token
            current_tok = Lexer::return_next_token();  
            expr = parse_expression();
            
            //setting current_tok to be the next token
            current_tok = Lexer::return_next_token();  
            
            //checking for ;
            if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ";"){
                //returning new assignment
                return new AST_assignment(identifier, expr);
            }else{
                //otherwise returning error
                cout << "Error at line: " << Lexer::line_index << ". Expected ';'!" <<endl;
                exit(1);
            }
        }else{
            //otherwise returning error
            cout << "Error at line: " << Lexer::line_index << ". Expected '='!" <<endl;
            exit(1);
        }    
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected identifier!" <<endl;
        exit(1);
    }

}

AST_print *Parser::parse_print(){
    AST_node_expression *expr;

    //getting the expression
    current_tok = Lexer::return_next_token();

    //parsing expression
    expr = parse_expression();

    //setting current_tok to be the next token
    current_tok = Lexer::return_next_token();

    //if ; is found
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ";"){
        //returning new print statement
        return new AST_print(expr);
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected ';'!" <<endl;
        exit(1);
    }
}

AST_if *Parser::parse_if(){
    AST_node_expression *expr;
    AST_block *if_block;
    AST_block *else_block;

    //setting current_tok to be the next token
    current_tok = Lexer::return_next_token();

    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == "("){
        //setting current_tok to be the next token
        current_tok = Lexer::return_next_token();
        //parsing expression
        expr = parse_expression();
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected '('!" <<endl;
        exit(1);
    }

    //setting current_tok to be the next token
    current_tok = Lexer::return_next_token();
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ")"){
        //setting current_tok to be the next token
        current_tok = Lexer::return_next_token();
        //parsing if block
        if_block = parse_block();
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected ')'!" <<endl;
        exit(1);
    }

    if(Lexer::see_next_token().lexeme == "else"){
        //consuming else token
        Lexer::return_next_token();

        //setting current_tok to be the next token
        current_tok = Lexer::return_next_token();

        //parsing else block
        else_block = parse_block();
    }else{
        //otherwise if there is no else block
        //create empty else block
        else_block = new AST_block(new vector<AST_node_statement*>);
    }

    //returning new if statement
    return new AST_if(expr, if_block, else_block);
}

AST_for *Parser::parse_for(){
    AST_variable_declaration *var_decl;
    AST_node_expression *expr;
    AST_assignment *assignment;
    AST_block *block;

    // //getting the expression
    // current_tok = Lexer::return_next_token();

    // //parsing expression
    // expr = parse_expression();

    //setting current_tok to be the next token
    current_tok = Lexer::return_next_token();

    //checking for (
    if(!(current_tok.t_id == punctuation_TOK && current_tok.lexeme == "(")){
        //if ( not found, returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected '('!" <<endl;
        exit(1);
    }

    //setting current_tok to be the next token
    current_tok = Lexer::return_next_token();

    //checking for variable declaration
    if(current_tok.t_id == keyword_TOK && current_tok.lexeme == "let"){
        //variable declaration found
        var_decl = parse_variable_decl();
    }else{
        //if variable declaration is not found
        //create empty var declaration
        var_decl = new vector<AST_variable_declaration*>;        
    }

    //setting current_tok to be the next token
    current_tok = Lexer::return_next_token();

    //checking for ;
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ";"){
        //setting current_tok to be the next token
        current_tok = Lexer::return_next_token();
        //parsing exoression
        expr = parse_expression();
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected ';'!" <<endl;
        exit(1);
    }

    //setting current_tok to be the next token
    current_tok = Lexer::return_next_token();   
    //checking for ;
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ";"){
        //setting current_tok to be the next token
        current_tok = Lexer::return_next_token();

        if(current_tok.t_id == identifier_TOK){
            //parsing assignment
            assignment = parse_assignment();
        }else if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ";"){
            assignment = new vector<AST_assignment*>;
        }else{
            //otherwise returning error
            cout << "Error at line: " << Lexer::line_index << ". Expected identifier or ')'!" <<endl;
            exit(1);
        }
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected ';'!" <<endl;
        exit(1);
    }

    //setting current_tok to be the next token
    current_tok = Lexer::return_next_token();   
    //parsing block
    block = parse_block();

    //returning for statement
    return new AST_for(var_decl, expr, assignment, block);
}

AST_while *Parser::parse_while(){
    AST_node_expression *expr;
    AST_block *block;

    //setting current_tok to be the next token
    current_tok = Lexer::return_next_token();

    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == "("){
        //setting current_tok to be the next token
        current_tok = Lexer::return_next_token();
        //parsing expression
        expr = parse_expression();
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected '('!" <<endl;
        exit(1);
    }

    //setting current_tok to be the next token
    current_tok = Lexer::return_next_token();
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ")"){
        //setting current_tok to be the next token
        current_tok = Lexer::return_next_token();
        //parsing block
        block = parse_block();
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected ')'!" <<endl;
        exit(1);
    }

    //returning new while statement
    return new AST_while(expr, block);
}

AST_return *Parser::parse_return(){
    AST_node_expression *expr;

    //getting the expression
    current_tok = Lexer::return_next_token();

    //parsing expression
    expr = parse_expression();

    //setting current_tok to be the next token
    current_tok = Lexer::return_next_token();

    //if ; is found
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ";"){
        //returning new return statement
        return new AST_return(expr);
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected ';'!" <<endl;
        exit(1);
    }
}

AST_function_declaration *Parser::parse_function_decl(){
    AST_identifier *identifier;
    AST_formal_params *f_params;
    AST_type *type;
    AST_block *block;

    //getting the identifier after fn
    current_tok = Lexer::return_next_token();
    //parsing the identifier
    identifier = parse_identifier();

    //setting current_tok to be the next token
    current_tok = Lexer::return_next_token();

    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == "("){
        vector<AST_formal_param*> *f_param = new vector<AST_formal_param*>;
        //setting current_tok to be the next token
        current_tok = Lexer::return_next_token();

        if(!(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ")")){
            //there are more formal parameters
            parse_formal_params(f_param);

            //setting current_tok to be the next token
            current_tok = Lexer::return_next_token();

            if(!(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ")")){
                //otherwise returning error
                cout << "Error at line: " << Lexer::line_index << ". Expected open bracket!" <<endl;
                exit(1);
            }
        }
        f_params = new AST_formal_params(f_param);

        //setting current_tok to be the next token
        current_tok = Lexer::return_next_token();

        //checking for -
        if(current_tok.t_id == additive_op_TOK && current_tok.lexeme == "-"){
            //setting current_tok to be the next token
            current_tok = Lexer::return_next_token();
            
            //checking for >
            if(current_tok.t_id == relational_op_TOK && current_tok.lexeme == ">"){
                //setting current_tok to be the next token
                current_tok = Lexer::return_next_token();
                //parsing type token
                type = parse_type();

                //setting current_tok to be the next token
                current_tok = Lexer::return_next_token();
                //parsing block token
                block = parse_block();
            }else{
                //otherwise returning error
                cout << "Error at line: " << Lexer::line_index << ". Expected '>'!" <<endl;
                exit(1);
            }
        }else{
            //otherwise returning error
            cout << "Error at line: " << Lexer::line_index << ". Expected '-'!" <<endl;
            exit(1);
        }
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected open bracket!" <<endl;
        exit(1);
    }

    //returning new function declaration
    return new AST_function_declaration(identifier, f_params, type, block);
}

AST_block *Parser::parse_block(){
    vector<AST_node_statement*> *block = new vector<AST_node_statement*>;
    
    int count = 0;

    //getting the next token after '{'
    current_tok = Lexer::return_next_token();
    
    //looping until close curly bracket is found
    while(Lexer::see_next_token().lexeme != "}"){
        if(count > 0){
            //getting the next statement block
            current_tok = Lexer::return_next_token();
        }

        //parsing the statement block
        block->push_back(parse_statement());
        count = count + 1;
    }

    //getting the next token to consume '}' since loop ends at curly bracket
    Lexer::return_next_token();

    //returning new block
    return new AST_block(block);
}


//parsing others
AST_type *Parser::parse_type(){
    //checking if the current token is a keyword
    if(current_tok.t_id == keyword_TOK){
        if(current_tok.lexeme == "float"){
            //returning type float
            return new AST_type(Type::Float);
        }else if(current_tok.lexeme == "int"){
            //returning type int
            return new AST_type(Type::Int);
        }else if(current_tok.lexeme == "bool"){
            //returning type bool
            return new AST_type(Type::Bool);
        }else if(current_tok.lexeme == "char"){
            //returning type char
            return new AST_type(Type::Char);
        }else{
            //otherwise returning error
            cout << "Error at line: " << Lexer::line_index << ". Expected type!" <<endl;
            exit(1);
        }
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected type!" <<endl;
        exit(1);
    }
}

AST_formal_param *Parser::parse_formal_param(){
    AST_identifier *identifier;
    AST_type *type;

    //if the current token is an identifier
    if(current_tok.t_id == identifier_TOK){
        //parsing the identifier
        identifier = parse_identifier();

        //setting current_tok to be the next token
        current_tok = Lexer::return_next_token();

        //if a semicolon is found
        if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ":"){
            //setting current_tok to be the next token
            current_tok = Lexer::return_next_token();
            //parsing the type
            type = parse_type();
        }else{
            //otherwise returning error
            cout << "Error at line: " << Lexer::line_index << ". Expected semicolon!" <<endl;
            exit(1);
        }

        return new AST_formal_param(identifier, type);
    }else{
        //otherwise returning error
        cout << "Error at line: " << Lexer::line_index << ". Expected identifier!" <<endl;
        exit(1);
    }
}

AST_formal_params *Parser::parse_formal_params(vector<AST_formal_param*> *f_params){
    f_params->push_back(parse_formal_param());

    //if a comma is found then there are more formal parameters
    if(Lexer::see_next_token().lexeme == ","){
        //consuming the comma
        Lexer::return_next_token();

        //checking that the next token is not a close bracket
        if(Lexer::see_next_token().lexeme != ")"){
            //setting the current token to be the next formal parameter
            current_tok = Lexer::return_next_token();
            //recalling the parse_formal_params function to parse the remaining formal parameters
            parse_formal_params(f_params);
        
        }else{
            //otherwise returning error
            cout << "Error at line: " << Lexer::line_index << ". Expected formal parameter!" <<endl;
            exit(1);
        }
    }
}
