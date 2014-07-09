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
		if (show_non_value_nodes || node->the_type == base_rule::node::type::value || node->the_type == base_rule::node::type::named_rule)
			for (size_t i = 0; i < depth; ++i) std::cout << " ";

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
				std::cout << "named_rule: " << node->the_value;
				break;
		}

		if (show_non_value_nodes || node->the_type == base_rule::node::type::value || node->the_type == base_rule::node::type::named_rule) std::cout << std::endl;

		for (auto &a_node: node->children) parse_tree(a_node, show_non_value_nodes, depth + 1);
	}
}

int main() {
	base_rule::set_build_ast(true);

	rule program;
	rule for_loop;
	rule range_for("range_for");
	rule iterator_for("iterator_for");
	rule declaration;
	rule logic_expression;
	rule expression;
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

	block		<<=	-substring("{")
				<<	+(
							-expression
						<<	-substring(";")
					 )
				<<	-substring("}");

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


