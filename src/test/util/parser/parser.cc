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

#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>

#include <util/parser/parser.h>
#include <util/tester/tester.h>

using namespace util::parser;

bool test_0() {
	rule sentence;
	std::string contents;
	
	if (!base_rule::file_to_string("test_data/test1.tt", contents)) return false;

	sentence <<= character("ab") << character("b") << character("cde");

	base_rule::match_range i(contents.begin(), contents.end());
	base_rule::match_range a_range;
	if (sentence.match(i, a_range)) {
		std::string s(a_range.first, a_range.second);
		std::cout << "Match: " << s << std::endl;
		return true;
	}
	else {
		std::cout << "Did not match" << std::endl;
		return false;
	}
}

bool test_1() {
	rule sentence, letters;
	std::string contents;
	
	if (!base_rule::file_to_string("test_data/test1.tt", contents)) return false;

	sentence <<=  letters << character("cde");
	letters <<= character("ab") << character("b");

	base_rule::match_range i(contents.begin(), contents.end());
	base_rule::match_range a_range;
	if (sentence.match(i, a_range)) {
		std::string s(a_range.first, a_range.second);
		std::cout << "Match: " << s << std::endl;
		return true;
	}
	else {
		std::cout << "Did not match" << std::endl;
		return false;
	}
}

bool test_2() {
	rule sentence, letters;
	std::string contents, sentence_match;
	
	if (!base_rule::file_to_string("test_data/test1.tt", contents)) return false;

	sentence <<=  (
					letters[ ([](std::string const &s) {std::cout << s << std::endl;}) ] << 
					character("cde")[ ([](std::string const &s){std::cout << s << std::endl;}) ]
				)
				[ ([&sentence_match](std::string const &s){std::cout << "Full match: " << (sentence_match = s) << std::endl;}) ];

	letters <<= character("ab") << character("b")[debug_action("Debug: \"", "\"\n")];

	base_rule::match_range i(contents.begin(), contents.end());
	base_rule::match_range a_range;
	if (sentence.match(i, a_range)) {
		std::string s(a_range.first, a_range.second);
		std::cout << "Match: " << s << std::endl;
		std::cout << "Matched string: " << sentence_match << std::endl;
		return true;
	}
	else {
		std::cout << "Did not match" << std::endl;
		return false;
	}
}

bool test_3() {
	rule sentence;
	std::string contents;

	if (!base_rule::file_to_string("test_data/test1.tt", contents)) return false;

	sentence <<= range('a', 'z') << range('b', 'c') << range('c', 'g');

	base_rule::match_range a_range;
	base_rule::match_range i(contents.begin(), contents.end());

	if (sentence.match(i, a_range)) {
		std::cout << "Match: " << std::string(a_range.first, a_range.second) << std::endl;
		return true;
	}
	else return false;
}

bool test_4() {
	rule sentence, auxiliary;
	std::string contents;

	if (!base_rule::file_to_string("test_data/test1.tt", contents)) return false;

	sentence <<= range('a', 'z') << auxiliary << range('c', 'g');
	auxiliary <<= range('f', 'g') | range('0', '1') | range('a', 'e') | character("23456789");

	base_rule::match_range a_range;
	base_rule::match_range i(contents.begin(), contents.end());

	if (sentence.match(i, a_range)) {
		std::cout << "Match: " << std::string(a_range.first, a_range.second) << std::endl;
		return true;
	}
	else return false;
}

bool test_5() {
	rule sentence, auxiliary;
	std::string contents;

	if (!base_rule::file_to_string("test_data/test1.tt", contents)) return false;

	sentence <<= !range('p', 'z') << !range('a', 'z') << auxiliary << range('c', 'g');
	auxiliary <<= range('f', 'g') | range('0', '1') | range('a', 'e') | character("23456789");

	base_rule::match_range a_range;
	base_rule::match_range i(contents.begin(), contents.end());

	if (sentence.match(i, a_range)) {
		std::cout << "Match: " << std::string(a_range.first, a_range.second) << std::endl;
		return true;
	}
	else return false;
}

bool test_6() {
	rule sentence;
	std::string contents;

	if (!base_rule::file_to_string("test_data/test1.tt", contents)) return false;

	sentence <<= +character("cba");

	base_rule::match_range a_range;
	base_rule::match_range i(contents.begin(), contents.end());

	if (sentence.match(i, a_range)) {
		std::cout << "Match: " << std::string(a_range.first, a_range.second) << std::endl;
		return true;
	}
	else return false;
}

bool test_7() {
	rule sentence;
	std::string contents;

	if (!base_rule::file_to_string("test_data/test1.tt", contents)) return false;

	sentence <<= *range('p', 'q') << *character("cba");

	base_rule::match_range a_range;
	base_rule::match_range i(contents.begin(), contents.end());

	if (sentence.match(i, a_range)) {
		std::cout << "Match: " << std::string(a_range.first, a_range.second) << std::endl;
		return true;
	}
	else return false;
}

bool test_8() {
	rule sentence;
	std::string contents;

	if (!base_rule::file_to_string("test_data/test1.tt", contents)) return false;

	sentence <<= -*range('p', 'q') << *-character("cba");

	base_rule::match_range a_range;
	base_rule::match_range i(contents.begin(), contents.end());

	if (sentence.match(i, a_range)) {
		std::cout << "Match: " << std::string(a_range.first, a_range.second) << std::endl;
		return true;
	}
	else return false;
}

bool test_9() {
	rule sentence;
	std::string contents;

	if (!base_rule::file_to_string("test_data/test2.tt", contents)) return false;

	std::cout << contents << std::endl;

	sentence <<= -*range('p', 'q') << *-character("cba");

	base_rule::match_range a_range;
	base_rule::match_range i(contents.begin(), contents.end());

	if (sentence.match(i, a_range)) {
		std::cout << "Match: " << std::string(a_range.first, a_range.second) << std::endl;
		return true;
	}
	else return false;
}

bool test_10() {
	rule sentence;
	std::string contents;

	if (!base_rule::file_to_string("test_data/test2.tt", contents)) return false;

	std::cout << contents << std::endl;

	sentence <<= -*range('p', 'q') << -*character("cba");

	base_rule::match_range a_range;
	base_rule::match_range i(contents.begin(), contents.end());

	if (sentence.match(i, a_range)) {
		std::cout << "Match: " << std::string(a_range.first, a_range.second) << std::endl;
		return true;
	}
	else return false;
}

bool test_11() {
	rule numbers;
	std::string contents;

	if (!base_rule::file_to_string("test_data/test3.tt", contents)) return false;

					//letters[ ([](std::string const &s) {std::cout << s << std::endl;}) ] << 
	numbers <<= *-integer()[
								([](std::string const &s){std::cout << s << std::endl;})
							];

	base_rule::match_range a_range;
	base_rule::match_range i(contents.begin(), contents.end());

	if (numbers.match(i, a_range)) {
		std::cout << "Match: " << std::string(a_range.first, a_range.second) << std::endl;
		return true;
	}
	else return false;
}

struct evaluate {
	std::stack<std::string> &numbers;
	std::stack<std::string> &operations;

	evaluate(std::stack<std::string> &numbers, std::stack<std::string> &operations) :
		numbers(numbers), operations(operations) {}

	void operator()(std::string const &) {
		int first, second, result = 0;

		if (numbers.empty()) throw "";
		std::stringstream(numbers.top()) >> second;
		numbers.pop();

		if (numbers.empty()) throw "";
		std::stringstream(numbers.top()) >> first;
		numbers.pop();

		std::string operation = operations.top();
		operations.pop();

		if (operation == "+") result = (first + second);
		else if (operation == "-") result = (first - second);
		else if (operation == "*") result = (first * second);
		else if (operation == "/") result = (first / second);

		std::stringstream result_string;
		result_string << result;
		numbers.push(result_string.str());
	}
};

bool test_12() {
	rule sum, product, multiplicand, group;
	std::stack<std::string> numbers, operations;
	//std::string expression = "2 + 3 * 4";
	//std::string expression = "2 * 3 + 4";
	std::string expression = "(2 + 3 * (4 - 2)) / 4";
	//std::string expression = "4 + 2 + 3";

	group <<= -character("(") << -sum << -character(")");
	multiplicand <<= -integer()[([&numbers](std::string const &s){numbers.push(s);})] | group;
	product <<= -multiplicand << *(-character("*/")[([&operations](std::string const &s){operations.push(s);})] << -multiplicand[evaluate(numbers,operations)]);
	sum <<= -product << *(-character("+-")[([&operations](std::string const &s){operations.push(s);})] << -product[evaluate(numbers,operations)]);

	base_rule::match_range a_range;
	base_rule::match_range i(expression.begin(), expression.end());

	if (sum.match(i, a_range)) {
		std::cout << "Match: " << std::string(a_range.first, a_range.second) << std::endl;
		std::cout << numbers.top() << std::endl; numbers.pop();
		return true;
	}
	else {
		std::cout << base_rule::get_error_message(base_rule::match_range(expression.begin(), expression.end())) << std::endl;
		return false;
	}
}

bool test_13() {
	rule main, aux;
	std::string text = "abc";

	main <<= aux << aux << aux[([](std::string const &s){std::cout << s;})];
	aux <<= character("cba");

	base_rule::match_range i(text.begin(), text.end());
	base_rule::match_range range;

	if (main.match(i, range)) {
		std::cout << "\nMatch: " << std::string(range.first, range.second) << std::endl;
		return true;
	}
	else return false;
}

bool test_14() {
	rule main, aux;
	std::string text = "abc";

	main <<= aux << aux << aux;
	aux <<= character("cba")[([](std::string const &s){std::cout << s;})];

	base_rule::match_range i(text.begin(), text.end());
	base_rule::match_range range;

	if (main.match(i, range)) {
		std::cout << "\nMatch: " << std::string(range.first, range.second) << std::endl;
		return true;
	}
	else return false;
}

bool test_15() {
	rule main;
	std::string text = "\t-12.03e-87";

	main <<= -real()[([](std::string const &s){std::cout << s << std::endl;})];

	base_rule::match_range i(text.begin(), text.end());
	base_rule::match_range range;

	if (main.match(i, range)) {
		std::cout << "Match: " << std::string(range.first, range.second) << std::endl;
		return true;
	}
	else return false;
}

bool test_16() {
	rule main;
	std::string text = "\tint\tan_integer_9\n";

	main <<= *(-identifier()[([](std::string const &s){std::cout << s << std::endl;})]);

	base_rule::match_range i(text.begin(), text.end());
	base_rule::match_range range;

	if (main.match(i, range)) {
		std::cout << "Match: " << std::string(range.first, range.second) << std::endl;
		return true;
	}
	else return false;
	
}

bool test_17() {
	rule main;
	std::string text = "\tint\tan_integer_9\n";

	main	<<=	-keyword("int")[(
					[](std::string const &s){std::cout << s << std::endl;}
				)] 
			<<	-identifier()[(
					[](std::string const &s){std::cout << s << std::endl;}
				)];

	base_rule::match_range i(text.begin(), text.end());
	base_rule::match_range range;

	if (main.match(i, range)) {
		std::cout << "Match: " << std::string(range.first, range.second) << std::endl;
		return true;
	}
	else return false;
}

bool test_18() {
	rule main;
	std::string text = "\n\t\"helló \t\\\"világ\\\"!\"";

	main <<= -string('"', '\\');

	base_rule::match_range i(text.begin(), text.end());
	base_rule::match_range range;

	if (main.match(i, range)) {
		std::cout << "Match: " << std::string(range.first + 1, range.second - 1) << std::endl;
		return true;
	}
	else return false;
}

bool test_19() {
	rule main;
	std::string text = "for(int";

	main <<= -keyword("for") << -character("(") << -keyword("int");

	base_rule::match_range i(text.begin(), text.end());
	base_rule::match_range range;

	if (main.match(i, range)) {
		std::cout << "Match: " << std::string(range.first, range.second) << std::endl;
		return true;
	}
	else return false;
}

bool test_20() {
	try {
		rule main;

		main <<= range('z', 'a');
	}
	catch (std::invalid_argument &ia) {
		std::cout << ia.what() << std::endl;
		return true;
	}

	return false;
}

bool test_21() {
	rule main;
	std::string text = "for(int i <=8\t\n";

	main <<= -keyword("for") << -character("(") << -keyword("int") << -identifier() << -substring("<=") << -integer() << -epsilon();

	base_rule::match_range i(text.begin(), text.end());
	base_rule::match_range range;

	if (main.match(i, range) && range.first == text.begin() && range.second == text.end()) {
		std::cout << "Match: " << std::string(range.first, range.second) << std::endl;
		return true;
	}
	else return false;
}

bool test_22() {
	rule line, sentence;
	std::string contents = "abd 12 32\ndfe 34 12\n";
	

	line <<= -identifier()[([](std::string const &id){std::cout << id << std::endl;})] << +-integer()[([](std::string const &num){std::cout << num << std::endl;})] << eol();
	sentence <<= +line[([](std::string const &){std::cout << std::endl;})];

	base_rule::match_range i(contents.begin(), contents.end());
	base_rule::match_range a_range;
	if (sentence.match(i, a_range)) {
		std::string s(a_range.first, a_range.second);
		std::cout << "Match: " << s << std::endl;
		return true;
	}
	else {
		std::cout << "Did not match" << std::endl;
		return false;
	}
}

bool test_23() {
	rule title, date, plotname, flags, variable_no, points, variables; 
	rule variable_definition, values, value_item;
	rule sentence;
	std::string contents;
	
	if (!base_rule::file_to_string("test_data/rawspice.raw", contents)) return false;

	title <<= -keyword("Title:", ":") << *~identifier() << ~eol();
	date <<= -keyword("Date:", ":") << -identifier() << -identifier() << -integer() << -+range('0', '9') << character(":") << +range('0', '9') << character(":") << +range('0', '9') << -integer() << ~eol();
	plotname <<= -keyword("Plotname:", ":") << +~identifier() << ~eol();
	flags <<= -keyword("Flags:", ":") << +~identifier() << ~eol();
	variable_no <<= -keyword("No. Variables:", ":") << -integer() << ~eol();
	points <<= -keyword("No. Points:", ":") << -integer() << ~eol();
	variable_definition <<= ~integer() << -identifier("_()") << -identifier("_()") << ~eol();
	variables <<= -keyword("Variables:", ":") << ~eol() << *variable_definition;
	value_item <<= ~integer() << *(~real() << ~eol());
	values <<= -keyword("Values:") << *-value_item;

	sentence <<= title << date << plotname << flags << variable_no << points << variables << values;

	base_rule::match_range i(contents.begin(), contents.end());
	base_rule::match_range a_range;
	if (sentence.match(i, a_range)) {
		std::string s(a_range.first, a_range.second);
		std::cout << "Match: " << s << std::endl;
		return true;
	}
	else {
		std::cout << "Did not match" << std::endl;
		return false;
	}
}

int main() {
	util::tester::tester the_tester(__FILE__);

	//*
	the_tester.add(test_0);
	the_tester.add(test_1);
	the_tester.add(test_2);
	the_tester.add(test_3);
	the_tester.add(test_4);
	the_tester.add(test_5);
	the_tester.add(test_6);
	the_tester.add(test_7);
	the_tester.add(test_8);
	the_tester.add(test_9);
	the_tester.add(test_10);
	the_tester.add(test_11);
	the_tester.add(test_12);
	the_tester.add(test_13);
	the_tester.add(test_14);
	the_tester.add(test_15);
	the_tester.add(test_16);
	the_tester.add(test_17);
	the_tester.add(test_18);
	the_tester.add(test_19);
	the_tester.add(test_20);
	the_tester.add(test_21);
	the_tester.add(test_22);
	the_tester.add(test_23);
	// */

	return the_tester.run();
}


