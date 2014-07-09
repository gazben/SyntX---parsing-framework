#include <test/util/parser/language_ast_parser.h>

language_ast_parser::language_ast_parser() :
	range_for("range_for"),
	iterator_for("iterator_for"),
	variable_type("variable_type"),
	type_modifier("type_modifier"),
	variable_name("variable_name"),
	variable_value("variable_value"),
	container_name("container_name"),
	expression_end("expression_end"),
	preincrement("preincrement"),
	postincrement("postincrement"),
	logic_operator("logic_operator"),
	block_start("block_start"),
	block_end("block_end") {

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
					<<	-container_name
					<<	-substring(")");

		container_name	<<=	identifier();

		iterator_for	<<=	-keyword("for")
						<<	-substring("(")
						<<	-declaration
						<<	-substring(";")
						<<	-logic_expression
						<<	-substring(";")
						<<	-expression
						<<	-substring(")");

		declaration		<<=	-variable_type
						<<	-type_modifier
						<<	-variable_name
						<<	!(
									-substring("=")
								<<	-variable_value
							 );

		variable_type	<<=	-(keyword("int") | keyword("char") | keyword("unsigned") | keyword("auto"));

		type_modifier	<<= -!(
									substring("&")
								|	substring("*")
							  );

		variable_name	<<=	identifier();

		variable_value	<<=	-integer();

		logic_expression	<<=	-variable_name
							<<	-logic_operator
							<<	-variable_value;

		logic_operator		<<=	-(substring("==") | substring("<") | substring(">") | substring("<=") | substring(">="));

		expression	<<=	-!preincrement
					<<	variable_name
					<<	-!postincrement;

		preincrement	<<=	-substring("++");
		postincrement	<<=	-substring("++");

		block		<<=	-block_start
					<<	+(
							(
									-expression
								<<	-expression_end
							)
							|	-for_loop
						 )
					<<	-block_end;

		expression_end	<<=	-substring(";");

		block_start	<<=	-substring("{");

		block_end	<<=	-substring("}");
}

bool language_ast_parser::match(std::string const &text, std::string &result, std::shared_ptr<base_rule::node> &ast_root) {
	base_rule::set_build_ast(true);
	util::parser::base_rule::match_range range;
	util::parser::base_rule::match_range i(text.begin(), text.end());

	if (program.match(i, range, ast_root)) {
		result = std::string(range.first, range.second);
		return true;
	}
	else return false;
}

void language_ast_parser::traverse_tree(std::shared_ptr<base_rule::node> const &a_node, std::vector<std::pair<std::string,std::string>> &the_program) {
	static enum {name, value} state = name;
	static std::string current_name;

	if (a_node) {
		switch (state) {
			case name:
				if (a_node->the_type == base_rule::node::type::named_rule) {
					current_name = a_node->the_value;
					state = value;
				}
				break;

			case value:
				if (a_node->the_type == base_rule::node::type::value) {
					the_program.push_back(std::make_pair(current_name, a_node->the_value));
					state = name;
				}
			break;
		}

		for (auto &n: a_node->children) traverse_tree(n, the_program);
	}
}

void language_ast_parser::print_program(std::ostream &os, std::vector<std::pair<std::string,std::string>> &the_program) {
	auto print_tabs = [&os](size_t n){for (size_t i = 0; i < n; ++i) os << "\t";};
	size_t tabs = 0;

	for (auto &element: the_program) {
		if (element.first == "block_start") ++tabs;
		else if (element.first == "block_end") --tabs;
		else if (element.first == "iterator_for") {os << std::endl; print_tabs(tabs); os << "iterator_for" << std::endl;}
		else if (element.first == "range_for") {os << std::endl; print_tabs(tabs); os << "range_for" << std::endl;}
		else if (element.first == "expression_end") {os << std::endl;}
		else {
			print_tabs(tabs);
			os << element.first << ": " << element.second << std::endl;
		}
	}
}
