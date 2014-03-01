#pragma once
#include <iostream>
#include <vector>

#include "Word.h"
#include "DataType.h"

class Lexer
{
public:
	Lexer(void);
	virtual ~Lexer(void);
	Token* scan();
	static int line;

private:
	void reserve(Word w);
	Word* findByString(std::string& str);
	void readChar();
	bool readChar(char c);

	char peekChar;
	std::vector<Word> words;

};



