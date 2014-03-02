#pragma once
#include <map>
#include "Word.h"
#include "Expr.h"

class Env
{
public:
	Env(void);
	Env(Env* p);

	virtual ~Env(void);

	void put(Word w, Id i);
	Id get(Word w);
	friend std::ostream& operator<<(std::ostream& os, const Env& env);
private:
	Env *prev;
	std::map<Word, Id> table;
};

