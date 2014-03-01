#pragma once
#include <iostream>
#include <sstream>
#include "Word.h"

class DataType : public Word
{
public:
	DataType();
	DataType(std::string str, Tag t, int w);
	virtual ~DataType(void);


	static DataType* TypeINT;
	static DataType* TypeFLOAT;
	static DataType* TypeCHAR;
	static DataType* TypeBOOL;
	static DataType* TypeNULL;

	int d_width;
};

class Array: public DataType
{
public:
	Array(int sz, DataType* p);
	~Array(void);
	virtual std::string toString();

	int a_size;
	DataType* a_of;
};

bool numeric(DataType* p);
DataType* max(DataType* p1, DataType* p2);
DataType* check(DataType* p1, DataType* p2);

