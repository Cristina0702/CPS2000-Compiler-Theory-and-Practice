#pragma once
#include <iostream>
#include <set>
#include <vector>

//for lexer.cpp
#include <fstream>
#include <sstream>
#include <stack>

#include "states.h"

using namespace std;

//setting the keywords from the EBNF
static set<string> keywords = {"float", "int", "bool", "char", "true", "false", "and", "or", "not",
                                "let", "print", "return", "if", "else", "for", "while", "fn"};

class Lexer{
    private:
        //vector to hold the program's file input
        static vector<char> program; 
        //function to get the position of the character from the transition table
        static int get_char_pos(char c_char);
        //function to get the next state from the transition table given the current state and character
        static int get_next_state(int current_state, char c_char);
        //function to check if the given lexeme is a keyword
        static bool check_if_keyword(string lexeme);
        //function to continue reading from the input file and return the next token
        static Token get_next_token();
        

    public:
        //to keep track of the character and line indexes of the file
        static int char_index;
        static int line_index;

        //Lexer();

        //function to read the program input and set it into a vector of chars
        static void read_program(string filename);
        //function which returns the next token from the program without changing the positions of the index
        static Token see_next_token();
        //function which calls get_next_token to get the next token which is not a comment
        static Token return_next_token();
        //function to clear the char vector
        static void clear_program();
        //function which calls the clear_program function and then loops through and stores the command line code input
        static void set_cmd_code(string p_input);
};