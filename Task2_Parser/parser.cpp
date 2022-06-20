#include "parser.h"

using namespace std;

Parser:: Parser(){
    //creating the AST
    AST = new vector<AST_node*>();
}

Parser:: ~Parser(){
    //clearing the AST
    AST->clear();
}

vector<AST_node*> *Parser::parse_AST(){
    //looping until all the input program is parsed
    while(lexer.see_next_token().t_id != Token_ID::EOF_TOK){
        //setting current token to be the next token from Lexer class
        current_tok = lexer.return_next_token();

        //parsing the statement and adding it to the AST
        AST->push_back(parse_statement()); 
    }  

    //returning the developed AST
    return AST;
}

AST_node_statement *Parser::parse_statement(){
    //calling the respective parse functions
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
        cout << "Error at line: " << lexer.line_index << ". Expected statement!" <<endl;
        return nullptr;
    }
}

AST_node_factor *Parser::parse_factor(){
    if(current_tok.t_id == bool_literal_TOK || current_tok.t_id == int_literal_TOK 
    || current_tok.t_id == float_literal_TOK || current_tok.t_id == char_literal_TOK){
        //calling function to parse literal
        return parse_literal();
    }else if(current_tok.t_id == identifier_TOK){
        if(lexer.see_next_token().lexeme == "("){
            //calling function to parse function call
            return parse_function_call();
        }else{
            //calling function to parse identifier
            return parse_identifier();
        }
    }else if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == "("){
        //calling function to parse sub_expression
        return parse_sub_expression();
    }else if((current_tok.t_id == additive_op_TOK && current_tok.lexeme == "-") || (current_tok.t_id == keyword_TOK && current_tok.lexeme == "not")){
        //calling function to parse unary
        return parse_unary();
    }else{
         //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected factor!" <<endl;
        return nullptr;
    }
}

//parsing factors:

//parsing literals
AST_node_literal *Parser::parse_literal(){
    if(current_tok.t_id == bool_literal_TOK){
        if(current_tok.lexeme == "true"){
            //returning new bool with value true
            return new AST_bool(true);
        }else if(current_tok.lexeme == "false"){
            //returning new bool with value false
            return new AST_bool(false);
        }else{
            //returning error
            cout << "Error at line: " << lexer.line_index << ". Expected boolean literal!" <<endl;
            return nullptr;
        }
    }else if(current_tok.t_id == int_literal_TOK){
        //returning new int with int value
        return new AST_int(stoi(current_tok.lexeme));
    }else if(current_tok.t_id == float_literal_TOK){
        //returning new float with float value
        return new AST_float(stof(current_tok.lexeme));
    }else if(current_tok.t_id == char_literal_TOK){
        //returning new char with string value
        return new AST_char(current_tok.lexeme);
    }else{
        //returning error
        cout << "Error at line: " << lexer.line_index << ". Expected literal!" <<endl;
        return nullptr;
    }
}

AST_identifier *Parser::parse_identifier(){
    if(current_tok.t_id == identifier_TOK){
        //returning new identifier
        return new AST_identifier(current_tok.lexeme);
    }else{
        //returning error
        cout << "Error at line: " << lexer.line_index << ". Expected identifier!" <<endl;
        return nullptr;
    }
}

AST_function_call *Parser::parse_function_call(){
    AST_identifier *identifier;
    AST_actual_params *actual_params;

    //parsing identifier
    identifier = parse_identifier();

    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();

    //checking for (
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == "("){
        vector<AST_node_expression*> *actual_param = new vector<AST_node_expression*>;
        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();
        if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ")"){
            //creating new AST_actual_params object from actual_param and assigning it to actual_params
            actual_params = new AST_actual_params(new vector<AST_node_expression*>);

            //returning new function call
            return new AST_function_call(identifier, actual_params);
        }else{
            //there are remaining actual parameters to be parsed
            //parsing the actual param
            actual_params = parse_actual_params(actual_param);

            //setting current_tok to be the next token
            current_tok = lexer.return_next_token();

            if(!(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ")")){
                //otherwise returning error
                cout << "Error at line: " << lexer.line_index << ". Expected ')'!" <<endl;
                return nullptr;
            }

            //creating new AST_actual_params object from actual_param and assigning it to actual_params
            actual_params = new AST_actual_params(actual_param);

            //returning new function call
            return new AST_function_call(identifier, actual_params);
        }
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected '('!" <<endl;
        return nullptr;
    }
}

AST_sub_expression *Parser::parse_sub_expression(){
    AST_node_expression *expr;

    //setting current_tok to be the next token to skip ( and get expression
    current_tok = lexer.return_next_token();

    //parsing expression
    expr = parse_expression();

    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();

    //checking for )
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ")"){
        //returning new sub expression
        return new AST_sub_expression(expr);
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected ')'!" <<endl;
        return nullptr;
    }
}

AST_unary *Parser::parse_unary(){
    AST_unary_operator *u_op;
    AST_node_expression *expr;

    //parsing unary operator
    u_op = parse_unary_operator();
    
    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();

    //parsing expression
    expr = parse_expression();

    return new AST_unary(u_op, expr);
}


//parsing expressions:

AST_actual_params *Parser::parse_actual_params(vector<AST_node_expression*> *actual_params){
    AST_node_expression *expr;
    
    //parsing expression
    expr = parse_expression();
    
    if(expr != nullptr){
        //parsing the parameter and adding it to the vector
        actual_params->push_back(parse_expression());
    }else{
        //returning error
        cout << "Error at line: " << lexer.line_index << ". Expected actual parameter!" <<endl;
        return nullptr;
    }

    //checking if the next token is a comma
    if(lexer.see_next_token().lexeme == ","){
        //consuming the token since its a comma
        lexer.return_next_token();

        if(lexer.see_next_token().lexeme == ")"){
            //returning error
            cout << "Error at line: " << lexer.line_index << ". Expected ')'!" <<endl;
            return nullptr;
        }

        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();
        //recalling the function to parse the remaining actual parameters
        return parse_actual_params(actual_params);
    }else if(lexer.see_next_token().lexeme == ")"){
        //consuming the token since its a )
        lexer.return_next_token();

        //returning new actual params
        return new AST_actual_params(actual_params);
    }else{
        //returning error
        cout << "Error at line: " << lexer.line_index << ". Expected ',' or ')'!" <<endl;
        return nullptr;
    }
}

// AST_actual_params *Parser::parse_actual_params(){
//     vector<AST_node_expression*> *actual_params = new vector<AST_node_expression*>;
//     AST_node_expression *expr;
    
//     //parsing expression
//     expr = parse_expression();
    
//     if(expr != nullptr){
//         //parsing the parameter and adding it to the vector
//         actual_params->push_back(parse_expression());
//     }else{
//         //returning error
//         cout << "Error at line: " << lexer.line_index << ". Expected actual parameter!" <<endl;
//         return nullptr;
//     }

//     //checking if the next token is a comma
//     if(lexer.see_next_token().lexeme == ","){
//         //consuming the token since its a comma
//         lexer.return_next_token();

//         if(lexer.see_next_token().lexeme == ")"){
//             //returning error
//             cout << "Error at line: " << lexer.line_index << ". Expected ')'!" <<endl;
//             return nullptr;
//         }

//         //setting current_tok to be the next token
//         current_tok = lexer.return_next_token();
//         //recalling the function to parse the remaining actual parameters
//         return parse_actual_params(actual_params);
//     }else if(lexer.see_next_token().lexeme == ")"){
//         return new AST_actual_params(actual_params);
//     }else{
//         //returning error
//         cout << "Error at line: " << lexer.line_index << ". Expected ','!" <<endl;
//         return nullptr;
//     }
// }

AST_node_expression *Parser::parse_term(){
    AST_node_expression *factor;
    factor = parse_factor();

    if(lexer.see_next_token().t_id == multiplicative_op_TOK){
        AST_multiplicative_operator *mult_op;
        AST_node_expression *factor2;

        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();
        //parsing multiplicative operator
        mult_op = parse_multiplicative_operator();

        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();
        //recalling function to parse second factor
        factor2 = parse_term();
        
        //returning new term
        return new AST_term(factor, mult_op, factor2);
    }else{
        //consuming the token
        //lexer.return_next_token();
        //returning factor
        return factor;
    }
}

AST_node_expression *Parser::parse_simple_expression(){
    AST_node_expression *term;
    //parsing term
    term = parse_term();

    if(lexer.see_next_token().t_id == additive_op_TOK){
        AST_additive_operator *add_op;
        AST_node_expression *term2;

        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();
        //parsing additive operator
        add_op = parse_additive_operator();
        
        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();
        //recalling function to parse second term
        term2 = parse_simple_expression();
        
        //returning new simple expression
        return new AST_simple_expression(term, add_op, term2);
    }else{
        //if there is only 1 term
        return term;
    }
}

AST_node_expression *Parser::parse_expression(){
    AST_node_expression *s_expr;
    //parsing simple expression
    s_expr = parse_simple_expression();

    if(lexer.see_next_token().t_id == relational_op_TOK){
        AST_relational_operator *rel_op;
        AST_node_expression *s_expr2;

        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();
        //parsing relational operator
        rel_op = parse_relational_operator();
        
        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();
        //recalling function to parse second simple expression
        s_expr2 = parse_expression();
        
        //returning new expression
        return new AST_expression(s_expr, rel_op, s_expr2);
    }else{
        //if there is only 1 expression
        return s_expr;
    }
}


//parsing operators:

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
            cout << "Error at line: " << lexer.line_index << ". Expected additive operator!" <<endl;
            return nullptr;
        }
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected additive operator!" <<endl;
        return nullptr;
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
            cout << "Error at line: " << lexer.line_index << ". Expected multiplicative operator!" <<endl;
            return nullptr;
        }
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected multiplicative operator!" <<endl;
        return nullptr;
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
            cout << "Error at line: " << lexer.line_index << ". Expected relational operator!" <<endl;
            return nullptr;
        }
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected relational operator!" <<endl;
        return nullptr;
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
        cout << "Error at line: " << lexer.line_index << ". Expected unary operator!" <<endl;
        return nullptr;
    }
}


//parsing statements:

AST_variable_declaration *Parser::parse_variable_decl(){
    AST_identifier *identifier;
    AST_type *type;
    AST_node_expression *expr;
    
    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();
    //parsing the identifier
    identifier = parse_identifier();

    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();

    //checking for :
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ":"){
        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();

        //parsing type
        type = parse_type();

        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();

        //checking for =
        if(current_tok.t_id == equals_TOK){
            //setting current_tok to be the next token
            current_tok = lexer.return_next_token();

            //parsing expression
            expr = parse_expression();

            //setting current_tok to be the next token
            current_tok = lexer.return_next_token();

            //checking for ;
            if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ";"){
                //returning new variable declaration
                return new AST_variable_declaration(identifier, type, expr);
            }else{
                //otherwise returning error
                cout << "Error at line: " << lexer.line_index << ". Expected ';'!" <<endl;
                return nullptr;
            }
        }else{
            //otherwise returning error
            cout << "Error at line: " << lexer.line_index << ". Expected '='!" <<endl;
            return nullptr;
        }
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected ':'!" <<endl;
        return nullptr;
    }
}

AST_assignment *Parser::parse_assignment(){
    AST_identifier *identifier;
    AST_node_expression *expr;

    if(current_tok.t_id == identifier_TOK){
        //parsing identifier
        identifier = parse_identifier();
    
        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();

        //checking for =
        if(current_tok.t_id == equals_TOK){
            //setting current_tok to be the next token
            current_tok = lexer.return_next_token();  
            //parsing expression
            expr = parse_expression();
            
            //setting current_tok to be the next token
            current_tok = lexer.return_next_token();  
            
            //checking for ;
            if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ";"){
                //returning new assignment
                return new AST_assignment(identifier, expr);
            }else{
                //otherwise returning error
                cout << "Error at line: " << lexer.line_index << ". Expected ';'!" <<endl;
                return nullptr;
            }
        }else{
            //otherwise returning error
            cout << "Error at line: " << lexer.line_index << ". Expected '='!" <<endl;
            return nullptr;
        }    
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected identifier!" <<endl;
        return nullptr;
    }

}

AST_print *Parser::parse_print(){
    AST_node_expression *expr;

    //getting the expression
    current_tok = lexer.return_next_token();

    //parsing expression
    expr = parse_expression();

    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();

    //if ; is found
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ";"){
        //returning new print statement
        return new AST_print(expr);
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected ';'!" <<endl;
        return nullptr;
    }
}

AST_if *Parser::parse_if(){
    AST_node_expression *expr;
    AST_block *if_block;
    AST_block *else_block;

    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();

    //checking for (
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == "("){
        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();
        //parsing expression
        expr = parse_expression();
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected '('!" <<endl;
        return nullptr;
    }

    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ")"){
        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();
        //parsing if block
        if_block = parse_block();
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected ')'!" <<endl;
        return nullptr;
    }

    if(lexer.see_next_token().lexeme == "else"){
        //consuming else token
        lexer.return_next_token();

        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();

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

    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();

    //checking for (
    if(!(current_tok.t_id == punctuation_TOK && current_tok.lexeme == "(")){
        //if ( not found, returning error
        cout << "Error at line: " << lexer.line_index << ". Expected '('!" <<endl;
        return nullptr;
    }

    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();

    //checking for variable declaration
    if(current_tok.t_id == keyword_TOK && current_tok.lexeme == "let"){
        //variable declaration found
        var_decl = parse_variable_decl();  
    }else if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ";"){
        //checking for ;

        //if variable declaration is not found
        //create empty var declaration
        var_decl = new AST_variable_declaration(new AST_identifier(""), new AST_type(Type::None), new AST_int(-1));

        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();

        //parsing exoression
        expr = parse_expression();
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected ';'!" <<endl;
        return nullptr;
    }

    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();   
    //checking for ;
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ";"){
        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();

        if(current_tok.t_id == identifier_TOK){
            //parsing assignment
            assignment = parse_assignment();
        }else if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ")"){
            assignment = new AST_assignment(new AST_identifier(""), new AST_int(-1));
        }else{
            //otherwise returning error
            cout << "Error at line: " << lexer.line_index << ". Expected identifier or ')'!" <<endl;
            return nullptr;
        }
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected ';'!" <<endl;
        return nullptr;
    }

    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();   
    //parsing block
    block = parse_block();

    //returning for statement
    return new AST_for(var_decl, expr, assignment, block);
}

AST_while *Parser::parse_while(){
    AST_node_expression *expr;
    AST_block *block;

    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();

    //checking for (
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == "("){
        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();
        //parsing expression
        expr = parse_expression();
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected '('!" <<endl;
        return nullptr;
    }

    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ")"){
        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();
        //parsing block
        block = parse_block();
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected ')'!" <<endl;
        return nullptr;
    }

    //returning new while statement
    return new AST_while(expr, block);
}

AST_return *Parser::parse_return(){
    AST_node_expression *expr;

    //getting the expression
    current_tok = lexer.return_next_token();

    //parsing expression
    expr = parse_expression();

    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();

    //if ; is found
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ";"){
        //returning new return statement
        return new AST_return(expr);
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected ';'!" <<endl;
        return nullptr;
    }
}

AST_function_declaration *Parser::parse_function_decl(){
    AST_identifier *identifier;
    AST_formal_params *f_params;
    AST_type *type;
    AST_block *block;

    //getting the identifier after fn
    current_tok = lexer.return_next_token();
    //parsing the identifier
    identifier = parse_identifier();

    //setting current_tok to be the next token
    current_tok = lexer.return_next_token();

    //checking for (
    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == "("){
        vector<AST_formal_param*> *f_param = new vector<AST_formal_param*>;
        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();

        //checking for )
        if(!(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ")")){
            //there are more formal parameters
            parse_formal_params(f_param);

            //setting current_tok to be the next token
            current_tok = lexer.return_next_token();

            if(!(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ")")){
                //otherwise returning error
                cout << "Error at line: " << lexer.line_index << ". Expected ')'!" <<endl;
                return nullptr;
            }
        }
        //creating new AST_formal_params object
        f_params = new AST_formal_params(f_param);

        //setting current_tok to be the next token
        current_tok = lexer.return_next_token();

        //checking for -
        if(current_tok.t_id == additive_op_TOK && current_tok.lexeme == "-"){
            //setting current_tok to be the next token
            current_tok = lexer.return_next_token();
            
            //checking for >
            if(current_tok.t_id == relational_op_TOK && current_tok.lexeme == ">"){
                //setting current_tok to be the next token
                current_tok = lexer.return_next_token();
                //parsing type token
                type = parse_type();

                //setting current_tok to be the next token
                current_tok = lexer.return_next_token();
                //parsing block token
                block = parse_block();
            }else{
                //otherwise returning error
                cout << "Error at line: " << lexer.line_index << ". Expected '>'!" <<endl;
                return nullptr;
            }
        }else{
            //otherwise returning error
            cout << "Error at line: " << lexer.line_index << ". Expected '-'!" <<endl;
            return nullptr;
        }
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected open bracket!" <<endl;
        return nullptr;
    }

    //returning new function declaration
    return new AST_function_declaration(identifier, f_params, type, block);
}

AST_block *Parser::parse_block(){
    vector<AST_node_statement*> *block = new vector<AST_node_statement*>;
    
    //int count = 0;

    if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == "{"){
        //getting the next token after '{'
        current_tok = lexer.return_next_token();
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected '{'!" <<endl;
        return nullptr;
    }

    //looping until close curly bracket is found
    while(current_tok.lexeme != "}"){
        //parsing the statement block
        block->push_back(parse_statement());
        
        //getting the next statement block
        current_tok = lexer.return_next_token();
    }

    //returning new block
    return new AST_block(block);
}


//parsing others:

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
            cout << "Error at line: " << lexer.line_index << ". Expected type!" <<endl;
            return nullptr;
        }
    }else if(current_tok.lexeme == ""){
        //returning type none
        return new AST_type(Type::None);
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected type!" <<endl;
        return nullptr;
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
        current_tok = lexer.return_next_token();

        //if a semicolon is found
        if(current_tok.t_id == punctuation_TOK && current_tok.lexeme == ":"){
            //setting current_tok to be the next token
            current_tok = lexer.return_next_token();
            //parsing the type
            type = parse_type();
        }else{
            //otherwise returning error
            cout << "Error at line: " << lexer.line_index << ". Expected semicolon!" <<endl;
            return nullptr;
        }

        //returning new formal param
        return new AST_formal_param(identifier, type);
    }else{
        //otherwise returning error
        cout << "Error at line: " << lexer.line_index << ". Expected identifier!" <<endl;
        return nullptr;
    }
}

AST_formal_params *Parser::parse_formal_params(vector<AST_formal_param*> *f_params){
    f_params->push_back(parse_formal_param());

    //if a comma is found then there are more formal parameters
    if(lexer.see_next_token().lexeme == ","){
        //consuming the comma
        lexer.return_next_token();

        //checking that the next token is not a close bracket
        if(lexer.see_next_token().lexeme != ")"){
            //setting the current token to be the next formal parameter
            current_tok = lexer.return_next_token();
            //recalling the parse_formal_params function to parse the remaining formal parameters
            parse_formal_params(f_params);
        
        }else{
            //otherwise returning error
            cout << "Error at line: " << lexer.line_index << ". Expected formal parameter!" <<endl;
            return nullptr;
        }
    }
}