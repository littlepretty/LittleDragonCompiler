#include <string>
#include <iostream>
#include <sstream>


typedef enum tag
{
	AND = 256, BASIC, BREAK, DO, ELSE, EQ, FALSE, GE, IN, IF,
	BIT_AND, BIT_OR, NOT, ASSIGN, GT, LT, 
	INDEX, LE, MINUS, NE, NUM, OR, REAL, TEMP, TRUE, WHILE

} Tag;

class Token
{
public:
	Token(Tag t):t_tag(t) {} ;
	virtual ~Token();
	virtual std::string toString() { 
		std::stringstream result;
		result<<t_tag;
		return result.str(); 
	}
private:
	const Tag t_tag;
};

class Num : public Token
{
public:
	Num(int val):Token(NUM),value(val) {};
	~Num();
	virtual std::string toString() { 
		std::stringstream result;
		result<<Token::toString()<<" value = "<<value;
		return result.str();
	}
private:
	const int value;
};

class Word : public Token
{
public:
	Word(std::string str, Tag t):Token(t), lexme(str) {};
	virtual ~Word();
	virtual std::string toString(){
		return Token::toString() + lexme;
	}

	bool operator==(const Word& rhs) {
		return this->lexme.compare(rhs.lexme) == 0;
	}

private:
	std::string lexme;

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
	
};

Word Word::WordAND("&&", AND);
Word Word::WordOR("||", OR);
Word Word::WordEQ("==", EQ);
Word Word::WordNE("!=", NE);
Word Word::WordLE("<=", LE);
Word Word::WordGE(">=", GE);
Word Word::WordMINUS("minus", MINUS);
Word Word::WordTRUE("true", TRUE);
Word Word::WordFALSE("false", FALSE);
Word Word::WordTEMP("temp", TEMP);

class Real : public Token
{
public:
	Real(float val):Token(REAL), value(val) {};
	~Real();
	virtual std::string toString(){
		std::stringstream result;
		result<<Token::toString()<<" value = "<<value;
		return result.str();
	}
private:
	float value;
};

class Env
{
public:
	Env(Env* n):prev(n) {};
	~Env();
	void put(Token w, Id i) {
		table[w] = i;
	}
	Id get(Token w) {
		for (Env* e = this; e != NULL; e=e->prev)
		{
			std::map<Token, Id>::iterator found = e->table.find(w);
			if (found != std::map<Token, Id>::end())
			{
				return found->second;
			}
		}
		return NULL;
	}
protected:
	Env* prev;
private:
	std::map<Token, Id> table;

};


class Type: public Word
{
public:
	Type(std::string str, Tag t, int w):Word(str,t),width(w) {};
	~Type();

	int width;
};

class Array: public Type
{
public:
	Array(int sz, Type p):Type("[]", INDEX, sz*p.width), size(sz), of(p) {};
	~Array();
	virtual std::string toString() {
		std::stringstream result;
		result<<"["<<size<<"]"<<of.toString();
	}

private:
	int size;
	Type of;
	static Type TypeINT;
	static Type TypeFLOAT;
	static Type TypeCHAR;
	static Type TypeBOOL;
};

Type Type::TypeINT("int", BASIC, 4);
Type Type::TypeFLOAT("float", BASIC, 4);
Type Type::TypeCHAR("char", BASIC, 1);
Type Type::TypeBOOL("bool", BASIC, 1);

bool numeric(Type p) 
{
	if (p == TypeINT || p == TypeFLOAT || p == TypeCHAR)
	{
		return true;
	} else {
		return false;
	}
}

Type max(Type p1, Type p2) 
{
	if (!numeric(p1) && !numeric(p2))
	{
		return NULL;
	} else if (p1 == TypeFLOAT || p2 == TypeFLOAT)
	{	
		return TypeFLOAT;
	} else if (p1 == TypeINT || p2 == TypeINT)
	{
		return TypeINT;
	} else {
		return TypeCHAR;
	}

}