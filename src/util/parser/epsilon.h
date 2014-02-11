#ifndef _UTIL_PARSER_EPSILON_
#define _UTIL_PARSER_EPSILON_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class epsilon : public base_rule {
			public:
				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range) {
					the_match_range.first = the_match_range.second = context.first;
					return true;
				}

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new epsilon(*this));
				}
		};
	}
}

#endif // _UTIL_PARSER_EPSILON_
