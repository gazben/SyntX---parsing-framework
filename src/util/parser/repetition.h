#ifndef _UTIL_PARSER_REPETITION_
#define _UTIL_PARSER_REPETITION_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class repetition : public base_rule {
			private:
				std::shared_ptr<base_rule> repeated_rule;

			public:
				repetition(base_rule const &repeated_rule) : repeated_rule(repeated_rule.clone()) {}

				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new repetition(*this));
				}
		};
	}
}

#endif // _UTIL_PARSER_REPETITION_
