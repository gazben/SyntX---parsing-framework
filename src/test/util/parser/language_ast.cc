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

void parse_tree(std::shared_ptr<base_rule::node> const &node, bool show_non_value_nodes = false, size_t depth = 0) {
	if (node) {
		if (show_non_value_nodes || node->the_type == base_rule::node::type::value) for (size_t i = 0; i < depth; ++i) std::cout << " ";

		switch (node->the_type) {
			case base_rule::node::type::value:
				std::cout << node->the_value;
				break;

			case base_rule::node::type::alternation:
				if (show_non_value_nodes) {
					std::cout << "alternation";
				}
				break;

			case base_rule::node::type::concatenation:
				if (show_non_value_nodes) {
					std::cout << "concatenation";
				}
				break;

			case base_rule::node::type::option:
				if (show_non_value_nodes) {
					std::cout << "option";
				}
				break;

			case base_rule::node::type::repetition:
				if (show_non_value_nodes) {
					std::cout << "repetition";
				}
				break;

			case base_rule::node::type::repetition_or_epsilon:
				if (show_non_value_nodes) {
					std::cout << "repetition_or_epsilon";
				}
				break;

			case base_rule::node::type::named_rule:
				std::cout << "named_rule: " << node->the_rule_name;
				break;
		}

		if (show_non_value_nodes || node->the_type == base_rule::node::type::value || node->the_type == base_rule::node::type::named_rule) std::cout << std::endl;

		for (auto &a_node: node->children) parse_tree(a_node, show_non_value_nodes, depth + 1);
	}
}

int main() {
	base_rule::set_build_ast(true);

	rule program, loop("loop"), if_statement, block, condition, expression, addition, addend, definition("definition");

	program <<= +(-loop | -if_statement | -definition);

	loop <<= -keyword("while") << -character("(") << -condition << -character(")") << -block;
	if_statement <<= -keyword("if") << -character("(") << -condition << -character(")") << -block;
	definition <<= -keyword("while") << -identifier() << -character(";"); //This is to show that the parser and AST can look ahead as needed

	block <<= -character("{") << +((-addition << -character(";")) | -loop | -if_statement) << -character("}");

	condition <<= -range('0', '9') << -character("<=>") << -range('0', '9');

	addition <<= -addend << *(-character("+") << -addend);
	addend <<= -range('0', '9') | -expression;
	expression <<= -character("(") << -addition << -character(")");

	std::string input;
	if (base_rule::file_to_string("test_data/code_example", input)) {
		base_rule::match_range context(input.cbegin(), input.cend());
		base_rule::match_range result;
		std::shared_ptr<base_rule::node> root;

		if (program.match(context, result, root)) {
			std::cout << "Matched: " << std::string(result.first, result.second) << std::endl;
			std::cout << std::endl << std::endl << "The Abstract Parsing Tree:" << std::endl;
			parse_tree(root);
		}
		else {
			std::cout << "Didn't match" << std::endl;
		}
	}
	else {
		std::cout << "Couldn't open file" << std::endl;
	}
}


