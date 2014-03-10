#pragma once

#include <string>
#include <iostream>

typedef enum tag
{
	AND = 256, BASIC, BREAK, DO, ELSE, EQ, FALSE, GE, IF, ID,
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
	virtual std::string toString() const;
	bool operator==(const Token& rhs) {
		return this->t_tag == rhs.t_tag;
	}
	friend std::ostream& operator<<(std::ostream& os, const Token& tok);

	Tag t_tag;
};

class Num : public Token
{
public:
	Num(int val);
	~Num();
	virtual std::string toString() const; 
	friend std::ostream& operator<<(std::ostream& os, const Num& tok);

	const int n_value;
};

class Real : public Token
{
public:
	Real(float val);
	~Real();
	virtual std::string toString() const;
	friend std::ostream& operator<<(std::ostream& os, const Real& tok);

private:
	float r_value;
};