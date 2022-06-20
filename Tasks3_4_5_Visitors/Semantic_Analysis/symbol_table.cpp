#include "symbol_table.h"

Symbol_Table::Symbol_Table(){
    //creating the symbol table
    symbol_table = new vector<map<string, Value*>*>;
    //opening the scope
    open_scope();
}
Symbol_Table::~Symbol_Table(){
    //clearing the symbol table
    symbol_table->clear();
}

void Symbol_Table::open_scope(){
    //adds a new map element at the end of the symbol table vector
    symbol_table->push_back(new map<string, Value*>);
}

void Symbol_Table::close_scope(){
    //deleting the last element of the symbol table vector
    symbol_table->pop_back();
}

int Symbol_Table::search(string identifier){
    for(int i=0; i < symbol_table->size(); i++){
        if(symbol_table->at(i)->find(identifier) != symbol_table->at(i)->end()){
            //if the identifier is found, position will be returned
            return i;
        }
    }
    //-1 is returned if identifier is not in symbol tale
    return -1;
}

int Symbol_Table::insert_variable(string identifier, Value *val){
    if(search(identifier) == -1){
        //if identifier is not already in the symbol table
        //adding identifier and value in symbol table
        symbol_table->back()->insert(make_pair(identifier, val));
        //returning 2 to show that identifier and value were added
        return 2;
    }else{
        //if identifier is already in the symbol table
        //returning -1
        return -1;
    }
}

int Symbol_Table::assign_variable(string identifier, Value *val){
    Value *variable;
    //getting the value of the identifier
    variable = return_value(identifier);

    //if the variable is not null and has the same type as the value
    if(variable != nullptr && variable->id_type == val->id_type){
        //checking the variable type and setting it's value to the appropriate value based on the type
        if(variable->id_type == Float){
            variable->float_val = val->float_val;
        }else if(variable->id_type == Int){
            variable->int_val = val->int_val;
        }else if(variable->id_type == Bool){
            variable->bool_val = val->bool_val;
        }
        // else if(variable->id_type == Char){
        //     variable->char_val = val->char_val;
        // }
        return 2;

    }else{
        //otherwise return -1
        return -1;
    }

}

bool Symbol_Table::check_function_call(string identifier, vector<Value*> *params){
    Value *func; 
    //getting the value of the identifier
    func = return_value(identifier);

    if(func != nullptr){
        if(func->f_params == nullptr){
            //returning error
            cout << "Error: No function parameters found!" << endl;
            return false;
        }else if(func->f_params->size() != params->size()){
            //if sizes do not correspond to each other
            //returning error
            cout << "Error: Parameter mismatch!" << endl;
            return false;
        }

        //looping to check that parameters correspond to each other
        for(int i=0; i < params->size(); i++){
            if(params->at(i)->id_type != func->f_params->at(i)->id_type){
                //returning error
                cout << "Error: Parameter mismatch!" << endl;
                return false;
            }
        }

        //returning true if everything is correct
        return true;
    }else{
        //returning error
        cout << "Error: Function not declared!" << endl;
        return false;
    }
}

Value *Symbol_Table::return_value(string identifier){
    //getting the position of the identifier
    int pos = search(identifier);

    if(pos != -1){
        //if identifier was found, returning value
        return symbol_table->at(pos)->at(identifier);
    }else{
        //if identifier was not found
        return nullptr;
    }
}