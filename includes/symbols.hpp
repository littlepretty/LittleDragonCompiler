#include <string>
#include <iostream>
#include <sstream>


typedef enum tag
{
	AND = 256, BASIC, BREAK, DO, ELSE, EQ, FALSE, GE, IN, IF,
	INDEX, LE, MINUS, NE, NUM, OR, REAL, TEMP, TRUE, WHILE
} Tag;

class Token
{
public:
	Token(Tag t):tag(t) {} ;
	virtual ~Token();
	virtual std::string toString() { return "" + (char)tag; }
private:
	const Tag tag;
};

class Num : public Token
{
public:
	Num(int val):Token(NUM),value(val) {};
	~Num();
	virtual std::string toString() { 
		std::stringstream result;
		result<<Token::toString<<" value = "<<value;
		return result.str();
	}
private:
	const int value;
};

class Word
{
public:
	Word(std::string str, Tag t):Token(t), lexme(str) {};
	virtual ~Word();
	virtual std::string toString(){
		return Token::toString + lexme;
	}

private:
	std::string lexme;
	
};

static Word WordAND("&&", AND);
static Word WordOR("||", OR);
static Word WordEQ("==", EQ);
static Word WordNE("!=", NE);
static Word WordLE("<=", LE);
static Word WordGE(">=", GE);
static Word WordMINUS("minus", MINUS);
static Word WordTRUE("true", TRUE);
static Word WordFALSE("false", FALSE);
static Word WordTEMP("temp", TEMP);

class Real
{
public:
	Real(float val):Token(REAL), value(val) {};
	~Real();
	virtual std::string toString(){
		std::stringstream result;
		result<<Token::toString<<" value = "<<value;
		return result.str();
	}
private:
	float value;
};



class Type: public Word
{
public:
	Type(std::string str, Tag t, int w):Word(str,t),width(w) {};
	~Type();

private:
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
	
};

static Type TypeINT("int", BASIC, 4);
static Type TypeFLOAT("float", BASIC, 4);
static Type TypeCHAR("char", BASIC, 1);
static Type TypeBOOL("bool", BASIC, 1);

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