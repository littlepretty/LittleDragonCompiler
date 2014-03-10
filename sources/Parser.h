#pragma once
#include "Lexer.h"
#include "Token.h"
#include "Stmt.h"
#include "DataType.h"
#include "Env.h"
#include "Logical.h"
#include <string>

class Parser
{
public:
	Parser(Lexer* l);
	virtual ~Parser(void);

	void error(std::string msg);
	void match(int t);
	void program();

private:
	void move();

	Stmt* block();

	void decls();

	DataType* type();
	DataType* dims(DataType* p);

	Stmt* stmts();
	Stmt* stmt();

	Stmt* assign();
	Expr* boolExpr();
	Expr* join();
	Expr* equality();
	Expr* rel();
	Expr* expr();
	Expr* term();
	Expr* unary();
	Expr* factor();
	Access* offset(Id* a);
	
	Lexer* p_lex;
	Token* look;
	Env* top;
	int used;
};

