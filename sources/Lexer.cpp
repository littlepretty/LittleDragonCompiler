#include "Lexer.h"

int Lexer::line = 1;

Lexer::Lexer(std::string sourceFileName)
{
	reserve(Word("if", IF));
	reserve(Word("else", ELSE));
	reserve(Word("while", WHILE));
	reserve(Word("do", DO));
	reserve(Word("break", BREAK));
	reserve(*Word::WordTRUE);
	reserve(*Word::WordFALSE);
	reserve(*DataType::TypeINT);
	reserve(*DataType::TypeFLOAT);
	reserve(*DataType::TypeCHAR);
	reserve(*DataType::TypeBOOL);

	source.open(sourceFileName.c_str(), std::ios::in); 
	source.unsetf(std::ios::skipws);
	if (!source.is_open())
	{
		std::cout << "Fail to Open File " << sourceFileName << std::endl;
		exit(1);
	}
}


Lexer::~Lexer(void)
{
}

Token* Lexer::scan() {
	for ( ; ; readChar())
	{	
		if (peekChar == ' ' || peekChar == '\t')
		{	
			continue;
		} else if (peekChar == '\n')
		{
			line++;
		} else if (peekChar > 0)
		{
			break;
		}
	}

	switch(peekChar) {
	case '&':
		if (readChar('&'))
		{
			std::cout<<(*Word::WordAND);
			return Word::WordAND;
		} else {
			//return Token('&');
			return new Token('&');
		}
		break;
	case '|':
		if (readChar('|'))
		{
			std::cout<<(*Word::WordOR);
			return Word::WordOR;
		} else {
			//return Token('|');
			return new Token('|');
		}
		break;
	case '=':
		if (readChar('='))
		{
			std::cout<<(*Word::WordEQ);
			return Word::WordEQ;
		} else {
			//return Token('=');
			return new Token('=');
		}
		break;
	case '<':
		if (readChar('='))
		{
			std::cout<<(*Word::WordLE);
			return Word::WordLE;
		} else {
			//return Token('<');
			return new Token('<');
		}
		break;
	case '>':
		if (readChar('='))
		{
			std::cout<<(*Word::WordGE);
			return Word::WordGE;
		} else {
			//return Token('>');
			return new Token('>');
		}
		break;
	case '!':
		if (readChar('='))
		{
			std::cout<<(*Word::WordNE);
			return Word::WordNE;
		} else {
			//return Token('!');
			return new Token('!');
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
			std::cout<<"Int Value\t"<<v<<std::endl;
			return new Token(NUM);	
		}
		float f = (float)v;
		float d = 10;
		while(isdigit(peekChar)) {
			f = f + (float)(peekChar-'0')/d;
			d = d * 10;
		}
		std::cout<<"Real Value\t"<<v<<std::endl;
		return new Token(REAL);
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
		Word* w = findByString(id);
		if (w == Word::WordNULL)
		{
			Word* idWord = new Word(id, ID);
			reserve(*idWord);
			std::cout<<(*idWord);
			return idWord;
		} 
		std::cout<<(*w);
		return w;
	}
	Token* tok = new Token(peekChar);
	peekChar = ' ';
	std::cout<<(*tok);
	return tok;
}

void Lexer::reserve(Word w) {
	words.push_back(w);
}

Word* Lexer::findByString(std::string& str) {
	for (std::vector<Word>::iterator iter = words.begin(); iter != words.end(); ++iter)
	{
		if (iter->w_lexme.compare(str) == 0)
		{
			return &(*iter);
		}
	}
	return Word::WordNULL;
}

void Lexer::readChar() 
{
	if (source.good())
	{
		source>>peekChar;
	}
	
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