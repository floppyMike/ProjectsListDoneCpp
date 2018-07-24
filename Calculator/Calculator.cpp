// Calculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <cmath>
#include <array>

//From "CustomLibrary"
#include <Input.h>
#include <Error.h>

static const std::array<std::string, 11> exList = { "+", "-", "*", "/", "sin", "cos", "tan", "log", "fact", "pow", "root" };

bool checkOperator(const std::string &ex);
void listCommands();

int main()
{
	std::cout << "Welcome to the simple scientific calculator!\nType one number or operator per line. (supports 1 operation)\n" << std::endl;
	
	const double x = getConsoleInput<double>();

	std::string _operator_;
	do
	{
		std::getline(std::cin, _operator_);
		if (_operator_ == "help")
			listCommands();
	}
	while (!checkOperator(_operator_));
	
	try
	{
		if (_operator_ == "sin")
			std::cout << std::sin(x) << std::endl;

		else if (_operator_ == "cos")
			std::cout << std::cos(x) << std::endl;

		else if (_operator_ == "tan")
			std::cout << std::tan(x) << std::endl;

		else if (_operator_ == "log")
		{
			if (x <= 0.0)
				throw Error("Null and negative numbers aren't allowed!");
			std::cout << std::log(x) << std::endl;
		}

		else if (_operator_ == "fact")
		{
			if (std::round(x) != x)
				throw Error("Number has a decimal point!");
			std::cout << [x]() mutable { double y = x;  for (short i = 1; i < x; i++) y *= i; return y; }() << std::endl;
		}

		else if (_operator_ == "pow")
			std::cout << std::pow(x, getConsoleInput<double>()) << std::endl;

		else if (_operator_ == "root")
			std::cout << std::pow(x, 1 / getConsoleInput<double>()) << std::endl;

		else if (_operator_ == "+")
			std::cout << x + getConsoleInput<double>() << std::endl;

		else if (_operator_ == "-")
			std::cout << x - getConsoleInput<double>() << std::endl;

		else if (_operator_ == "*")
			std::cout << x * getConsoleInput<double>() << std::endl;

		else if (_operator_ == "/")
			std::cout << x / getConsoleInput<double>() << std::endl;

	}
	catch (const Error &msg)
	{
		std::cerr << msg.what() << std::endl;
	}


	getchar();
    return 0;
}

bool checkOperator(const std::string &ex)
{
	for (const auto &val : exList)
		if (ex == val)
			return true;
	return false;
}

void listCommands()
{
	for (const auto &val : exList)
		std::cout << "\"" << val << "\"\n";
	std::cout << std::flush;
}