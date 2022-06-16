#include "AST_type.h"

#include "../../../Tasks3_4_5_Visitors/visitor.h"

AST_type::AST_type(Type t){
    this->type = t;
}

AST_type::~AST_type() = default;

string AST_type::toString(){
    if(type == Type::Float){
        return "float";
    }else if(type == Type::Int){
        return "int";
    }else if(type == Type::Bool){
        return "bool";
    }else if(type == Type::Char){
        return "char";
    }
}

void AST_type::accept(Visitor *Visitor){
    visitor->visit(this)
}