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

#include <applications/symbolic_expression.h>

namespace applications {
	symbolic_expression::symbolic_expression() {
		using namespace util::parser;
		
		tree_node *current_root = &root; 

		expression	<<=	-character("(")[( [&current_root](std::string const &){current_root = current_root->add_child("");} )]
					<<	*-(
							(
									identifier()
								|	real()
								|	string()
								|	character("+-*/!?")
							)[( [&current_root](std::string const &s){current_root->add_child(s);} )]
							|	expression
						)
					<<	-character(")")[( [&current_root](std::string const &){current_root = current_root->parent;} )];
	}

	bool symbolic_expression::test(std::string const &text) {
		util::parser::base_rule::match_range context(text.begin(), text.end()), range;
		
		if (expression.match(context, range)) {
			std::cout << "Match" << std::endl;
			return true;
		}
		else {
			std::cout << "Didn't match" << std::endl;
			return false;
		}
	}

}
