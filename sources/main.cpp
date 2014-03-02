
#include "Lexer.h"
#include "Parser.h"

int main() 
{
	Lexer *lex = new Lexer("sample.dc");
	Parser parser(lex);
	parser.program();

	return 0;
}

