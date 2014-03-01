#pragma once
#include "Expr.h"
#include "Token.h"
#include "DataType.h"

class Op : public Expr
{
public:
	Op(Token* tok, DataType* p);
	virtual ~Op(void);

	virtual Expr* reduce();
};

class Arith: public Op
{
public:
	Arith(Token* tok, Expr* e1, Expr* e2);
	~Arith();

	virtual Expr* gen();
	virtual std::string toString();

private:
	Expr* exp1;
	Expr* exp2;
};

class Unary: public Op
{
public:
	Unary(Token* tok, Expr* e);
	~Unary();
	virtual Expr* gen();
	virtual std::string toString();
private:
	Expr* exp;
};

class Access: public Op
{
public:
	Access(Id* a, Expr* i, DataType* p);
	~Access();

	virtual Expr* gen();
	virtual void jumping(int t, int f);
	virtual std::string toString();

	Id* array;
	Expr* index;
};