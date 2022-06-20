#pragma once

#include <set>

#include "tokens.h"

using namespace std;

#define NUM_STATES 23
#define ALPHABET_SIZE 17
#define Se -1


struct State{
    //to store the state id
    int state_id;
    //to store whether the state is a final state or not
    bool final_state;
    //to store the token type of the state
    Token_ID token_id;
};

int transition_table[NUM_STATES][ALPHABET_SIZE] = {
    //letter  digit  printable  \n  .  "  _  *  /  +  -  <  >  !  =  (|)|,|;|:|{|}  EOF     
    {7,1,Se,Se,Se, 4, 7, 8, 14, 9, 20, 10, 10, 12, 11, 21, 22},           //S0
    {Se, 1, Se, Se, 2, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se},   //S1
    {Se, 3, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se},  //S2
    {Se, 3, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se},  //S3
    {Se, Se, 5, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se},  //S4
    {Se, Se, Se, Se, Se, 6, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se},  //S5
    {Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se}, //S6
    {7, 7, Se, Se, Se, Se, 7, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se},    //S7
    {Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se},  //S8
    {Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se},  //S9
    {Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, 13, Se, Se},  //S10
    {Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, 13, Se, Se},  //S11
    {Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, 13, Se, Se},  //S12
    {Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se},  //S13
    {Se, Se, Se, Se, Se, Se, Se, 17, 15, Se, Se, Se, Se, Se, Se, Se, Se},  //S14
    {Se, Se, 15, 16, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se},  //S15
    {Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se},  //S16
    {Se, Se, 17, 17, Se, Se, Se, 18, Se, Se, Se, Se, Se, Se, Se, Se, Se},  //S17
    {Se, Se, Se, Se, Se, Se, Se, Se, 19, Se, Se, Se, Se, Se, Se, Se, Se},  //S18
    {Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se},  //S19
    {Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, 21, Se, Se, Se, Se},  //S20
    {Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se},  //S21
    {Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se, Se},  //S22
};

class States{
    public:
        //creating a states array with type struct State
        static State states[NUM_STATES];

        static void init_DFSA(){
            //hardcoding the final state's ids
            set<int> final_states = {1,3,6,7,8,9,10,11,13,14,16,19,20,21,22};

            //looping according to the number of states
            for (int i = 0; i < NUM_STATES; i++){
                //assigning the state id to the state
                states[i].state_id = i;
                //setting whether the state is a final state or not depending on if it's id is found int the final_states set.
                states[i].final_state = final_states.find(i) != final_states.end();
            }

            //hardcoding the token type of each state
            states[0].token_id = Token_ID::ERROR_TOK;
            states[1].token_id = Token_ID::int_literal_TOK;
            states[2].token_id = Token_ID::ERROR_TOK;
            states[3].token_id = Token_ID::float_literal_TOK;
            states[4].token_id = Token_ID::ERROR_TOK;
            states[5].token_id = Token_ID::ERROR_TOK;
            states[6].token_id = Token_ID::char_literal_TOK;
            states[7].token_id = Token_ID::identifier_TOK; //can also be a keyword, bool_literal, additive_op or multiplicative_op
            states[8].token_id = Token_ID::multiplicative_op_TOK;
            states[9].token_id = Token_ID::additive_op_TOK;
            states[10].token_id = Token_ID::relational_op_TOK;
            states[11].token_id = Token_ID::equals_TOK;
            states[12].token_id = Token_ID::ERROR_TOK;
            states[13].token_id = Token_ID::relational_op_TOK;
            states[14].token_id = Token_ID::multiplicative_op_TOK;
            states[15].token_id = Token_ID::ERROR_TOK;
            states[16].token_id = Token_ID::comment_TOK;
            states[17].token_id = Token_ID::ERROR_TOK;
            states[18].token_id = Token_ID::ERROR_TOK;
            states[19].token_id = Token_ID::comment_TOK;
            states[20].token_id = Token_ID::additive_op_TOK;
            states[21].token_id = Token_ID::punctuation_TOK;
            states[22].token_id = Token_ID::EOF_TOK;
        }
};