#include <string>
#include <memory>
#include <iostream>

#include <util/parser/parser.h>

#include <test/util/parser/language_ast_parser.h>

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
	std::string input;

	if (base_rule::file_to_string("test_data/code_example", input)) {
		std::string result;
		language_ast_parser parser;
		std::shared_ptr<base_rule::node> ast;

		if (parser.match(input, result, ast)) {
			std::cout << "Matched: " << result << std::endl;
			parse_tree(ast);
		}
		else std::cout << "Didn't match." << std::endl;
	}	
	else std::cout << "Couldn't open file" << std::endl;

}

