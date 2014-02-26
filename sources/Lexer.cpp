#include "Lexer.h"

int Lexer::line = 1;

Lexer::Lexer(void)
{
	reserve(Word("if", IF));
	reserve(Word("else", ELSE));
	reserve(Word("while", WHILE));
	reserve(Word("do", DO));
	reserve(Word("break", BREAK));
	reserve(Word::WordTRUE);
	reserve(Word::WordFALSE);
	reserve(DataType::TypeINT);
	reserve(DataType::TypeFLOAT);
	reserve(DataType::TypeCHAR);
	reserve(DataType::TypeBOOL);
}


Lexer::~Lexer(void)
{
}

Token Lexer::scan() {
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
			return Word::WordAND;
		} else {
			//return Token('&');
			return Token(BIT_AND);
		}
		break;
	case '|':
		if (readChar('|'))
		{
			return Word::WordOR;
		} else {
			//return Token('|');
			return Token(BIT_OR);
		}
		break;
	case '=':
		if (readChar('='))
		{
			return Word::WordEQ;
		} else {
			//return Token('=');
			return Token(ASSIGN);
		}
		break;
	case '<':
		if (readChar('='))
		{
			return Word::WordLE;
		} else {
			//return Token('<');
			return Token(LT);
		}
		break;
	case '>':
		if (readChar('='))
		{
			return Word::WordGE;
		} else {
			//return Token('>');
			return Token(GT);
		}
		break;
	case '!':
		if (readChar('='))
		{
			return Word::WordNE;
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
		float f = (float)v;
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
		if (w == Word::WordNULL)
		{
			Word idWord(id, ID);
			reserve(idWord);
			return idWord;
		} 
		return w;
	}
	Token tok(peekChar);
	peekChar = ' ';
	return tok;
}
void Lexer::reserve(Word w) {
	words.push_back(w);
}
Word Lexer::findByString(std::string& str) {
	for (std::vector<Word>::iterator iter = words.begin(); iter != words.end(); ++iter)
	{
		if (iter->w_lexme.compare(str) == 0)
		{
			return *iter;
		}
	}
	return Word::WordNULL;
}
void Lexer::readChar() {
	std::cin>>peekChar;
}
bool Lexer::readChar(char c) {
	readChar();
	if (peekChar != c)
	{
		return false;
	}
	peekChar = ' ';
	return true;
}