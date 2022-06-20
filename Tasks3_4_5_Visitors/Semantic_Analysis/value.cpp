#include "value.h"

Value::Value(Val_Type id_type){
    //setting the type based on the given type
    this->id_type = id_type;
    
    //initialising all the values to nullptr
    float_val = nullptr;
    int_val = nullptr;
    bool_val = nullptr;
    char_val = nullptr;
    f_params = nullptr;
}

Value::~Value(){
    //deleting all the values
    delete float_val;
    delete int_val;
    delete bool_val;
    delete char_val;
    f_params->clear();
}

Value::Value(float float_val){
    //setting the type
    id_type = Float;
    //storing the new value of the appropriate type
    this->float_val = new float(float_val);

    //setting the unused values to nullptr
    int_val = nullptr;
    bool_val = nullptr;
    char_val = nullptr;
    f_params = nullptr;
}

Value::Value(int int_val){
    //setting the type
    id_type = Int;
    //storing the new value of the appropriate type
    this->int_val = new int(int_val);

    //setting the unused values to nullptr
    float_val = nullptr;
    bool_val = nullptr;
    char_val = nullptr;
    f_params = nullptr;
}

Value::Value(bool bool_val){
    //setting the type
    id_type = Bool;
    //storing the new value of the appropriate type
    this->bool_val = new bool(bool_val);

    //setting the unused values to nullptr
    float_val = nullptr;
    int_val = nullptr;
    char_val = nullptr;
    f_params = nullptr;
}

Value::Value(string type){
    //getting the type
    if(type == "float"){
        id_type = Float;
    }else if(type == "int"){
        id_type = Int;
    }else if(type == "bool"){
        id_type = Bool;
    }else{
        id_type = Char;
    }

    //setting the unused values to nullptr
    float_val = nullptr;
    int_val = nullptr;
    bool_val = nullptr;
    char_val = nullptr;
    f_params = nullptr;
}

Value::Value(string type, vector<Value*> *f_params){
    //getting the type
    if(type == "float"){
        id_type = Float;
    }else if(type == "int"){
        id_type = Int;
    }else if(type == "bool"){
        id_type = Bool;
    }else{
        id_type = Char;
    }

    //storing the given parameters
    this->f_params = f_params;

    //setting the unused values to nullptr
    float_val = nullptr;
    int_val = nullptr;
    bool_val = nullptr;
    char_val = nullptr;
}