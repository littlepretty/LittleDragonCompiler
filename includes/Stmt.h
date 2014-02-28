#pragma once
#include "Node.h"
#include "Expr.h"
#include "Op.h"

class Stmt : public Node
{
public:
	Stmt(void);
	virtual ~Stmt(void);
	virtual void gen(int b, int a){};
	bool operator==(const Stmt& rhs);
	static Stmt StmtNULL;
	static Stmt Enclosing;

	int after;
};


class If: public Stmt
{
public:
	If(Expr e, Stmt s);
	~If();

	virtual void gen(int b, int a);
private:
	Expr test;
	Stmt stmt;
};

class Else: public Stmt
{
public:
	Else(Expr e, Stmt s1, Stmt s2);
	~Else();
	virtual void gen(int b, int a);
private:
	Expr test;
	Stmt stmt1;
	Stmt stmt2;
};

class While: public Stmt
{
public:
	While();
	void init(Expr e, Stmt s);
	~While();
	virtual void gen(int b, int a);

private:
	Expr test;
	Stmt stmt;
};


class Do: public Stmt
{
public:
	Do();
	void init(Expr e, Stmt s);
	~Do();
	virtual void gen(int b, int a);

private:
	Expr test;
	Stmt stmt;
};

class Set: public Stmt
{
public:
	Set(Id i, Expr e);
	~Set();
	virtual void gen(int b, int a);

private:
	Id id;
	Expr exp;

};

class SetElem: public Stmt
{
public:
	SetElem(Access x, Expr e);
	~SetElem();
	virtual void gen(int b, int a);

private:
	Id array;
	Expr index;
	Expr exp;
};

class Break: public Stmt
{
public:
	Break();
	~Break();
	virtual void gen(int b, int a);

private:
	Stmt stmt;
};


class Seq: public Stmt
{
public:
	Seq(Stmt s1, Stmt s2);
	~Seq();
	virtual void gen(int b, int a);
private:
	Stmt stmt1;
	Stmt stmt2;
};














