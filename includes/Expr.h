#pragma once
#include "Node.h"
#include "Token.h"
#include "Word.h"
#include "DataType.h"

#include <sstream>

class Expr: public Node
{
public:
	Expr(Token tok, DataType p);
	virtual ~Expr();

	bool operator==(const Expr& rhs);
	virtual Expr gen();
	virtual Expr reduce();
	virtual void jumping(int t, int f);
	virtual void emitJumps(std::string test, int t, int f);

	virtual std::string toString();

	Token op;
	DataType type;
	const static Expr ExprNULL; 
};

class Id: public Expr
{
public:
	Id(Token id, DataType p, int b);
	~Id();
private:
	int offset;
};

class Temp: public Expr
{
public:
	Temp(DataType p);
	~Temp();
	virtual std::string toString();
	
	static int count;
private:
	int number;	
};


class Constant: public Expr
{
public:
	Constant(Token tok, DataType p);
	Constant(int i);
	
	~Constant();

	virtual void jumping(int t, int f);

	const static Constant ConstantTRUE;
	const static Constant ConstantFALSE;
};