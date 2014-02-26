#include "../includes/lexer.hpp"
#include "../includes/symbols.hpp"
#include "../includes/inter.hpp"
#include "../includes/parser.hpp"

int main(int argc, char const *argv[])
{
	Lexer lexer;
	Parser parser(lexer);
	parser.parseProgram();

	return 0;
}