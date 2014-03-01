#include "Word.h"

Word* Word::WordAND = new Word("&&", AND);
Word* Word::WordOR = new Word("||", OR);
Word* Word::WordEQ = new Word("==", EQ);
Word* Word::WordNE = new Word("!=", NE);
Word* Word::WordLE = new Word("<=", LE);
Word* Word::WordGE = new Word(">=", GE);
Word* Word::WordMINUS = new Word("minus", MINUS);
Word* Word::WordTRUE = new Word("true", TRUE);
Word* Word::WordFALSE = new Word("false", FALSE);
Word* Word::WordTEMP = new Word("temp", TEMP);
Word* Word::WordNULL = new Word("null", TAG_NULL);

Word::Word(std::string str, Tag t):Token(t),w_lexme(str)
{
}


Word::~Word(void)
{
}

std::string Word::toString()
{
	return Token::toString() + w_lexme;
}

bool Word::operator==(const Word& rhs) 
{
	return this->w_lexme.compare(rhs.w_lexme) == 0;
}

bool operator<(const Word& lhs, const Word& rhs)
{
	return lhs.w_lexme.compare(rhs.w_lexme) < 0;
}