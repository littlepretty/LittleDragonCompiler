#include "Logical.h"


Logical::Logical(Token tok, Expr e1, Expr e2): Expr(tok, check(exp1.type, exp2.type)), exp1(e1), exp2(e2) {
	if (type == DataType::TypeNULL)
	{
		error("Type Error");
	}
};

Logical::~Logical(void)
{
}

Expr Logical::gen(){
	int f = newLabel();
	int a = newLabel();
	Temp temp(type);
	this->jumping(0, f);
	emit(temp.toString() + " = true");
	std::stringstream result;
	result<<"goto L"<<a;
	emit(result.str());
	emitLabel(f);
	emit(temp.toString() + " = false");
	emitLabel(a);
	return temp;
}

std::string Logical::toString() {
	return exp1.toString() + " " + op.toString() + " " + exp2.toString();
}

Or::Or(Token tok, Expr e1, Expr e2):Logical(tok,e1,e2) {}
Or::~Or(){}

void Or::jumping(int t, int f) {
	int label = t != 0 ? t : newLabel();
	exp1.jumping(label,0);
	exp2.jumping(t,f);
	if (t == 0)
	{
		emitLabel(label);
	}
}

And::And(Token tok, Expr e1, Expr e2):Logical(tok,e1,e2) 
{

}
And::~And()
{

}

void And::jumping(int t, int f) {
	int label = f !=0 ? f : newLabel();
	exp1.jumping(0, label);
	exp2.jumping(t,f);
	if (f == 0)
	{
		emitLabel(label);
	}
}

Not::Not(Token tok, Expr e):Logical(tok,e,e) 
{

}
Not::~Not()
{

}

void Not::jumping(int t, int f) {
	jumping(f,t);
}
std::string Not::toString() {
	return op.toString() + " " + exp2.toString();
}

Rel::Rel(Token tok, Expr e1, Expr e2):Logical(tok,e1,e2) 
{

}

Rel::~Rel()
{

}

void Rel::jumping(int t, int f) {
	Expr a = exp1.reduce();
	Expr b = exp2.reduce();
	std::string test = a.toString() + " " + op.toString() + " " + b.toString();
	emitJumps(test, t, f);
}

































