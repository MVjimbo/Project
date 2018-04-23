#include "Parcer.h"
#include <iostream>
#include <fstream>


double count(const Expreccion & e)
{
	switch (e.args.size())
	{
	case (2):
	{
		auto a = count(e.args[0]);
		auto b = count(e.args[1]);
		if (e.token == "+") return a + b;
		if (e.token == "-") return a - b;
		if (e.token == "*") return a * b;
		if (e.token == "/") return (int)a + (int)b;
		if (e.token == "**") return pow(a, b);
		if (e.token == "mod") return (int)a % (int)b;
		break;
	}
	case (1):
	{
		auto a = count(e.args[0]);
		if (e.token == "+") return a;
		if (e.token == "-") return -a ;
		if (e.token == "sin") return sin(a);
		if (e.token == "cos") return cos(a);
		if (e.token == "abs") return abs(a);
		break;
	}
	case (0):
	{
		return stoi(e.token);

	}
	}
	throw runtime_error("No");
}

using namespace std;

int main()
{
	ifstream fin;
	fin.open("text1.txt");
	int i = 0;
	char b;
	while (fin.get(b))
	{
		i++;
	}
	fin.close();
	fin.clear();
	fin.open("text1.txt");
	char *c = new char[i + 1];
	c[i]='\0';
	int j = 0;
	while (fin.get(b))
	{
		c[j++] = b;
	}

	Parser par(c);
	cout<<count(par.parse());
	system("pause");
	return 0;
}