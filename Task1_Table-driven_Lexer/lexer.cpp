#include "lexer.h"

vector<char> Lexer::program;
State States::states[NUM_STATES];

int Lexer::char_index;
int Lexer::line_index;

void Lexer::read_program(string filename){
    ifstream fp;
    char curent_char;

    fp.open(filename);

    //if the file cannot be open
    if (!fp.good()) {
        //printing error
        cout << "File: " << filename << " could not be opened!";
        exit(1);
    }

    //getting file characters until EOF is reached
    while (fp.get(curent_char)) {
        //adding the characters to the vector
        Lexer::program.push_back(curent_char); 
    }
    //when EOF is reached, closing the file
    fp.close();

    cout << "File: " << filename << " was opened successfully!" <<endl;

    //adding an EOF character at the end of the vector
    Lexer::program.push_back(EOF);
}

//returning the given character position
int Lexer::get_char_pos(char c_char){
    if (isalpha(c_char)){
        // if a letter is found
        return 0;
    } else if (isdigit(c_char)){
        //if a digit is found
        return 1;
    } else if (c_char == '\t' || (c_char > 32 && c_char < 126)){
        //if a printable character is found
        return 2;
    } else if (c_char == '\n'){
        return 3;
    } else if (c_char == '.'){
        return 4;
    } else if (c_char == '"'){
        return 5;
    } else if (c_char == '_'){
        return 6;
    }  else if (c_char == '*'){
        return 7;
    } else if (c_char == '/'){
        return 8;
    } else if (c_char == '+'){
        return 9;
    } else if (c_char == '-'){
        return 10;
    } else if (c_char == '<'){
        return 11;
    } else if (c_char == '>'){
        return 12;
    } else if (c_char == '!'){
        return 13;
    } else if (c_char == '='){
        return 14;
    } else if (c_char == '(' || c_char == ')' || c_char == ',' || c_char == ';' || c_char == ':' || c_char == '{' || c_char == '}'){
        //if a punctuation character is found
        return 15;
    } else if(c_char == EOF){
        //if an end of file character is found
        return 16;
    }else{
        return -1;
    }
}

//getting the next state from the current state with the given character
int Lexer::get_next_state(int c_state, char c_char){
    //getting the position of the character
    int char_pos = get_char_pos(c_char);
    //returning the state reached after passing a character to the current state
    return transition_table[c_state][char_pos];
}

//checking if the given lexeme is a keyword
bool Lexer::check_if_keyword(string lex){
    return (keywords.find(lex) != keywords.end());
}

Token Lexer::see_next_token(){
    //getting the file char and line indexes 
    int t_char_index = Lexer::char_index;
    int t_line_index = Lexer::line_index;

    //calling the return_next_token() function to get the next token
    Token next_tok = return_next_token(); 
    
    //resetting the char and line index
    Lexer::char_index = t_char_index;
    Lexer::line_index = t_line_index;
    
    return next_tok;
}

Token Lexer::return_next_token(){ 
    //getting the next token
    Token tok = get_next_token();

    //if the token is a comment, then it will not be returned and the next token is found
    while(tok.t_id == comment_TOK){
        //getting the next token if the current token is a comment
        tok = get_next_token();
    }
    //returning the token
    return tok;
}

Token Lexer::get_next_token(){
    //setting current state to be the first state
    int current_state = 0;
    char current_char;
    string lexeme;
    Token tok;
    
    //creating stack for visisted states 
    stack<int> visited_states;
    //pushing the initial state S0 to the stack
    visited_states.push(0);
    
    //loop until the entire input program has been read
    do{
        //getting the character from the vector of chars 
        current_char = Lexer::program.at(char_index);
        //incrementing the index of the read characters
        Lexer::char_index++;

        //if a newline character is found, the line counter is incremented unless it is part of the char literal or comment
        if(current_char == '\n' && (current_state != 4 && current_state != 15 && current_state != 17)){
            Lexer::line_index++;
            continue;
        }
        
        //incrementing line counter if newline character is found in comment
        if(current_char == '\n' && (current_state == 15 || current_state == 17)){
            Lexer::line_index++;
        }
        
        //ignoring the character if it is not a char literal and it is a tab or whitespace
        if(current_state != 4 && (current_char == ' ' || current_char == '\t')){
            continue;
        }

        //calling the get_next_state function to find the next state will be after using the current character on the current state
        current_state = Lexer::get_next_state(current_state, current_char);
        //adding the current character to the lexeme
        lexeme = lexeme + current_char;

        //if DFSA moved to state 7, the check_if_keyword function will be called
        //to check if the lexeme is a keyword
        if (current_state == 7 && check_if_keyword(lexeme)){
            tok.lexeme = lexeme;
            
            if (lexeme == "true" || lexeme == "false"){
                //checking if the keyword is a boolean literal token and if so setting the token to the approriate token
                tok.t_id = Token_ID::bool_literal_TOK;
            }else if (lexeme == "and"){
                //checking if the keyword is a multiplicative op token and if so setting the token to the approriate token
                tok.t_id = Token_ID::multiplicative_op_TOK;
            } else if (lexeme == "or"){
                //checking if the keyword is a additive op token and if so setting the token to the approriate token
                tok.t_id = Token_ID::additive_op_TOK;
            }else{
                //otherwise setting the token to be a keyword token
                tok.t_id = Token_ID::keyword_TOK;
            }

            //returning the token
            return tok;
        }

        //if a final state was reached, then there is no need to keep track of the previous states
        if (States::states[current_state].final_state){
            //popping all the states from the stack until it is empty
            while(!visited_states.empty()){
                visited_states.pop();
            }
        } 

        //adding the current state on the stack
        visited_states.push(current_state);

    } while (current_state != -1 && Lexer::char_index < program.size());
    
    //looping while the current state isn't final and the stack isn't empty
    while (!States::states[current_state].final_state && !visited_states.empty()){
        //removing the last character froom the lexeme
        lexeme.pop_back();
        //decreasing the file character index by 1
        Lexer::char_index--;

        //removing the non-final state from the top of the stack
        visited_states.pop();
        //setting the current state to be the next state from the top of the stack 
        current_state = visited_states.top();
    }
    
    //if the current state is a final state
    if (States::states[current_state].final_state){
        //taking the token id of the current state
        tok.t_id == States::states[current_state].token_id;
        //setting the token lexeme
        tok.lexeme = lexeme;
        //returning the token
        return tok;
    } else {
        //if the current state is not a final state, an error will be returned with the file line index
        cout << "Lexical error at line: " << Lexer::line_index << endl;
        exit(-1);
    }
}

void Lexer::clear_program(){
    //clearing the char vector
    Lexer::program.clear();
}

void Lexer::set_cmd_code(string p_input) {
    //calling the clear_program to clear the char vector
    clear_program();

    //looping through the given program input to keep track of the command line code
    for (auto const &p_char : p_input) {
        //pushing each character
        program.push_back(p_char);
    }
    //pushing an EOF
    program.push_back(EOF);
}

int main(){
    Lexer lexer;

    string file = "testLexer.txt";

    lexer.read_program(file);

    States::init_DFSA();
}