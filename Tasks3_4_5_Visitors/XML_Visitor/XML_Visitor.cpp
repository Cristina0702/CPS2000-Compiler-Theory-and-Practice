#include "XML_Visitor.h"

XML_Visitor::XML_Visitor(){
    indentation = "";
}

void XML_Visitor::visit_AST(vector<AST_node*> *AST){
    cout << "<Abstract_Syntax_Tree>" <<endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    for (auto const &child: *AST){
        child->accept(this);
    }
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << "</Abstract_Syntax_Tree>" << endl;
}
        
//literals
void XML_Visitor::visit(AST_float *AST_node) {
    cout << indentation << "<Float>" << AST_node->float_val << "</Float>" << endl;
}
void XML_Visitor::visit(AST_int *AST_node) {
    cout << indentation << "<Int>" << AST_node->int_val << "</Int>" << endl;
}

void XML_Visitor::visit(AST_bool *AST_node) {
    //boolalpha is used to display 'true' or 'false'
    cout << indentation << "<Bool>" << boolalpha << AST_node->bool_val << "</Bool>" << endl;
}

void XML_Visitor::visit(AST_char *AST_node) {
    cout << indentation << "<Char>" << AST_node->val << "</Char>" << endl;
}

//factors
void XML_Visitor::visit(AST_identifier *AST_node) {
    cout << indentation << "<Identifier>" << AST_node->identifier << "</Identifier>" << endl;
}

void XML_Visitor::visit(AST_function_call *AST_node) {
    cout << indentation << "<Function_Call>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    AST_node->identifier->accept(this);
    AST_node->actual_params->accept(this);
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Function_Call>" << endl;
}

void XML_Visitor::visit(AST_sub_expression *AST_node) {
    cout << indentation << "<Sub_Expression>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    AST_node->expr->accept(this);
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Sub_Expression>" << endl;
}

void XML_Visitor::visit(AST_unary *AST_node) {
    cout << indentation << "<Unary>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    AST_node->u_op->accept(this);
    AST_node->expr->accept(this);
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Unary>" << endl;
}

//expressions
void XML_Visitor::visit(AST_term *AST_node) {
    cout << indentation << "<Term>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    AST_node->factor1->accept(this);
    AST_node->multi_op->accept(this);
    AST_node->factor2->accept(this);
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Term>" << endl;
}

void XML_Visitor::visit(AST_simple_expression *AST_node) {
    cout << indentation << "<Simple_Expression>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    AST_node->term1->accept(this);
    AST_node->add_op->accept(this);
    AST_node->term2->accept(this);
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Simple_Expression>" << endl;
}

void XML_Visitor::visit(AST_expression *AST_node) {
    cout << indentation << "<Expression>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    AST_node->s_expression1->accept(this);
    AST_node->rel_op->accept(this);
    AST_node->s_expression2->accept(this);
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Expression>" << endl;
}

void XML_Visitor::visit(AST_actual_params *AST_node) {
    cout << indentation << "<Actual_Params>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    //looping to call the accept function for all the nodes in the value of this node
    for(AST_node_expression *p: *AST_node->actual_params){
        p->accept(this);
    }
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Actual_Params>" << endl;
}

//statements
void XML_Visitor::visit(AST_variable_declaration *AST_node) {
    cout << indentation << "<Variable_Decl>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    AST_node->identifier->accept(this);
    AST_node->type->accept(this);
    AST_node->expr->accept(this);
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Variable_Decl>" << endl;
}

void XML_Visitor::visit(AST_assignment *AST_node) {
    cout << indentation << "<Assignment>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    AST_node->identifier->accept(this);
    AST_node->expression->accept(this);
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Assignment>" << endl;
}

void XML_Visitor::visit(AST_print *AST_node) {
    cout << indentation << "<Print_Statement>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    AST_node->expr->accept(this);
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Print_Statement>" << endl;
}

void XML_Visitor::visit(AST_if *AST_node) {
    cout << indentation << "<If_Statement>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    AST_node->expr->accept(this);
    AST_node->if_block->accept(this);
    //checking if the optional variable is empty
    //if the optional variable is empty, it's accept function will not be called
    if(!AST_node->else_block->block->empty()){
        AST_node->else_block->accept(this);
    }
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</If_Statement>" << endl;
}

void XML_Visitor::visit(AST_for *AST_node) {
    cout << indentation << "<For_Statement>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    //checking if the optional variable is empty
    //if the optional variable is empty, it's accept function will not be called
    if(AST_node->var->type->toString() != ""){
        AST_node->var->accept(this);
    }
    //checking if the optional variable is empty
    //if the optional variable is empty, it's accept function will not be called
    if(AST_node->assignment->identifier->identifier != ""){
        AST_node->assignment->accept(this);
    }
    AST_node->block->accept(this);
    AST_node->expr->accept(this);
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</For_Statement>" << endl;    
}

void XML_Visitor::visit(AST_while *AST_node) {
    cout << indentation << "<While_Statement>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    AST_node->expr->accept(this);
    AST_node->block->accept(this);
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</While_Statement>" << endl;
}

void XML_Visitor::visit(AST_return *AST_node) {
    cout << indentation << "<Return_Statement>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    AST_node->expr->accept(this);
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Return_Statement>" << endl;
}

void XML_Visitor::visit(AST_function_declaration *AST_node) {
    cout << indentation << "<Function_Decl>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    AST_node->identifier->accept(this);
    //checking if the optional variable is empty
    //if the optional variable is empty, it's accept function will not be called
    if(!AST_node->f_params->f_params->empty()){
        AST_node->f_params->accept(this);
    }
    AST_node->type->accept(this);
    AST_node->block->accept(this);
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Function_Decl>" << endl;
}

void XML_Visitor::visit(AST_block *AST_node) {
    cout << indentation << "<Block>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    //looping to call the accept function for all the nodes in the value of this node
    for(AST_node_statement *p: *AST_node->block){
        p->accept(this);
    }
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Block>" << endl;
}

//operators
void XML_Visitor::visit(AST_multiplicative_operator *AST_node) {
    cout << indentation << "<Mult_Op>" << "'" << AST_node->toString() << "'" << "</Mult_Op>" << endl;
}

void XML_Visitor::visit(AST_additive_operator *AST_node) {
    cout << indentation << "<Add_Op>" << "'" << AST_node->toString() << "'" << "</Add_Op>" << endl;
}

void XML_Visitor::visit(AST_relational_operator *AST_node) {
    cout << indentation << "<Rel_Op>" << "'" << AST_node->toString() << "'" << "</Rel_Op>" << endl;
}

void XML_Visitor::visit(AST_unary_operator *AST_node) {
    cout << indentation << "<Unary_Op>" << "'" << AST_node->toString() << "'" << "</Unary_Op>" << endl;
}

//others
void XML_Visitor::visit(AST_formal_param *AST_node) {
    cout << indentation << "<Formal_Param>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    AST_node->identifier->accept(this);
    AST_node->type->accept(this);
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Formal_Param>" << endl;
}

void XML_Visitor::visit(AST_formal_params *AST_node) {
    cout << indentation << "<Formal_Params>" << endl;
    //increasing the indentation by 1 tab
    indentation = indentation + "\t";
    //looping to call the accept function for all the nodes in the value of this node
    for(AST_formal_param *p: *AST_node->f_params){
        p->accept(this);
    }
    //decreasing the indentation by 1 tab
    indentation.pop_back();
    cout << indentation << "</Formal_Params>" << endl;
}

void XML_Visitor::visit(AST_type *AST_node) {
    cout << indentation << "<Type>" << "'" << AST_node->toString() << "'" << "</Type>" << endl;
}