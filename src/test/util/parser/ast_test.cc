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
#include <iostream>

#include <util/parser/parser.h>

using namespace util::parser;

void parse_tree(std::shared_ptr<base_rule::node> const &node, size_t depth = 0) {
	if (node) {
		for (size_t i = 0; i < depth; ++i) std::cout << " ";

		switch (node->the_type) {
			case base_rule::node::type::value:
				std::cout << node->the_value << std::endl;
			break;

			case base_rule::node::type::alternation:
				std::cout << "alternation" << std::endl;
			break;

			case base_rule::node::type::concatenation:
				std::cout << "concatenation" << std::endl;
			break;

			case base_rule::node::type::option:
				std::cout << "option" << std::endl;
			break;

			case base_rule::node::type::repetition:
				std::cout << "repetition" << std::endl;
			break;

			case base_rule::node::type::repetition_or_epsilon:
				std::cout << "repetition_or_epsilon" << std::endl;
			break;
		}

		for (auto &a_node: node->children) parse_tree(a_node, depth + 1);
	}
}

int main() {
	base_rule::set_build_ast(true);

	rule addition, addend, expression;

	addition <<= -addend << *(-character("+") << -addend);
	addend <<= -range('0', '9') | -expression;
	expression <<= -character("(") << -addition << -character(")");

	std::string input = "2 + (3 + 4)\n";
	base_rule::match_range context(input.cbegin(), input.cend());
	base_rule::match_range result;
	std::shared_ptr<base_rule::node> root;

	if (addition.match(context, result, root)) {
		std::cout << "Matched: " << std::string(result.first, result.second) << std::endl;
		parse_tree(root);
	} else {
		std::cout << "Didn't match" << std::endl;
	}
}

