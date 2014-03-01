#include "Env.h"


Env::Env(void):prev(NULL)
{
}

Env::Env(Env* p):prev(p)
{

}

void Env::put(Word w, Id i)
{
	table[w] = i;
}

Id Env::get(Word w)
{
	for (Env* e = this; e != NULL; e = e->prev)
	{
		std::map<Word,Id>::iterator found = e->table.find(w);
		if (found != e->table.end())
		{
			return found->second;
		}
	}
	return *Id::IdNULL;
}

Env::~Env(void)
{
}
