#pragma once
#include "Node.h"
#include "Token.h"
#include "Word.h"
#include "DataType.h"

#include <sstream>
#include <iostream>

class Expr: public Node
{
public:
	Expr();
	Expr(Token* tok, DataType* p);
	virtual ~Expr();

	bool operator==(const Expr& rhs);
	virtual Expr* gen();
	virtual Expr* reduce();
	virtual void jumping(int t, int f);
	virtual void emitJumps(std::string test, int t, int f);

	virtual std::string toString() const;

	friend std::ostream& operator<<(std::ostream& os, const Expr& expr);

	static Expr* ExprNULL; 

	Token* op;
	DataType* type;
	
};

class Id: public Expr
{
public:
	Id();
	Id(Token* id, DataType* p, int b);

	~Id();

	friend std::ostream& operator<<(std::ostream& os, const Id& id);
	
	static Id* IdNULL;
private:
	int offset;
};

class Temp: public Expr
{
public:
	Temp(DataType* p);
	~Temp();
	virtual std::string toString() const;
	
	friend std::ostream& operator<<(std::ostream& os, const Temp& temp);
	static int count;
private:
	int number;	
};


class Constant: public Expr
{
public:
	Constant(Token* tok, DataType* p);
	Constant(int i);
	
	~Constant();

	friend std::ostream& operator<<(std::ostream& os, const Constant& constant);

	virtual void jumping(int t, int f);

	static Constant* ConstantTRUE;
	static Constant* ConstantFALSE;
};