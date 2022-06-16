#pragma once

#include <iostream>

struct Token{
    token_id t_id;
    std::string lexeme;
};
 
enum token_id{        
    int_literal_TOK,         
    float_literal_TOK,
    char_literal_TOK,  
    identifier_TOK,
    bool_literal_TOK,
    equals_TOK,
    relational_op_TOK,  
    additive_op_TOK,
    multiplicative_op_TOK,        
    comment_TOK,     
    keyword_TOK,       
    punctuation_TOK,        
    ERROR_TOK,           
    EOF_TOK,            
};