
#include "Lexer.h"
#include "Parser.h"

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

int main() 
{
	//MyStruct ms;
	//testPointer(&ms);


	Lexer *lex = new Lexer("sample.dc");
	Parser parser(lex);
	parser.program();

	return 0;
}

