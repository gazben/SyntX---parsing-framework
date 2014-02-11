#ifndef _UTIL_PARSER_REPETITIONOREPSILON_
#define _UTIL_PARSER_REPETITIONOREPSILON_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class repetition_or_epsilon : public base_rule {
			private:
				std::shared_ptr<base_rule> repeated_rule;

			public:
				repetition_or_epsilon(base_rule const &repeated_rule) : repeated_rule(repeated_rule.clone()) {}

				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new repetition_or_epsilon(*this));
				}
		};
	}
}

#endif // _UTIL_PARSER_REPETITIONOREPSILON_
