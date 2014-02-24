#include "includes/lexer.hpp"
#include "includes/parser.hpp"

int int main(int argc, char const *argv[])
{
	Lexer lexer;
	Parser parser(lexer);
	parser.parseProgram();

	return 0;
}