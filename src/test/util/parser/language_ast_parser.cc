#include <test/util/parser/language_ast_parser.h>

language_ast_parser::language_ast_parser() :
	range_for("range_for"),
	iterator_for("iterator_for"),
	variable_type("variable_type"),
	type_modifier("type_modifier"),
	variable_name("variable_name"),
	variable_value("variable_value"),
	container_name("container_name"),
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
								<<	-substring(";")
							)
							|	-for_loop
						 )
					<<	-block_end;

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
