#pragma once

//forward declaration to import Visitor class in subclasses
class Visitor;

class AST_node{
    public:
        //abstract class destructor 
        virtual ~AST_node() = default;
        virtual void accept(Visitor *vistor) = 0;
};