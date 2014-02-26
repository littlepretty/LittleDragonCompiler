#pragma once
#include "Expr.h"
#include "DataType.h"

DataType check(DataType p1, DataType p2);

class Logical :	public Expr
{
public:
	Logical(Token tok, Expr e1, Expr e2);
	virtual ~Logical(void);

	virtual Expr gen();
	virtual std::string toString();
	Expr exp1, exp2;
};

class Or: public Logical
{
public:
	Or(Token tok, Expr e1, Expr e2);
	~Or();
	virtual void jumping(int t, int f);
};

class And: public Logical
{
public:
	And(Token tok, Expr e1, Expr e2);
	~And();
	virtual void jumping(int t, int f);
};

class Not: public Logical
{
public:
	Not(Token tok, Expr e);
	~Not();
	virtual void jumping(int t, int f);
	virtual std::string toString();
};

class Rel: public Logical
{
public:
	Rel(Token tok, Expr e1, Expr e2);
	~Rel();
	virtual void Rel::jumping(int t, int f);
};