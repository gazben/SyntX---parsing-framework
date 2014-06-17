/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2013, Gergely Nagy
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <sstream>

#include <applications/calculator.h>

namespace applications {
	char const *calculator::evaluate::empty_stack::what() const noexcept {
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
