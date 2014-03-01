
#include "Lexer.h"
#include "Parser.h"

int main() 
{
	Lexer *lex = new Lexer("text.dc");
	Parser parser(lex);
	parser.program();

	return 0;
}

