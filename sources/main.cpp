
#include "Lexer.h"
#include "Parser.h"
#include <fstream>

struct MyStruct
{
	int *pInt;
	MyStruct *next;
};

void testPointer(MyStruct *father)
{
	int *pi1 = new int(10);
	int *pi2 = new int(100);

	MyStruct* son = new MyStruct;
	son->pInt = pi2;
	son->next = NULL;

	father->pInt = pi1;
	father->next = son;

	delete son;
}

std::ofstream intermediaRepresentStream;

int main() 
{
	//MyStruct ms;
	//testPointer(&ms);

	intermediaRepresentStream.open("sample.ir", std::ios::out);
	if (!intermediaRepresentStream.is_open())
	{
		std::cout << "Fail to Open File for Output IR" << std::endl;
		exit(1);
	}

	Lexer *lex = new Lexer("sample.dc");
	Parser parser(lex);
	parser.program();

	return 0;
}

