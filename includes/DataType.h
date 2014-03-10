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

	bool operator==(const DataType& rhs) const;

	friend std::ostream& operator<<(std::ostream& os, const DataType& type);

	static DataType* TypeINT;
	static DataType* TypeFLOAT;
	static DataType* TypeCHAR;
	static DataType* TypeBOOL;
	static DataType* TypeNULL;

	bool numeric() const;

	int d_width;
};

DataType* max(DataType* p1, DataType* p2);
DataType* check(DataType* p1, DataType* p2);

class Array: public DataType
{
public:
	Array(int sz, DataType* p);
	~Array(void);
	virtual std::string toString() const;

	int a_size;
	DataType* a_of;
};



