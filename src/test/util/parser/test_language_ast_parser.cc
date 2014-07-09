#include <string>
#include <memory>
#include <iostream>

#include <util/parser/parser.h>

#include <test/util/parser/language_ast_parser.h>

int main() {
	std::string input;

	if (base_rule::file_to_string("test_data/code_example", input)) {
		std::string result;
		language_ast_parser parser;
		std::shared_ptr<base_rule::node> ast;

		if (parser.match(input, result, ast)) {
			std::vector<std::pair<std::string,std::string>> the_program;

			std::cout << "Matched: " << result << std::endl;
			
			language_ast_parser::traverse_tree(ast, the_program);
			language_ast_parser::print_program(std::cout, the_program);
		}
		else std::cout << "Didn't match." << std::endl;
	}	
	else std::cout << "Couldn't open file" << std::endl;
}

