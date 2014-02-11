#ifndef _UTIL_PARSER_OPTION_
#define _UTIL_PARSER_OPTION_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class option : public base_rule {
			private:
				std::shared_ptr<base_rule> optional_rule;

			public:
				option(base_rule const &optional_rule) : optional_rule(optional_rule.clone()) {}

				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new option(*this));
				}
		};
	}
}

#endif // _UTIL_PARSER_OPTION_
