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
	void emit(std::String str) {
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

class Constant: public Expr
{
public:
	Constant(Token tok, Type p): Expr(tok,p) {};
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

	
};

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

	Type check(Type p1, Type p2) {
		if (p1.type == TypeBOOL && p2.type == TypeBOOL)
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