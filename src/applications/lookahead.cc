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

#include <applications/lookahead.h>

namespace applications {
	lookahead::lookahead() {
		using namespace util::parser;

		for_loop	<<=	(
							-range_for[(
								[](std::string const &s){std::cout << "range for";}
							)] 
						|	-iterator_for[(
								[](std::string const &s){std::cout << "iterator for";}
							)]
						)
						<< -epsilon();
		;

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

		declaration		<<=	-(keyword("int") | keyword("char") | keyword("unsigned"))
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
	}

	bool lookahead::test(std::string const &text, std::string &result) {
		util::parser::base_rule::match_range range;
		util::parser::base_rule::match_range i(text.begin(), text.end());

		if (for_loop.match(i, range)) {
			result = std::string(range.first, range.second);
			return true;
		}
		else return false;
	}

}
