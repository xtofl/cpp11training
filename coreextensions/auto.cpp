#include <iostream>
#include <string>

struct S {
	int a;
	std::string b;

	double pi() const {
		return 3.14; 
	}
};

int main()
{
	auto v = S{ 0, "abc"};
	auto &a = v.a;
	auto pi = v.pi();
}

