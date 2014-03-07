#include "Stmt.h"

Stmt* Stmt::StmtNULL = new Stmt();
Stmt* Stmt::Enclosing = Stmt::StmtNULL;

Stmt::Stmt(void)
{
}

Stmt::~Stmt(void)
{
}

bool Stmt::operator==(const Stmt& rhs)
{
	return this->after == rhs.after && this->lexerLine == rhs.after;
}

void Stmt::gen(int b, int a)
{

}

If::If(Expr* e, Stmt* s):test(e), stmt(s) 
{
	//test = new Expr(*e);
	//stmt = new Stmt(*s);

	if (test->type == DataType::TypeBOOL)
	{
	} else {
		test->error("Require BOOL in If Stmt");
	}
}

If::~If()
{

}

void If::gen(int b, int a) {
	int label = newLabel();
	test->jumping(0,a);
	emitLabel(label);
	stmt->gen(label,a);
}

Else::Else(Expr* e, Stmt* s1, Stmt* s2) :test(e), stmt1(s1), stmt2(s2)
{
	//test = new Expr(*e);
	//stmt1 = new Stmt(*s1);
	//stmt2 = new Stmt(*s2);

	if (test->type == DataType::TypeBOOL)
	{
		
	} else {
		test->error("Require BOOL in If Stmt");
	}
}

Else::~Else()
{

}

void Else::gen(int b, int a){
	int label1 = newLabel();
	int label2 = newLabel();
	test->jumping(0,label2);

	emitLabel(label1);
	stmt1->gen(label1, a);
	std::stringstream gt;
	gt<<"goto L"<<a;
	emit(gt.str());

	emitLabel(label2);
	stmt2->gen(label2,a);
}

While::While() 
{
	test = Expr::ExprNULL;
	stmt = Stmt::StmtNULL;
}

void While::init(Expr* e, Stmt* s)
{
	test = e;
	stmt = s;
	if (test->type == DataType::TypeBOOL)
	{

	} else {
		test->error("Require BOOL in While Stmt");
	}
}

While::~While()
{

}

void While::gen(int b, int a)
{
	after = a;
	test->jumping(0,a);
	int label = newLabel();
	emitLabel(label);
	stmt->gen(label,b);

	std::stringstream gt;
	gt<<"goto L"<<b;
	emit(gt.str());
}

Do::Do()
{
}

void Do::init(Expr* e, Stmt* s)
{
	test = e;
	stmt = s;
	if (test->type == DataType::TypeBOOL)
	{

	} else {
		test->error("Require BOOL in Do-While Stmt");
	}
}

Do::~Do()
{

}

void Do::gen(int b, int a) {
	after = a;
	int label = newLabel();
	stmt->gen(b,label);
	emitLabel(label);
	test->jumping(b,0);
}

Set::Set(Id* i, Expr* e):id(i), exp(e) 
{
	//exp = new Expr(*e);
	if (*check(id->type, exp->type) == *DataType::TypeNULL)
	{
		error("Type Error");
	}
}

Set::~Set()
{

}
void Set::gen(int b, int a) 
{
	emit(id->toString() + " = " + exp->gen()->toString());
}


SetElem::SetElem(Access* x, Expr* e): array(x->array), index(x->index), exp(e) 
{
	/*
	index = new Expr(*(x->index));
	exp = new Expr(*e);
	*/
	if (*check(x->type, exp->type) == *DataType::TypeNULL)
	{
		error("Type Error");
	}
}

SetElem::~SetElem()
{

}
void SetElem::gen(int b, int a) 
{
	std::string s1 = index->reduce()->toString();
	std::string s2 = exp->reduce()->toString();
	emit(array->toString() + " [ " + s1 + "] = " + s2);
}


Break::Break() 
{
	if (Stmt::StmtNULL == Stmt::Enclosing)
	{
		error("Unenclosed Break");
	}
	stmt = Enclosing;
}
Break::~Break()
{
}
void Break::gen(int b, int a) 
{
	std::stringstream gt;
	gt<<"goto L"<<after;
	emit(gt.str());
}

Seq::Seq(Stmt* s1, Stmt* s2) :stmt1(s1), stmt2(s2)
{
}

Seq::~Seq()
{

}

void Seq::gen(int b, int a) {
	if (stmt1 == Stmt::StmtNULL)
	{
		stmt2->gen(b, a);
	} else if (stmt2 == Stmt::StmtNULL)
	{
		stmt1->gen(b, a);
	} else {
		int label = newLabel();
		stmt1->gen(b, label);
		emitLabel(label);
		stmt2->gen(label,a);
	}
}


