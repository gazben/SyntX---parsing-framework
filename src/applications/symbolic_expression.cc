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
