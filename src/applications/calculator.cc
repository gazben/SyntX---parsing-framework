#include <sstream>

#include <applications/calculator.h>

namespace applications {
	char const *calculator::evaluate::empty_stack::what() const throw() {
		return "The stack is empty.";
	}

	void calculator::evaluate::operator()(std::string const &) {
		int first, second, result = 0;

		if (numbers.empty()) throw empty_stack();
		second = numbers.top();
		numbers.pop();

		if (numbers.empty()) throw empty_stack();
		first = numbers.top();
		numbers.pop();

		char operation = operations.top();
		operations.pop();

		switch (operation) {
			case '+' :
				result = (first + second);
				break;

			case '-' :
				result = (first - second);
				break;

			case '*' :
				result = (first * second);
				break;

			case '/' :
				result = (first / second);
				break;
		}

		numbers.push(result);
	}

	calculator::calculator() {
		group	<<= 	-character("(")
				<< 		-sum
				<< 		-character(")");

		multiplicand	<<=	-integer()[(
								[this](std::string const &s) {
									std::stringstream stream(s);
									int num;
									stream >> num;
									numbers.push(num);
								}
							)] 
						|	group;

		product	<<=	-multiplicand
				<< 	*(
							-character("*/")[(
								[this](std::string const &s){operations.push(s[0]);}
							)]
						<<	-multiplicand[
								evaluate(numbers, operations)
							]
					);

		sum	<<=	-product
			<<	*(
						-character("+-")[(
							[this](std::string const &s){operations.push(s[0]);}
						)] 
					<<	-product[
							evaluate(numbers, operations)
						]
				);
	}
	
	bool calculator::calculate(std::string const &expression, int &result) {
		base_rule::match_range a_range;
		base_rule::match_range i(expression.begin(), expression.end());

		if (sum.match(i, a_range)) {
			result =  numbers.top();
			numbers.pop();

			return true;
		}
		else return false;
	}
}
