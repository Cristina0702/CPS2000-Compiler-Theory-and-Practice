#include "Task1_Table-driven_Lexer/lexer.h"
#include "Task2_Parser/parser.h"
#include "Tasks3_4_5_Visitors/XML_Visitor/XML_Visitor.h"
#include "Tasks3_4_5_Visitors/Semantic_Analysis/semantic_analysis_visitor.h"

using namespace std;

int main(){
    //creating lexer object
    Lexer *lexer;
    //creating parser object
    Parser *parser;

    //creating the AST vector
    vector<AST_node*> *AST;

    //reading test file
    lexer->read_program("../test.txt");

    //calling Parser constructor with lexer
    parser = new Parser(lexer);

    //calling the parse_AST() function to develop the AST
    AST = parser->parse_AST();

    //creating XML_Visitor object
    XML_Visitor *XML_visitor = new XML_Visitor;
    //creating SA_Visitor object
    SA_Visitor *SA_visitor = new SA_Visitor;

    //looping through the AST
    if(AST != nullptr){
        //for each node in the AST
        for(AST_node *ast_node: *AST){
            //calling the SA_Visitor visit() function for the node
            //to perform Semantic Analysis
            ast_node->accept(SA_visitor);
            
            //calling the XML_Visitor visit() function for the node
            //to perform AST XML Generation
            ast_node->accept(XML_visitor);
        }
    }

    return 0;
}