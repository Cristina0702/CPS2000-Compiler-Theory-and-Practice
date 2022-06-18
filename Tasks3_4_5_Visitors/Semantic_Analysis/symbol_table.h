#pragma once

#include "value.h"

#include <map>

class Symbol_Table{
    private:
        vector<map<string, Value*>*> *symbol_table;

    public:
        Symbol_Table();
        ~Symbol_Table();

        void open_scope();
        void close_scope();

        int search(string identifier);
        int insert_variable(string identifier, Value *val);
        int assign_variable(string identifier, Value *val);
        
        bool check_function_call(string identifier, vector<Value*> *params);

        Value *return_value(string identifier);
};