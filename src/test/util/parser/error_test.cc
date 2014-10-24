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

int main() {
	rule addition, addend, expression;

	addition <<= addend << +(character("+") << addend);
	addend <<= range('0', '9') | expression;
	expression <<= character("(") << addition << character(")");

	std::string input = "2+(3-4)";
	base_rule::match_range context(input.cbegin(), input.cend());
	base_rule::match_range result;

	if (addition.match(context, result))
		std::cout << "Matched: " << std::string(result.first, result.second) << std::endl;
	else {
		std::cout << base_rule::get_error_message(base_rule::match_range(input.cbegin(), input.cend())) << std::endl;
	}
}

