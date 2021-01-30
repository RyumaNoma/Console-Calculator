#include "Calc.hpp"

bool Calc::is_same(const std::string a, const std::string b)
{
	if (a.size() != b.size()) return false;
	
	int N = a.size();
	for (int i = 0; i < N; i++)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	
	return true;
}

int Calc::pow(int a, int b)
{
	int out = 1;
	for (int i = 0; i < b; i++)
	{
		out *= a;
	}
	
	return out;
}