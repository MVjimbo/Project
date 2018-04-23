#include "Parcer.h"

int getpriority(const string & token)
{
	if (token == "-") return 1;
	if (token == "+") return 1;
	if (token == "*") return 2;
	if (token == "/") return 2;
	if (token == "mod") return 3;
	if (token == "**") return 3;
	return 0;
}


Expreccion Parser::parse()
{
	return parse_binary_expression(0);
}

string Parser::parse_token()
{
	while ((*input == ' ') || (*input == '\n')) input++;
	if ((*input >= 48) && (*input <= 57))
	{
		string number;
		while ((*input >= 48) && (*input <= 57))
		{
			number += *input;
			input++;
		}
		return number;
	}
	string mas[] = { "+", "-", "**", "*", "/", "mod", "abs", "sin", "cos", "(", ")" };
	string t;
	for (int i = 0; i < 11; i++)
	{
		t = mas[i];
		if (strncmp(input, t.c_str(), t.size())==0)
		{
			input += t.length();
			return t;
		}
	}
	return "";
}


Expreccion Parser::parse_simple_expression()
{
	auto token = parse_token();
	if (token.empty())
		throw std::runtime_error("Invalid input");
	if (token[0] >= 48 && token[0] <= 57)
		return token;
	if (token == "(")
	{
		auto result = parse();
		if (parse_token() != ")")
			throw std::runtime_error("No )");
		return result;
	}
	auto result = parse_simple_expression();
	return Expreccion(token, result);
}

Expreccion Parser::parse_binary_expression(int min_priority)
{
	auto left_expr = parse_simple_expression();
	for (;;)
	{
		auto token = parse_token();
		auto priority = getpriority(token);
		if (priority <= min_priority)
		{
			input -= token.size();
			return left_expr;
		}
		auto right_expr = parse_binary_expression(priority);
		left_expr = Expreccion(token, left_expr, right_expr);	
	}
}

