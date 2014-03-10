#include "Node.h"
#include "Lexer.h"
#include "ExternGlobal.h"


int Node::label = 0;



Node::Node(void)
{
	lexerLine = Lexer::line; 
}

Node::~Node(void)
{

}

void Node::error(std::string str) 
{
	std::cerr<<"Near Line "<<lexerLine<<": "<<str<<std::endl;
	intermediaRepresentStream << "Near Line " << lexerLine << ": " << str << std::endl;
}

int Node::newLabel() 
{
	return ++label;
}

void Node::emitLabel(int i) 
{
	std::cout<<"L"<<i<<":";
	intermediaRepresentStream << "L" << i << ":";
}

void Node::emit(std::string str) 
{
	std::cout<<"\t"<<str<<std::endl;
	intermediaRepresentStream << "\t" << str << std::endl;
}