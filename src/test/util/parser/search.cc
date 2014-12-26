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

#include <string>
#include <vector>
#include <iostream>

#include <util/parser/parser.h>
#include <util/tester/tester.h>

using namespace util::parser;

bool test_0() {
	rule number;

	number <<= character("(") << integer()[([](std::string const &match){std::cout << "Lambda says: " << match << std::endl;})] << character(")");


	std::string input = "other stuff (3) something else";

	base_rule::match_range context(input.cbegin(), input.cend());
	base_rule::match_range result;

	if (search(context, number, result)) {
		std::cout << "Matched: " << std::string(result.first, result.second) << std::endl;
		return true;
	}
	else {
		std::cout << "Didn't match" << std::endl;
		return false;
	}
}

bool test_1() {
	rule include, path;
	std::vector<std::string> includes;

	include <<= -character("#") << -keyword("include") << -character("<") << -path[([&includes](std::string const &a_path){includes.push_back(a_path);})] << -character(">");
	path <<= +(range('a', 'z') | range('A', 'Z') | range('0', '9') | character("_/."));

	std::string input = R"delimiter(
		#include <iostream>
		#include <string>
		#include <util/parser/parser.h>
		
		int main() {
			std::cout << "Hello" << std::endl;
		}
	)delimiter";

	base_rule::match_range context(input.cbegin(), input.cend());
	base_rule::match_range result;

	if (search_all(context, include, [](std::string const &an_include){std::cout << an_include << std::endl;})) {
		std::cout << "Matched" << std::endl;
		for (auto &path: includes) std::cout << "\t" << path << std::endl;
		return true;
	}
	else {
		std::cout << "Didn't match" << std::endl;
		return false;
	}
}

int main() {
	util::tester::tester the_tester(__FILE__);

	the_tester.add(test_0);
	the_tester.add(test_1);

	return the_tester.run();
}

