#pragma once
#include <string>
#include <iostream>

class Node
{
public:
	Node(void);
	virtual ~Node(void);
	void error(std::string str);
	int newLabel();
	void emitLabel(int i);
	void emit(std::string str);

	int lexerLine;
	static int label;
};

