#include "value.h"

Value::Value(Val_Type id_type){
    this->id_type = id_type;
    float_val = nullptr;
    int_val = nullptr;
    bool_val = nullptr;
    char_val = nullptr;
    f_params = nullptr;
}

Value::~Value(){
    delete float_val;
    delete int_val;
    delete bool_val;
    delete char_val;
    f_params->clear();
}

Value::Value(float float_val){
    id_type = Float;
    this->float_val = new float(float_val);

    int_val = nullptr;
    bool_val = nullptr;
    char_val = nullptr;
    f_params = nullptr;
}

Value::Value(int int_val){
    id_type = Int;
    this->int_val = new int(int_val);

    float_val = nullptr;
    bool_val = nullptr;
    char_val = nullptr;
    f_params = nullptr;
}

Value::Value(bool bool_val){
    id_type = Bool;
    this->bool_val = new bool(bool_val);

    float_val = nullptr;
    int_val = nullptr;
    char_val = nullptr;
    f_params = nullptr;
}

Value::Value(string type){
    if(type == "float"){
        id_type = Float;
    }else if(type == "int"){
        id_type = Int;
    }else if(type == "bool"){
        id_type = Bool;
    }else{
        id_type = Char;
    }

    float_val = nullptr;
    int_val = nullptr;
    bool_val = nullptr;
    char_val = nullptr;
    f_params = nullptr;
}

Value::Value(string type, vector<Value*> *f_params){
    if(type == "float"){
        id_type = Float;
    }else if(type == "int"){
        id_type = Int;
    }else if(type == "bool"){
        id_type = Bool;
    }else{
        id_type = Char;
    }

    this->f_params = f_params;

    float_val = nullptr;
    int_val = nullptr;
    bool_val = nullptr;
    char_val = nullptr;
}