#include <string>
#include <iostream>

#include <util/parser/parser.h>
#include <applications/symbolic_expression.h>

enum error_code {OK, FILE_NOT_FOUND, DIDNT_MATCH};

void print_tree(applications::symbolic_expression::tree_node &root, std::ostream &stream = std::cout) {
	stream << root.value << std::endl;

	for (auto p : root.children) {
		print_tree(*p, stream);
	}
}

int main() {
	std::string contents;

	if (!util::parser::base_rule::file_to_string("test_data/se.tt", contents)) return FILE_NOT_FOUND;

	applications::symbolic_expression se;

	if (se.test(contents)) {
		print_tree(se.get_root());
		return OK;

	}
	else return DIDNT_MATCH;
	
	return OK;
}
