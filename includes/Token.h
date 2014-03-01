#pragma once

#include <string>

typedef enum tag
{
	AND = 256, BASIC, BREAK, DO, ELSE, EQ, FALSE, GE, IN, IF, ID,
	BIT_AND, BIT_OR, NOT, ASSIGN, GT, LT, 
	INDEX, LE, MINUS, NE, NUM, OR, REAL, TEMP, TRUE, WHILE,
	TAG_NULL
} Tag;

class Token
{
public:
	Token();
	Token(Tag t);
	Token(char c);
	virtual ~Token(void);
	virtual std::string toString();
	bool operator==(const Token& rhs) {
		return this->t_tag == rhs.t_tag;
	}

	Tag t_tag;
};

class Num : public Token
{
public:
	Num(int val);
	~Num();
	virtual std::string toString(); 

	const int n_value;
};

class Real : public Token
{
public:
	Real(float val);
	~Real();
	virtual std::string toString();
private:
	float r_value;
};