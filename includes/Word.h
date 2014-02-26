#pragma once
#include "Token.h"

class Word :
	public Token
{
public:
	Word(std::string str, Tag t);
	virtual ~Word(void);

	virtual std::string toString();
	bool operator==(const Word& rhs);

	const static Word WordAND;
	const static Word WordOR;
	const static Word WordEQ;
	const static Word WordNE;
	const static Word WordLE;
	const static Word WordGE;
	const static Word WordMINUS;
	const static Word WordTRUE;
	const static Word WordFALSE;
	const static Word WordTEMP;
	const static Word WordNULL;

	std::string w_lexme;
};

