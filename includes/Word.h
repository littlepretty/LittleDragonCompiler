#pragma once
#include "Token.h"

class Word : public Token
{
public:
	Word(std::string str, Tag t);
	virtual ~Word(void);

	virtual std::string toString();
	bool operator==(const Word& rhs);

	friend bool operator<(const Word& lhs, const Word& rhs);

	static Word* WordAND;
	static Word* WordOR;
	static Word* WordEQ;
	static Word* WordNE;
	static Word* WordLE;
	static Word* WordGE;
	static Word* WordMINUS;
	static Word* WordTRUE;
	static Word* WordFALSE;
	static Word* WordTEMP;
	static Word* WordNULL;

	std::string w_lexme;
};

