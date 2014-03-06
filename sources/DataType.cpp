#include "DataType.h"


DataType* DataType::TypeINT  = new DataType("int", BASIC, 4);
DataType* DataType::TypeFLOAT = new DataType("float", BASIC, 4);
DataType* DataType::TypeCHAR = new DataType("char", BASIC, 1);
DataType* DataType::TypeBOOL = new DataType("bool", BASIC, 1);
DataType* DataType::TypeNULL = new DataType("null", TAG_NULL, 0);

DataType::DataType():Word("null", TAG_NULL),d_width(0)
{
}

DataType::DataType(std::string str, Tag t, int w): Word(str, t), d_width(w)
{
}

DataType::~DataType(void)
{
}

bool DataType::operator==(const DataType& rhs)
{
	return this->w_lexme.compare(rhs.w_lexme) == 0 && this->d_width == rhs.d_width;
}

std::ostream& operator<<(std::ostream& os, const DataType& type)
{
	os<<"Basic Type: "<<type.w_lexme<<std::endl;
	return os;
}

Array::Array(int sz, DataType* p):DataType("[]", INDEX, sz*p->d_width), a_size(sz), a_of(p)
{

}
Array::~Array(void)
{

}
std::string Array::toString() const
{
	std::stringstream result;
	result<<"["<<a_size<<"]"<<a_of->toString();
	return result.str();
}

bool numeric(DataType* p) 
{
	if (*p == *DataType::TypeINT || *p == *DataType::TypeFLOAT || *p == *DataType::TypeCHAR)
	{
		return true;
	} else {
		return false;
	}
}

DataType* max(DataType* p1, DataType* p2) 
{
	if (!numeric(p1) && !numeric(p2))
	{
		return DataType::TypeNULL;;
	}
	else if (*p1 == *DataType::TypeFLOAT || *p2 == *DataType::TypeFLOAT)
	{	
		return DataType::TypeFLOAT;
	}
	else if (*p1 == *DataType::TypeINT || *p2 == *DataType::TypeINT)
	{
		return DataType::TypeINT;
	} else {
		return DataType::TypeCHAR;
	}

}

DataType* check(DataType* p1, DataType* p2) {
	if (*p1 == *DataType::TypeBOOL && *p2 == *DataType::TypeBOOL)
	{
		return DataType::TypeBOOL;
	}
	else if (*p1 == *DataType::TypeINT && *p2 == *DataType::TypeINT)
	{
		return DataType::TypeBOOL;
	}
	else if (*p1 == *DataType::TypeFLOAT && *p2 == *DataType::TypeFLOAT)
	{
		return DataType::TypeBOOL;
	}
	else if (*p1 == *DataType::TypeCHAR && *p2 == *DataType::TypeCHAR)
	{
		return DataType::TypeBOOL;
	} else {
		return DataType::TypeNULL;
	}
}