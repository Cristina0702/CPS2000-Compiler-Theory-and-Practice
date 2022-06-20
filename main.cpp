#include "Task1_Table-driven_Lexer/lexer.h"
#include "Task2_Parser/parser.h"
#include "Tasks3_4_5_Visitors/XML_Visitor/XML_Visitor.h"
#include "Tasks3_4_5_Visitors/Semantic_Analysis/semantic_analysis_visitor.h"

using namespace std;

int main(){
    Lexer *lexer;
    Parser *parser;

    lexer = new Lexer();
    parser = new Parser(lexer);
}