#pragma once
#include <iostream>
#include <set>
#include <vector>

//for lexer.cpp
#include <fstream>
#include <sstream>
#include <stack>

#include "tokens.h"

using namespace std;

//setting the keywords from the EBNF
static set<string> keywords = {"float", "int", "bool", "char", "true", "false", "and", "or", "not",
                                "let", "print", "return", "if", "else", "for", "while", "fn"};

class Lexer{
    private:
        //vector to hold the program's file input
        static vector<char> Lexer::program; 
        //function to get the position of the character from the transitive table
        static int get_char_pos(char c_char);
        //function to get the next state from the transititve table given the current state and character
        static int get_next_state(int current_state, char c_char);
        //function to check if the given lexeme is a keyword
        static bool check_if_keyword(string lexeme);
        //function to continue reading from the input file and return the next token
        Token Lexer::get_next_token();
        

    public:
        //to keep track of the character and line indexes of the file
        int char_index;
        int line_index;

        //function to read the program input and set it into a vector of chars
        void Lexer::read_program(string filename);
        //function which returns the next token from the program without changing the positions of the index
        Token Lexer::see_next_token();
        //function which calls get_next_token to get the next token which is not a comment
        Token Lexer::return_next_token();
        //function to clear the char vector
        void Lexer::clear_program();
        //function which calls the clear_program function and then loops through and stores the command line code input
        void Lexer::set_cmd_code(string p_input);
};