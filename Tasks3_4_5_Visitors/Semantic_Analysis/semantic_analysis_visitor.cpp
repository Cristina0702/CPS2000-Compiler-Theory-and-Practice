#include "semantic_analysis_visitor.h"

SA_Visitor::SA_Visitor(){
    symbol_table = new Symbol_Table();
    flag = false;
}

SA_Visitor::~SA_Visitor(){
    delete symbol_table;
}

//to visit every node in the AST
void SA_Visitor::visit_AST(vector<AST_node*> *AST){
    //looping through all the AST nodes
    for(auto const &child: *AST){
        child->accept(this);
    }

    cout << "No errors occured whilst performing Semantic Analysis" << endl;
}

//literals
void SA_Visitor::visit(AST_float *AST_node) {
    current_type = Float;
}

void SA_Visitor::visit(AST_int *AST_node) {
    current_type = Int;
}

void SA_Visitor::visit(AST_bool *AST_node) {
    current_type = Bool;
}

void SA_Visitor::visit(AST_char *AST_node) {
    current_type = Char;
}

//factors
void SA_Visitor::visit(AST_identifier *AST_node) {
    if(symbol_table->return_value(AST_node->identifier) != nullptr){
        current_type = symbol_table->return_value(AST_node->identifier)->id_type;
    }else{
        //returning error
        cout << "Identifier " << AST_node->identifier << " is not declared!" << endl;
        exit(1);
    }
}

void SA_Visitor::visit(AST_function_call *AST_node) {
    vector<Value*> *params_type = new vector<Value*>;

    for(AST_node_expression* expr: *AST_node->actual_params->actual_params){
        expr->accept(this);
        params_type->push_back(new Value(current_type));
    }

    if(symbol_table->check_function_call(AST_node->identifier->identifier, params_type)){
        current_type = symbol_table->return_value(AST_node->identifier->identifier)->id_type;
    }else{
        //returning error
        cout << "Error: Invalid function call!" << endl;
        exit(1);
    }
}

void SA_Visitor::visit(AST_sub_expression *AST_node) {
    AST_node->expr->accept(this);
}

void SA_Visitor::visit(AST_unary *AST_node) {
    AST_node->expr->accept(this);

    //checking if the operator is a 'not'
    if(AST_node->u_op->toString() == "not"){
        //checking if the variable type is bool as 'not' can be only applied to bool variables
        if(current_type != Bool){
            //returning error
            cout << "Error: 'not' can be applied only to bool variables!" << endl;
            exit(1);
        }
    }else if(AST_node->u_op->toString() == "-" && current_type == Bool){
        //if there is a '-' and variable type is bool
        //returning error as '-' can only be applied to float and int variables
        cout << "Error: '-' can be applied only to float and int variables!" << endl;
        exit(1);
    }
}

//expressions
void SA_Visitor::visit(AST_term *AST_node) {
    Val_Type t1;
    Val_Type t2;

    AST_node->factor1->accept(this);
    //getting factor 1 type
    t1 = current_type;

    AST_node->factor2->accept(this);
    //getting factor 2 type
    t2 = current_type;

    if(t1 == t2){
        //if both term types are the same
        string e_op;

        e_op = AST_node->multi_op->toString();

        if(e_op == "*"){
            //if operator is *
            if(t1 == Float){
                //setting current type to be float as float * float = float
                current_type = Float;
            }else if(t1 == Int){
                //setting current type to be int as int * int = int
                current_type = Int;
            }else{
                //returning error
                cout << "Error: Operator: " << e_op << " can be applied to float and int variables only!" << endl;
                exit(1);
            }
        }else if(e_op == "/"){
            //if operator is /
            if(t1 != Bool){
                //setting current type to be Float
                current_type = Float;
            }else{
                //returning error
                cout << "Error: Operator: " << e_op << " can be applied to float and int variables only!" << endl;
                exit(1);
            }
        }else if(e_op == "and"){
            //if the operator is 'and'
            if(t1 == Bool){
                //setting current type to be Bool
                current_type = Bool;
            }else{
                //returning error
                cout << "Error: Operator: " << e_op << " can be applied to bool variables only!" << endl;
                exit(1);
            }
        }
    }else{
        //returning error
        cout << "Error: Factors must have the same type!" << endl;
        exit(1);
    }
}

void SA_Visitor::visit(AST_simple_expression *AST_node) {
    Val_Type t1;
    Val_Type t2;

    AST_node->term1->accept(this);
    //getting term 1 type
    t1 = current_type;

    AST_node->term2->accept(this);
    //getting term 2 type
    t2 = current_type;

    if(t1 == t2){
        //if both term types are the same
        string e_op;

        e_op = AST_node->add_op->toString();

        if(e_op == "+" || e_op == "-"){
            if(t1 != Bool){
                //setting current type to be equal to t1's type
                current_type = t1;
            }else{
                //returning error
                cout << "Error: Operator: " << e_op << " can be applied to float and int variables only!" << endl;
                exit(1);
            }
        }else if(e_op == "or"){
            //if the operator is 'or'
            if(t1 == Bool){
                //setting current type to be Bool
                current_type = Bool;
            }else{
                //returning error
                cout << "Error: Operator: " << e_op << " can be applied to bool variables only!" << endl;
                exit(1);
            }
        }
    }else{
        //returning error
        cout << "Error: Terms must have the same type!" << endl;
        exit(1);
    }
}

void SA_Visitor::visit(AST_expression *AST_node) {
    Val_Type t1;
    Val_Type t2;

    AST_node->s_expression1->accept(this);
    //getting simple expression 1 type
    t1 = current_type;

    AST_node->s_expression2->accept(this);
    //getting simple expression 2 type
    t2 = current_type;

    if(t1 == t2){
        //if both simple expression types are the same
        string e_op;

        e_op = AST_node->rel_op->toString();

        if(t1 == Bool && (e_op == "<" || e_op == ">")){
            //returning error
            cout << "Error: Operator: " << e_op << " can be applied to float and int variables only!" << endl;
            exit(1);
        }else{
            //setting current type to be Bool
            current_type = Bool;
        }
    }else{
        //returning error
        cout << "Error: Simple expressions must have the same type!" << endl;
        exit(1);
    }
}

void SA_Visitor::visit(AST_actual_params *AST_node) {
    //handled in Function_call visit function
}

//statements
void SA_Visitor::visit(AST_variable_declaration *AST_node) {
    Val_Type var_type;

    //getting the variable type
    if(AST_node->type->toString() == "float"){
        var_type = Float;
    }else if(AST_node->type->toString() == "int"){
        var_type = Int;
    }else if(AST_node->type->toString() == "bool"){
        var_type = Bool;
    }else if(AST_node->type->toString() == "char"){
        var_type = Char;
    }

    AST_node->expr->accept(this);
    
    //checking if the identifier type is the same as the expression type
    if(var_type == current_type){
        //inserting the variable in the symbol table
        if(symbol_table->insert_variable(AST_node->identifier->identifier, new Value(current_type)) == -1){
            //returning error if variable is already in the symbol table
            cout << "Error: Variable: " << AST_node->identifier->identifier << " is already declared!" << endl;
            exit(1);
        }
    }else{
        //returning error
        cout << "Error: Declared identifier type is differrent than expression type!" << endl;
        exit(1);
    }
}

void SA_Visitor::visit(AST_assignment *AST_node) {
    Val_Type var_t;
    Val_Type val_t;

    AST_node->identifier->accept(this);
    var_t = current_type;

    AST_node->expression->accept(this);
    val_t = current_type;

    if(var_t != val_t){
        //returning error
        cout << "Error: Expression type does not match variable type!" << endl;
        exit(1);
    }
}

void SA_Visitor::visit(AST_print *AST_node) {
    AST_node->expr->accept(this);
}

void SA_Visitor::visit(AST_if *AST_node) {
    AST_node->expr->accept(this);
    if(current_type == Bool){
        AST_node->if_block->accept(this);
        AST_node->else_block->accept(this);
    }else{
        //returning error
        cout << "Error: If statement expression must be of type bool!" << endl;
        exit(1);
    }
}

void SA_Visitor::visit(AST_for *AST_node) {
    Val_Type expr_type;

    //checking if variable declaration identifier is empty
    if(AST_node->var->identifier->identifier != ""){
        AST_node->var->accept(this);
    }

    AST_node->expr->accept(this);

    //setting expression type to be current type
    expr_type = current_type;

    //checking that expression type is Bool
    if(expr_type != Bool){
        //returning error
        cout << "Error: If statement expression must be of type bool!" << endl;
        exit(1);
    }

    //checking if assignment identifier is empty
    if(AST_node->assignment->identifier->identifier != ""){
        AST_node->assignment->accept(this);
    }
}

void SA_Visitor::visit(AST_while *AST_node) {
    AST_node->expr->accept(this);

    //checking that the current variable is of type bool
    if(current_type == Bool){
        AST_node->block->accept(this);
    }else{
        //returning error
        cout << "Error: While statement expression must be bool!" << endl;
        exit(1);
    }
}

void SA_Visitor::visit(AST_return *AST_node) {
    AST_node->expr->accept(this);
}

void SA_Visitor::visit(AST_function_declaration *AST_node) {
    string func_name;
    string func_type;
    vector<Value*> *params_type = new vector<Value*>;

    func_name = AST_node->identifier->identifier;
    func_type = AST_node->type->toString();

    //getting function return type
    if(AST_node->type->toString() == "float"){
        return_type = Float;
    }else if(AST_node->type->toString() == "int"){
        return_type = Int;
    }else if(AST_node->type->toString() == "bool"){
        return_type = Bool;
    }else if(AST_node->type->toString() == "char"){
        return_type = Char;
    }

    for(int i=0; i < AST_node->f_params->f_params->size(); i++){
        params.insert(make_pair(AST_node->f_params->f_params->at(i)->identifier->identifier,
        new Value(AST_node->f_params->f_params->at(i)->type->toString())));
        params_type->push_back(new Value(AST_node->f_params->f_params->at(i)->type->toString()));
    }

    Value *method = new Value(func_type, params_type);
    symbol_table->insert_variable(func_name, method);
    AST_node->block->accept(this);

    if(flag == true){
        //setting the flag back to false
        flag = false;
    }else{
        //returning error
        cout << "Error: Return statement not found in function!" << endl;
        exit(1);
    }
}

void SA_Visitor::visit(AST_block *AST_node) {
    int to_check;

    //opening the scope
    symbol_table->open_scope();

    //if there are function declaration parameters
    if(!params.empty()){
        //getting the start of the parameters
        map<string, Value*>::iterator iter = params.begin();
        //looping until the end of the parameters is reached
        while(iter != params.end()){
            //inserting the variable; identifier and value
            to_check = symbol_table->insert_variable(iter->first, iter->second);
            //checking if variable was inserted correctly
            if(to_check == -1){
                //returning error
                cout << "Error: Failed to insert parameter into symbol table as identifier: " << iter->first << " is already declared!" << endl;
            } 
            //moving to the next parameter
            iter++;
        }
    }

    //clearing the function declaration parameters
    params.clear();

    //looping through the staements in the block
    for(AST_node_statement *statement: *AST_node->block){
        statement->accept(this);

        //checking the types
        if(typeid(AST_return) == typeid(*statement)){
            flag = true;
            //checking function return type with current type
            if(return_type != current_type){
                //returning error
                cout << "Error: Retrun type is not according to function return type!" << endl;
                exit(1);
            }
        }
    }
    //closing the cscope
    symbol_table->close_scope();
}


//operators
void SA_Visitor::visit(AST_multiplicative_operator *AST_node) {
    //handled in term visit function
}

void SA_Visitor::visit(AST_additive_operator *AST_node) {
    //handled in simple_expression visit function    
}

void SA_Visitor::visit(AST_relational_operator *AST_node) {
    //handled in expression visit function
}

void SA_Visitor::visit(AST_unary_operator *AST_node) {
    //handled in unary visit function
}

//others
void SA_Visitor::visit(AST_formal_param *AST_node) {
    //handled in function_declaration visit function
}

void SA_Visitor::visit(AST_formal_params *AST_node) {
    //handled in function_declaration visit function
}

void SA_Visitor::visit(AST_type *AST_node) {
    //empty
}