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

#include <tuple>
#include <string>
#include <iostream>

#include <util/parser/parser.h>

using namespace util::parser;

void simple_test() {
	rule addition, addend, expression;

	addition <<= -addend << +(-character("+") << -addend);
	addend <<= -range('0', '9') | -expression;
	expression <<= -character("(") << -addition << -character(")");

	std::string input = "2+(3-4)";
	base_rule::match_range context(input.cbegin(), input.cend());
	base_rule::match_range result;

	if (addition.match(context, result))
		std::cout << "Matched: " << std::string(result.first, result.second) << std::endl;
	else {
		std::cout << base_rule::get_error_message(base_rule::match_range(input.cbegin(), input.cend())) << std::endl;
	}
}

void complex_test() {
	rule program;
	rule for_loop;
	rule range_for("range_for");
	rule iterator_for("iterator_for");
	rule declaration;
	rule logic_expression;
	rule expression;
	rule sentence;
	rule block;

	program		<<=	-+for_loop
				<<	-epsilon();

	for_loop	<<=	(
							-range_for
						|	-iterator_for
					)
				<<	-block;

	range_for	<<=	-keyword("for")
				<<	-substring("(")
				<<	-declaration
				<<	-substring(":")
				<<	-identifier()
				<<	-substring(")");

	iterator_for	<<=	-keyword("for")
					<<	-substring("(")
					<<	-declaration
					<<	-substring(";")
					<<	-logic_expression
					<<	-substring(";")
					<<	-expression
					<<	-substring(")");

	declaration		<<=	-(keyword("int") | keyword("char") | keyword("unsigned") | keyword("auto"))
					<<	-!(
								substring("&")
							|	substring("*")
						  )
					<<	-identifier()
					<<	!(
								-substring("=")
							<<	-integer()
						 );

	logic_expression	<<=	-identifier()
						<<	-(substring("==") | substring("<") | substring(">") | substring("<=") | substring(">="))
						<<	-integer();

	expression	<<=	-!substring("++")
				<<	identifier()
				<<	!substring("++");

	sentence	<<=	-expression
				<<	-substring(";");

	block		<<=	-substring("{")
				<<	+(
							-sentence 
						|	-for_loop
					 )
				<<	-substring("}");
	
	std::string input = R"(
		for (int i = 0; i < 10; ++i) {
			++apple;
			lemon++;
		}

		for (auto &element: container) {
			element++;
		}

		for (int i = 5; i > 15; ++i) {
			+apple;
			for (auto e: container) {
				++lemon;
			}
		}
	)";

	base_rule::match_range context(input.cbegin(), input.cend());
	base_rule::match_range result;

	if (program.match(context, result) && context.first == context.second) {
		std::cout << "Matched: " << std::string(result.first, result.second) << std::endl;
	}
	else {
		std::cout << base_rule::get_error_message(base_rule::match_range(input.cbegin(), input.cend())) << std::endl;
		std::cout << std::endl << "The failure_log:" << std::endl;
		auto failure_log = base_rule::get_failure_log();
		for (auto const &entry: failure_log) {
			std::cout << (std::get<0>(entry) - input.cbegin()) << ": " << std::get<1>(entry) << std::endl;
		}
	}
}

int main() {
	void (*tests[])() = {simple_test, complex_test};

	for (auto test: tests) {
		test();
		base_rule::clear_failure_log();
	}
}
