#include "Word.h"

const Word Word::WordAND("&&", AND);
const Word Word::WordOR("||", OR);
const Word Word::WordEQ("==", EQ);
const Word Word::WordNE("!=", NE);
const Word Word::WordLE("<=", LE);
const Word Word::WordGE(">=", GE);
const Word Word::WordMINUS("minus", MINUS);
const Word Word::WordTRUE("true", TRUE);
const Word Word::WordFALSE("false", FALSE);
const Word Word::WordTEMP("temp", TEMP);
const Word Word::WordNULL("null", TAG_NULL);

Word::Word(std::string str, Tag t):Token(t),w_lexme(str)
{
}


Word::~Word(void)
{
}

std::string Word::toString(){
	return Token::toString() + w_lexme;
}

bool Word::operator==(const Word& rhs) {
	return this->w_lexme.compare(rhs.w_lexme) == 0;
}