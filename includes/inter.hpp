#include <string>
#include <iostream>
#include "lexer.hpp"
#include "symbols.hpp"

class Node
{
public:
	Node() { lexLine = Lexer::line; };
	virtual ~Node();
	void error(std::string str) {
		std::cerr<<"Near Line "<<lexLine<<": "<<str<<std::endl;
	}
	void newLabel() {
		label++;
	}
	void emitLabel(int i) {
		std::cout<<"L"<<i<<":";
	}
	void emit(std::string str) {
		std::cout<<"\t"<<str<<std::endl;
	}
private:
	int lexLine;
	static int label;

};

int Node::label = 0;

class Expr: public Node
{
public:
	Expr(Token tok, Type p):op(tok), type(p) {};
	virtual ~Expr();

	virtual Expr gen() {
		return *this;
	}
	virtual Expr reduce() {
		return *this;
	}
	virtual void jumping(int t, int f) {
		emitJumps(toString(), t, f);
	}
	virtual void emitJumps(std::string test, int t, int f) {
		std::stringstream ifPart, elsePart;
		if (t != 0 && f !=0)
		{
			ifPart<<"if "<<test<<" goto L"<<t;
			elsePart<<"goto L"<<f;
			emit(ifPart.str());
			emit(elsePart.str());
		} else if (t != 0)
		{
			ifPart<<"if "<<test<<" goto L"<<t;
			emit(ifPart.str());
		} else if (f != 0)
		{
			elsePart<<"iffalse "<<test<<" goto L"<<f;
			emit(elsePart.str());
		} else {

		}

	}
	virtual std::string toString() {
		return op.toString();
	}
private:
	Token op;
	Type type;
};

class Id: public Expr
{
public:
	Id(Word id, Type p, int b):Expr(id, p), offset(b) {};
	~Id();
private:
	int offset;
};

class Temp: public Expr
{
public:
	Temp(Type p): Expr(WordTEMP, p) {
		number = ++count;
	};
	~Temp();
	virtual std::string toString() {
		std::stringstream result;
		result<<"t"<<number;
		return result.str();
	}
private:
	int number;	
	static int count;
};

static int count = 0;

class Constant;



class Constant: public Expr
{
public:
	Constant(Token tok, Type p): Expr(tok,p) {};
	Constant(int i): Expr(Num(i), TypeINT) {};
	~Constant();
	virtual jumping(int t, int f) {
		if (*this == ConstantTRUE && t != 0)
		{
			std::stringstream result;
			result<<"goto L"<<t;
			emit(result.str());
		} else if (*this == ConstantFALSE && f != 0)
		{
			std::stringstream result;
			result<<"goto L"<<f;
			emit(result.str());
		}
	}

	static Constant ConstantTRUE;
	static Constant ConstantTRUE;
};

Constant Constant::ConstantTRUE(WordTRUE, TypeBOOL);
Constant Constant::ConstantTRUE(WortFALSE, TypeBOOL);

class Op: public Expr
{
public:
	Op(Token tok, Type p):Expr(tok, p) {};
	virtual ~Op();
	virtual Expr reduce() {
		Expr x = gen();
		Temp temp(Type);
		emit(temp.toString + " = " + x.toString());
		return temp;
	}
};

class Arith: public Op
{
public:
	Arith(Token tok, Expr e1, Expr e2):Op(tok, NULL), exp1(e1), exp2(e2) {
		type = max(exp1.type, exp2.type);
		if (type == NULL)
		{
			error("Type Error");
		}
	};
	~Arith();

	virtual Expr gen() {
		return Arith(op, exp1.reduce(), exp2.reduce());
	}

	virtual std::string toString() {
		return exp1.toString() + " " + op.toString() + " " + exp2.toString();
	}

private:
	Expr exp1, exp2;
};

class Unary: public Op
{
public:
	Unary(Token tok, Expr e):Op(tok, NULL), exp(e) {
		type = max(TypeINT, e.type);
		if (type == NULL)
		{
			error("Type Error");
		}
	};
	~Unary();
	virtual Expr gen() {
		return Unary(op, exp.reduce());
	}
	virtual std::string toString() {
		return op.toString() + " " + exp.toString;
	}
private:
	Expr exp;
};

class Access: public Op
{
public:
	Access(Id a, Expr i, Type p): Op("[]",INDEX,p), array(a), index(i) {};
	~Access();

	virtual Expr gen() {
		return Access(array, index.reduce(), type);
	}
	virtual void jumping(int t, int f) {
		emitJumps(reduce().toString(),t,f);
	}
	virtual std::string toString() {
		return array.toString() + " [ " + index.toString() + " ] ";
	}
private:
	Id array;
	Expr index;

};

class Logical: public Expr
{
public:
	Logical(Token tok, Expr e1, Expr e2): Expr(tok, NULL), exp1(e1), exp2(e2) {
		type = check(exp1.type, exp2.type);
		if (type == NULL)
		{
			error("Type Error");
		}
	};
	virtual ~Logical();

	virtual Type check(Type p1, Type p2) {
		if (p1.type == TypeBOOL && p2.type == TypeBOOL)
		{
			return TypeBOOL;
		} else if (p1.type == TypeINT && p2.type == TypeINT)
		{
			return TypeBOOL;
		} else if (p1.type == TypeFLOAT && p2.type == TypeFLOAT)
		{
			return TypeBOOL;
		} else if (p1.type == TypeCHAR && p2.type == TypeCHAR)
		{
			return TypeBOOL;
		} else {
			return NULL;
		}
	}
	virtual Expr gen(){
		int f = newLabel();
		int a = newLabel();
		Temp temp(type);
		this->jumping(0, f);
		emit(temp.toString() + " = true");
		std::stringstream result;
		result<<"goto L"<<a;
		emit(result.str());
		emitLabel(f);
		emit(temp.toString + " = false");
		emitLabel(a);
		return temp;
	}
	virtual std::string toString() {
		return exp1.toString() + " " + op.toString() + " " + exp2.toString();
	}
	
private:
	Expr exp1, exp2;
};

class Or: public Logical
{
public:
	Or(Token tok, Expr e1, Expr e2):Logical(tok,e1,e2) {};
	~Or();
	virtual void jumping(int t, int f) {
		int label = t != 0 ? t : newLabel();
		exp1.jumping(label,0);
		exp2.jumping(t,f);
		if (t == 0)
		{
			emitLabel(label);
		}
	}
};

class And: public Logical
{
public:
	And(Token tok, Expr e1, Expr e2):Logical(tok,e1,e2) {};
	~And();
	virtual void jumping(int t, int f) {
		int label = f !=0 ? f : newLabel();
		exp1.jumping(0, label);
		exp2.jumping(t,f);
		if (f == 0)
		{
			emitLabel(label);
		}
	}

};

class Not: public Logical
{
public:
	Not(Token tok, Expr e):Logical(tok,e,e) {};
	~Not();
	virtual void jumping(int t, int f) {
		jumping(f,t);
	}
	virtual std::string toString() {
		return op.toString() + " " + exp2.toString();
	}
	
};

class Rel: public Logical
{
public:
	Rel(Token tok, Expr e1, Expr e2):Logical(tok,e1,e2) {};
	~Rel();

	virtual void jumping(int t, int f) {
		Expr a = exp1.reduce();
		Expr b = exp2.reduce();
		std::string test = a.toString() + " " + op.toString() + " " + b.toString();
		emitJumps(test, t, f);
	}
	
};

class Stmt: public Node
{
public:
	Stmt();
	virtual ~Stmt();
	virtual void gen(int b, int a) {};

	static Stmt StmtNULL;
	static Stmt Enclosing;
private:
	int after;
};

Stmt Stmt::StmtNULL;
Stmt Stmt::Enclosing = Stmt::StmtNULL;


class If: public Stmt
{
public:
	If(Expr e, Stmt s):test(e), stmt(s) {
		if (test.type != TypeBOOL)
		{
			test.error("Require BOOL in If Stmt");
		}

	};
	~If();

	virtual void gen(int b, int a) {
		int label = newLabel();
		test.jumping(0,a);
		emitLabel(label);
		stmt.gen(label,a);
	}
private:
	Expr test;
	Stmt stmt;
};

class Else: Stmt
{
public:
	Else(Expr e, Stmt s1, Stmt s2):test(e), stmt1(s1), stmt2(s2) {
		if (test.type != TypeBOOL)
		{
			test.error("Require BOOL in If Stmt");
		}
	};
	~Else();
	virtual void gen(int b, int a){
		int label1 = newLabel();
		int label2 = newLabel();
		test.jumping(0,label2);
		
		emitLabel(label1);
		stmt1.gen(label1, a);
		std::stringstream gt;
		gt<<"goto L"<<a;
		emit(gt.str());

		emitLabel(label2);
		stmt2.gen(label2,a);
	}
private:
	Expr test;
	Stmt stmt1;
	Stmt stmt2;
};

class While: public Stmt
{
public:
	While():test(NULL),stmt(NULL) {};
	void init(Expr e, Stmt s) {
		test = e;
		stmt = s;
		if (test.type != TypeBOOL)
		{
			test.error("Require BOOL in If Stmt");
		}
	}
	~While();
	virtual void gen(int b, int a) {
		after = a;
		test.jumping(0,a);
		int label = newLabel();
		emitLabel(label);
		stmt.gen(label,b);

		std::stringstream gt;
		gt<<"goto L"<<b;
		emit(gt.str());
	}

private:
	Expr test;
	Stmt stmt;
};

class Do: public Stmt
{
public:
	Do():test(NULL),stmt(NULL) {};
	void init(Expr e, Stmt s) {
		test = e;
		stmt = s;
		if (test.type != TypeBOOL)
		{
			test.error("Require BOOL in If Stmt");
		}
	}
	~Do();
	virtual void gen(int b, int a) {
		after = a;
		int label = newLabel();
		stmt.gen(b,label);
		emitLabel(label);
		test.jumping(b,0);
	}

private:
	Expr test;
	Stmt stmt;
	
};

class Set: public Stmt
{
public:
	Set(Id i, Expr e):id(i), exp(e) {
		if (check(id.type, exp.type) == NULL)
		{
			error("Type Error");
		}
	};
	Type check(Type p1, Type p2) {
		if (numeric(p1) && numeric(p2))
		{
			return p2;
		} else if (p1 == TypeBOOL && p2 == TypeBOOL)
		{
			return p2;
		} else {
			return NULL;
		}
	}
	~Set();
	virtual void gen(int b, int a) {
		emit(id.toString() + " = " + exp.gen.toString());
	}

private:
	Id id;
	Expr exp;
	
};

class SetElem: public Stmt
{
public:
	SetElem(Access x, Expr e)exp(e) {
		array = x.array;
		index = x.index;
		if (check(x.type, exp.type) == NULL)
		{
			error("Type Error");
		}
	};
	Type check(Type p1, Type p2) {
		if (numeric(p1) && numeric(p2))
		{
			return p2;
		} else if (p1 == TypeBOOL && p2 == TypeBOOL)
		{
			return p2;
		} else {
			return NULL;
		}
	}
	~SetElem();

	virtual void gen(int b, int a) {
		std::string s1 = index.reduce().toString();
		std::string s2 = exp.reduce().toString();
		emit(array.toString() + " [ " + s1 + "] = " + s2);
	}

private:
	Id array;
	Expr index;
	Expr exp;
};

class Break: public Stmt
{
public:
	Break() {
		if (StmtNULL::StmtNULL == Stmt::Enclosing)
		{
			error("Unenclosed Break");
		}
		stmt = Enclosing;
	};
	~Break();
	virtual void gen(int b, int a) {
		std::stringstream gt;
		gt<<"goto L"<<after;
		emit(gt.str());
	}
private:
	Stmt stmt;
	
};

class Seq: public Stmt
{
public:
	Seq(Stmt s1, Stmt s2):stmt1(s1), stmt2(s2) {};
	~Seq();
	virtual void gen(int b, int a) {
		if (stmt1 == StmtNULL)
		{
			stmt2.gen(b, a);
		} else if (stmt2 == StmtNULL)
		{
			stmt1.gen(b, a);
		} else {
			int label = newLabel();
			stmt1.gen(b, label);
			emitLabel(label);
			stmt2.gen(label,a);
		}
	}
private:
	Stmt stmt1;
	Stmt stmt2;
};





















