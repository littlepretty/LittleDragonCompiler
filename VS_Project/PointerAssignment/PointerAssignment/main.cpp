#include <iostream>

int main()
{
	int x = 10;
	int y = 100;
	int *p = &x;
	int *t = p;
	p = &y;
	std::cout << *p << std::endl;
	std::cout << *t << std::endl;

	return 0;
}