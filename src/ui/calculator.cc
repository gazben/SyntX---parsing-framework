#include <string>
#include <iostream>

#include <applications/calculator.h>

int main() {
	int result;
	std::string expression;
	applications::calculator the_calculator;

	while (std::getline(std::cin, expression)) {
		if (the_calculator.calculate(expression, result)) {
			std::cout << result << std::endl;
		}
	}

	return 0;
}
