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

        AST->push_back(parse_tok());

        next_tok = Lexer::see_next_token().t_id 
    }  
   return AST;
}

AST_node_statement *Parser::parse_tok(){
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

//parsing statements
AST_variable_declaration *Parser::parse_variable_decl(){
    AST_identifier *identifier;
    AST_type *type;
    AST_node_expression *expr;

    current_tok = Lexer::return_next_token();
    identifier = parse_identifier();

    current_tok = Lexer::return_next_token();
}

AST_assignment *Parser::parse_assignment(){}

AST_print *Parser::parse_print(){}

AST_if *Parser::parse_if(){}

AST_for *Parser::parse_for(){}

AST_while *Parser::parse_while(){}

AST_return *Parser::parse_return(){}

AST_function_declaration *Parser::parse_function_decl(){}

AST_block *Parser::parse_block(){}