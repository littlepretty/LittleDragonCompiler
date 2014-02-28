#include "Parser.h"


Parser::Parser(Lexer l): p_lex(l), used(0), look(NULL)
{
	move();
}


Parser::~Parser(void)
{
}

void Parser::move()
{
	look = p_lex.scan();
}

void Parser::error(std::string msg)
{
	std::cerr<<"Near Line "<<p_lex.line<<": "<<msg<<std::endl;
}

void Parser::match(int t)
{
	if ((int)look.t_tag == t)
	{
		move();
	} else {
		error("Syntax Error");
	}
}

void Parser::program()
{
	Stmt s = block();
	int begin = s.newLabel();
	int after = s.newLabel();
	s.emitLabel(begin);
	s.gen(begin,after);
	s.emitLabel(after);
}

Stmt Parser::block()
{
	match('{');
	decls();
	Stmt s = stmts();
	match('}');
	return s;
}

void Parser::decls()
{
	while(look.t_tag == BASIC) {
		DataType p = type();
		Token tok = look;
		match(ID);
		match(';');
		Id id(tok, p, used);
		used = used + p.d_width;
	}
}

DataType Parser::type()
{
	DataType* p = dynamic_cast<DataType*>(&look);
	match(BASIC);
	if (look.t_tag != '[')
	{
		return *p;
	} else {
		return dims(*p);
	}
}

DataType Parser::dims(DataType p)
{
	match('[');
	Num *tok = dynamic_cast<Num*>(&look);
	match(NUM);
	match(']');
	if (look.t_tag == '[')
	{
		p = dims(p);
	}
	return Array(tok->n_value, p);
}

Stmt Parser::stmts()
{
	if (look.t_tag == '}')
	{
		return Stmt::StmtNULL;
	} else {
		return Seq(stmt(), stmts());
	}
}

Stmt Parser::stmt()
{
	if (look.t_tag == ';')
	{
		move();
		return Stmt::StmtNULL;
	} else if (look.t_tag == IF)
	{
		match(IF);
		match('(');
		Expr x = boolExpr();
		match(')');
		Stmt s1 = stmt();
		if (look.t_tag != ELSE)
		{
			return If(x, s1);
		}
		match(ELSE);
		Stmt s2 = stmt();
		return Else(x, s1, s2);
	} else if (look.t_tag == WHILE)
	{
		Stmt savedStmt = Stmt::Enclosing;
		match(WHILE);
		match('(');
		Expr x = boolExpr();
		match(')');
		Stmt s1 = stmt();
		While w(x, s1);
		Stmt::Enclosing = savedStmt;
		return w;
	} else if (look.t_tag == DO)
	{
		Stmt savedStmt = Stmt::Enclosing;

	}

}

Stmt Parser::assign()
{

}










































































