#pragma once
#include <iostream>
#include <vector>
#include <fstream>

#include "Word.h"
#include "DataType.h"

class Lexer
{
public:
	Lexer(std::string sourceFileName);
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
	std::ifstream source;
};



