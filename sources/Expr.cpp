#include "Expr.h"

Expr* Expr::ExprNULL = new Expr(); 

Expr::Expr()
{

}

Expr::Expr(Token* tok, DataType* p):op(tok), type(p) 
{

}


Expr::~Expr(void)
{
}

bool Expr::operator==(const Expr& rhs)
{
	return this->op == rhs.op && this->type == rhs.type;
}


Expr* Expr:: gen()
{
	return this;
}
Expr* Expr::reduce() 
{
	return this;
}
void Expr::jumping(int t, int f) 
{
	emitJumps(toString(), t, f);
}
void Expr::emitJumps(std::string test, int t, int f) 
{
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

std::string Expr::toString() {
	return op->toString();
}

Id* Id::IdNULL = new Id();

Id::Id()
{

}

Id::Id(Token* id, DataType* p, int b):Expr(id, p), offset(b) 
{
}

Id::~Id(void)
{

}

int Temp::count = 0;

Temp::Temp(DataType* p): Expr(Word::WordTEMP, p) {
	number = ++count;
};
Temp::~Temp()
{

}
std::string Temp::toString() {
	std::stringstream result;
	result<<"t"<<number;
	return result.str();
}

Constant* Constant::ConstantTRUE = new Constant(Word::WordTRUE, DataType::TypeBOOL);
Constant* Constant::ConstantFALSE = new Constant(Word::WordFALSE, DataType::TypeBOOL);

Constant::Constant(Token* tok, DataType* p): Expr(tok,p) {};
Constant::Constant(int i): Expr(new Num(i), DataType::TypeINT) {};

Constant::~Constant()
{

}

void Constant::jumping(int t, int f) {
	if (this == Constant::ConstantTRUE && t != 0)
	{
		std::stringstream result;
		result<<"goto L"<<t;
		emit(result.str());
	} else if (this == ConstantFALSE && f != 0)
	{
		std::stringstream result;
		result<<"goto L"<<f;
		emit(result.str());
	}
}