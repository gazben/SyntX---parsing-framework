#ifndef _APPLICATIONS_LOOKAHEAD_
#define _APPLICATIONS_LOOKAHEAD_

#include <string>

#include <util/parser/parser.h>

namespace applications {
	class lookahead {
		private:
			util::parser::rule for_loop, range_for, iterator_for, declaration, logic_expression, expression;

		public:
			lookahead();

			bool test(std::string const &text, std::string &result);
	};
}
#endif // _APPLICATIONS_LOOKAHEAD_
