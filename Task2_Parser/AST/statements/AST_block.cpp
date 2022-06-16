#include "AST_block.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_block::AST_block(vector<AST_node_statement*> *block){
    this->block = block;
}

AST_block::~AST_block(){
    block->clear();
}

void AST_block::accept(Visitor *visitor){
    visitor->visit(this);
}