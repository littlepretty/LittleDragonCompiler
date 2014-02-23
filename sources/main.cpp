#include "includes/lexer.h"
#include "includes/parser.h"

int int main(int argc, char const *argv[])
{
	
	Lexer lexer();
	Parser parser(lexer);
	parser.parseProgram();

	return 0;
}