#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "symbols.hpp"


class Lexer
{
public:
	Lexer() {
		reserve(Word("if", IF));
		reserve(Word("else", ELSE));
		reserve(Word("while", WHILE));
		reserve(Word("do", DO));
		reserve(Word("break", BREAK));
		reserve(WordTRUE);
		reserve(WordFALSE);
		reserve(TypeINT);
		reserve(TypeFLOAT);
		reserve(TypeCHAR);
		reserve(TypeBOOL);
	};
	~Lexer();

	Token scan() {
		for ( ; ; readChar())
		{	
			if (peekChar == ' ' || peekChar == '\t')
			{	
				continue;
			} else if (peekChar == '\n')
			{
				line++;
			} else {
				break;
			}
		}

		switch(peekChar) {
			case '&':
				if (readChar('&'))
				{
					return WordAND;
				} else {
					//return Token('&');
					return Token(BIT_AND);
				}
				break;
			case '|':
				if (readChar('|'))
				{
					return WordOR;
				} else {
					//return Token('|');
					return Token(BIT_OR);
				}
				break;
			case '=':
				if (readChar('='))
				{
					return WordEQ;
				} else {
					//return Token('=');
					return Token(ASSIGN);
				}
				break;
			case '<':
				if (readChar('='))
				{
					return WordLE;
				} else {
					//return Token('<');
					return Token(LT);
				}
				break;
			case '>':
				if (readChar('='))
				{
					return WordGE;
				} else {
					//return Token('>');
					return Token(GT);
				}
				break;
			case '!':
				if (readChar('='))
				{
					return WordNE;
				} else {
					//return Token('!');
					return Token(NOT);
				}
				break;
			default:
				break;		
		}
		if (isdigit(peekChar))
		{
			int v = 0;
			do
			{
				v = v*10 + (peekChar-'0');
				readChar();
			} while (isdigit(peekChar));
			if (peekChar != '.')
			{	
				return Token(NUM);	
			}
			float f = v;
			float d = 10;
			while(isdigit(peekChar)) {
				f = f + (float)(peekChar-'0')/d;
				d = d * 10;
			}
			return Token(REAL);
		}
		if (isalpha(peekChar))
		{
			std::stringstream idSS;
			do
			{
				idSS<<peekChar;
				readChar();
			} while (isalpha(peekChar));
			std::string id = idSS.str();
			Word w = findByString(id);
			if (w == NULL)
			{
				w = Word(id, ID);
				reserve(w);
			} 
			return w;
		}
		Token tok(peekChar);
		peekChar = ' ';
		return tok;
	}
	

private:
	void reserve(Word w) {
		words.push_back(w);
	}
	Word findByString(std::string& str) {
		for (std::vector<words>::iterator iter = words.begin(); iter != words.end(); ++iter)
		{
			if (iter->lexme.compare(str) == 0)
			{
				return *iter;
			}
		}
		return NULL;
	}
	void readChar() {
		std::cin>>peekChar;
	}
	bool readChar(char c) {
		readChar();
		if (peekChar != c)
		{
			return false;
		}
		peekChar = ' ';
		return true;
	}

	static int line;
	char peekChar;
	std::vector<Word> words;

};

int Lexer::line = 1;
