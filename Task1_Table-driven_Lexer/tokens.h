#pragma once

#include <iostream>

using namespace std;

struct Token{
    //to store the token type
    Token_ID t_id;
    //to store the token's contents
    string lexeme;
};
 
enum Token_ID{      
    //the token types
    bool_literal_TOK = 0, //S7
    int_literal_TOK = 1, //S1
    float_literal_TOK = 2, //S3
    char_literal_TOK = 3, //S6
    identifier_TOK = 4, //S7
    multiplicative_op_TOK = 5, //S7, S8, S14
    additive_op_TOK = 6, //S7, S9, S20
    relational_op_TOK = 7, //S10, S13
    equals_TOK = 8, //S11
    comment_TOK = 9, //S16, S19 
    punctuation_TOK = 10, //S21
    keyword_TOK = 11, //S7
    EOF_TOK = 12, //S22
    ERROR_TOK = 13,
};