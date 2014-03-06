#include "Parser.h"


Parser::Parser(Lexer* l): p_lex(l), used(0), look(NULL), top(NULL)
{
	move();
}


Parser::~Parser(void)
{
}

void Parser::move()
{
	look = p_lex->scan();
}

void Parser::error(std::string msg)
{
	std::cerr<<"Near Line "<<p_lex->line<<": "<<msg<<std::endl;
}

void Parser::match(int t)
{
	if ((int)look->t_tag == t)
	{
		move();
	} else {
		error("Syntax Error");
	}
}

void Parser::program()
{
	Stmt* s = block();
	int begin = s->newLabel();
	int after = s->newLabel();
	s->emitLabel(begin);
	s->gen(begin,after);
	s->emitLabel(after);
}

Stmt* Parser::block()
{
	match('{');
	Env* savedEnv = top;
	top = new Env(top);
	decls();
	Stmt* s = stmts();
	match('}');
	top = savedEnv;

	return s;
}

void Parser::decls()
{
	while(look->t_tag == BASIC) {
		DataType* p = type();
		Word* tokWord = (Word *)look;
		match(ID);
		match(';');
		//Word *w = (Word *)&tok;
		Id id(tokWord, p, used);
		top->put(*tokWord, id);
		used = used + p->d_width;
	}
}

DataType* Parser::type()
{
	Word *lookAsWord = (Word*)look;
	int width = 0;
	if (lookAsWord->w_lexme.compare("char") == 0)
	{
		width = 1;
	} else if (lookAsWord->w_lexme.compare("bool") == 0)
	{
		width = 1;
	} else {
		width = 4;
	}
	DataType* p = new DataType(lookAsWord->w_lexme, lookAsWord->t_tag, width);
	match(BASIC);
	if (look->t_tag != '[')
	{
		return p;
	} else {
		return dims(p);
	}
}

DataType* Parser::dims(DataType* p)
{
	match('[');
	Num *tok = (Num *)look;
	match(NUM);
	match(']');
	if (look->t_tag == '[')
	{
		p = dims(p);
	}
	return new Array(tok->n_value, p);
}

Stmt* Parser::stmts()
{
	if (look->t_tag == '}')
	{
		return Stmt::StmtNULL;
	} else {
		Stmt *s = stmt();
		return new Seq(s, stmts());
	}
}

Stmt* Parser::stmt()
{
	if (look->t_tag == ';')
	{
		move();
		return Stmt::StmtNULL;
	} else if (look->t_tag == IF)
	{
		match(IF);
		match('(');
		Expr* x = boolExpr();
		match(')');
		Stmt* s1 = stmt();
		if (look->t_tag != ELSE)
		{
			return new If(x, s1);
		}
		match(ELSE);
		Stmt* s2 = stmt();
		return new Else(x, s1, s2);
	} else if (look->t_tag == WHILE)
	{
		While* whileNode = new While();;
		Stmt* savedStmt = Stmt::Enclosing;
		Stmt::Enclosing = whileNode;
		match(WHILE);
		match('(');
		Expr* x = boolExpr();
		match(')');
		Stmt* s = stmt();
		whileNode->init(x, s);
		Stmt::Enclosing = savedStmt;
		return whileNode;
	} else if (look->t_tag == DO)
	{
		Do* doNode = new Do();
		Stmt* savedStmt = Stmt::Enclosing;
		Stmt::Enclosing = doNode;
		match(DO);
		Stmt* s = stmt();
		match(WHILE);
		match('(');
		Expr* x = boolExpr();
		match(')');
		match(';');
		doNode->init(x, s);
		Stmt::Enclosing = savedStmt;
		return doNode;
	} else if (look->t_tag == BREAK)
	{
		match(BREAK);
		match(';');
		return new Break();
	} else if (look->t_tag == '{')
	{
		return block();
	} else {
		return assign();
	}

}

Stmt* Parser::assign()
{
	Stmt* s = NULL;
	Word* w = (Word*)look;
	Id* id = &top->get(*w);
	if (id == Id::IdNULL)
	{
		error(w->toString()+" Undeclared");
	}
	match(ID);
	if (look->t_tag == '=')
	{
		move();
		//	Error, id here is NULL, so id==Id::IdNULL is not working!!!
		s = new Set(id, boolExpr());
	} else {
		Access* x = offset(id);
		match('=');
		s = new SetElem(x, boolExpr());
	}
	match(';');
	return s;
}

Expr* Parser::boolExpr()
{
	Expr* x = join();
	while(look->t_tag == OR)
	{
		Token* tok = look;
		move();
		x = new Or(tok, x, join());
	}
	return x;
}

Expr* Parser::join()
{
	Expr* x = equality();
	while(look->t_tag == AND)
	{
		Token* tok = look;
		move();
		x = new And(tok, x, equality());
	}
	return x;
}

Expr* Parser::equality()
{
	Expr* x = rel();
	while(look->t_tag == EQ || look->t_tag == NE)
	{
		Token* tok = look;
		move();
		x= new Rel (tok, x, rel());
	}
	return x;
}

Expr* Parser::rel()
{
	Expr* x = expr();
	if (look->t_tag == '<' || look->t_tag == '>' || look->t_tag ==LE || look->t_tag == GE)
	{
		Token* tok = look;
		move();
		Expr *rhsExpr = expr();
		return new Rel(tok, x, rhsExpr);
	}
	return x;
}

Expr* Parser::expr()
{
	Expr* x = term();
	while(look->t_tag == '+' || look->t_tag == '-')
	{
		Token* tok = look;
		move();
		Arith* temp = new Arith(tok, x, expr());
		x = temp;
	}
	return x;
}

Expr* Parser::term()
{
	Expr* x = unary();
	while(look->t_tag == '*' || look->t_tag == '/')
	{
		Token* tok = look;
		move();
		x = new Arith(tok, x, unary());
	}
	return x;
}

Expr* Parser::unary()
{
	if (look->t_tag == '-')
	{
		move();
		return new Unary(Word::WordMINUS, unary());
	} else if (look->t_tag == '!')
	{
		Token* tok = look;
		move();
		return new Not(tok, unary());
	} else {
		return factor();
	}
}

Expr* Parser::factor()
{
	Expr *x = NULL;
	if (look->t_tag == '(')
	{
		move();
		x = boolExpr();
		match(')');
		return x;
	} else if (look->t_tag == NUM)
	{
		x = new Constant(look, DataType::TypeINT);
		move();
		return x;
	} else if (look->t_tag == REAL)
	{
		x = new Constant(look, DataType::TypeFLOAT);
		move();
		return x;
	} else if (look->t_tag == TRUE)
	{
		move();
		return Constant::ConstantTRUE;
	} else if(look->t_tag == FALSE)
	{
		move();
		return Constant::ConstantFALSE;
	} else if (look->t_tag == ID)
	{
		std::string s = look->toString();
		Word *w = (Word*)look;
		Id* id = &top->get(*w);
		if (id == Id::IdNULL)
		{
			error(look->toString() + "Undeclared");
		}
		move();
		if (look->t_tag != '[')
		{
			return id;
		} else {
			return offset(id);
		}
	} else {
		error("Syntax Error");
		return Expr::ExprNULL;
	}
}

Access* Parser::offset(Id* a)
{
	Array* type = (Array *)a->type;
	match('[');
	Expr* index = boolExpr();
	DataType* ofType = type->a_of;
	Expr* w = new Constant(ofType->d_width);
	Expr* t1 = new Arith(new Token('*'), index, w);
	Expr* loc = t1;
	Expr* t2 = NULL;

	match(']');

	while(look->t_tag == '[')
	{
		match('[');
		index = boolExpr();
		w = new Constant(ofType->d_width);
		t1 = new Arith(new Token('*'), index, w);
		t2 = new Arith(new Token('+'), loc, t1);
		loc = t2;
	}
	return new Access(a, loc, ofType);
}






































































