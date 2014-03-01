#include "Op.h"

Op::Op(Token* tok, DataType* p):Expr(tok, p) 
{
}

Op::~Op(void)
{
}

Expr* Op::reduce() 
{
	Expr* x = gen();
	Temp* temp = new Temp(type);
	std::stringstream result;
	result<<temp->toString()<<" = "<<x->toString();
	emit(result.str());
	return temp;
}

Arith::Arith(Token* tok, Expr* e1, Expr* e2):Op(tok, max(exp1->type, exp2->type)), exp1(e1), exp2(e2) 
{
	if (type == DataType::TypeNULL)
	{
		error("Type Error");
	}
};

Arith::~Arith()
{

}

Expr* Arith::gen()
{
	return new Arith(op, exp1->reduce(), exp2->reduce());
}

std::string Arith::toString() {
	return exp1->toString() + " " + op->toString() + " " + exp2->toString();
}


Unary::Unary(Token* tok, Expr* e):Op(tok, max(DataType::TypeINT, e->type)), exp(e)
{
	if (type == DataType::TypeNULL)
	{
		error("Type Error");
	}
};

Unary::~Unary()
{

}

Expr* Unary::gen() 
{
	return new Unary(op, exp->reduce());
}

std::string Unary::toString() {
	return op->toString() + " " + exp->toString();
}


Access::Access(Id* a, Expr* i, DataType* p): Op(new Word("[]",INDEX),p), array(a), index(i) 
{

}

Access::~Access()
{

}

Expr* Access::gen() {
	return new Access(array, index->reduce(), type);
}

void Access::jumping(int t, int f) {
	emitJumps(reduce()->toString(),t,f);
}

std::string Access::toString() {
	return array->toString() + " [ " + index->toString() + " ] ";
}