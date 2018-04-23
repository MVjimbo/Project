#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <cstring>
#include <stdexcept>
using namespace std;

struct Expreccion
{
	Expreccion(string token) : token(token) {};
	Expreccion(string token, Expreccion a) : token(token), args{ a } {};
	Expreccion(string token, Expreccion a, Expreccion b) : token(token), args{ a,b } {};
	vector <Expreccion> args;
	string token;
};



class Parser
{
public:
	explicit Parser(const char* input) : input(input) {} // Конструктор, принимает строку с выражением
	Expreccion parse(); // Основная функция парсинга
private:
	std::string parse_token(); // Парсит один токен
	Expreccion parse_simple_expression(); // Парсит простое выражение
	Expreccion parse_binary_expression(int min_priority); // Парсит бинарное выражение

	const char* input; // Кусок строки, который еще не распарсили
};
