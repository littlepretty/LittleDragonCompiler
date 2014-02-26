#include "Token.h"
#include <sstream>

Token::Token(Tag t): t_tag(t)
{
}

Token::Token(char t): t_tag((Tag)t)
{
}

Token::~Token(void)
{
}

std::string Token::toString()
{
	std::stringstream result;
	result<<t_tag;
	return result.str(); 
}

Num::Num(int val):Token(NUM), n_value(val)
{
}

Num::~Num()
{
}

std::string Num::toString()
{
	std::stringstream result;
	result<<Token::toString()<<" value = "<<n_value;
	return result.str();
}

Real::Real(float val):Token(REAL), r_value(val) 
{
}

Real::~Real()
{
}

std::string Real::toString()
{
	std::stringstream result;
	result<<Token::toString()<<" value = "<<r_value;
	return result.str();
}