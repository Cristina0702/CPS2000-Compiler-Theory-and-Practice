#pragma once

#include <iostream>
#include <vector>

using namespace std;

enum Val_Type{
    Float = 0,
    Int = 1,
    Bool = 2,
    Char = 3,
    Func = 4
};

class Value{
    public: 
        Val_Type id_type;

        float *float_val;
        int *int_val;
        bool *bool_val;
        char *char_val;

        vector<Value*> *f_params;

        Value(Val_Type id_type);
        ~Value();

        Value(float float_val);
        Value(int int_val);
        Value(bool bool_val);

        Value(string type);
        Value(string type, vector<Value*> *f_params);
};        