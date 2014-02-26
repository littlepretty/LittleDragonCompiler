#pragma once
#include <iostream>
#include <sstream>
#include "Word.h"

class DataType : public Word
{
public:
	DataType(std::string str, Tag t, int w);
	virtual ~DataType(void);

	
	const static DataType TypeINT;
	const static DataType TypeFLOAT;
	const static DataType TypeCHAR;
	const static DataType TypeBOOL;
	const static DataType TypeNULL;
	int d_width;
};

class Array: public DataType
{
public:
	Array(int sz, DataType p);
	~Array(void);
	virtual std::string toString();

private:
	int a_size;
	DataType a_of;
};

bool numeric(DataType p);
DataType max(DataType p1, DataType p2);
DataType check(DataType p1, DataType p2);

