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

Id Env::get(const Word* w)
{
	for (Env* e = this; e != NULL; e = e->prev)
	{
		std::map<Word,Id>::iterator found = e->table.find(*w);
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

std::ostream& operator<<(std::ostream& os, const Env& env)
{
	os << "\n\n/*** Begin Environment ***/\n\n";
	for (const Env* e = &env; e != NULL; e = e->prev)
	{
		std::map<Word, Id> tab = e->table;
		for (std::map<Word, Id>::iterator iter = tab.begin(); iter != tab.end(); iter++)
		{
			os<<iter->first<<iter->second<<"\n\n";
		}
	}
	os << "/*** End Environment ***/\n\n";
	return os;
}