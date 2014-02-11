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
