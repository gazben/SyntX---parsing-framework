#ifndef _UTIL_PARSER_WHITESPACE_
#define _UTIL_PARSER_WHITESPACE_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class whitespace : public base_rule {
			private:
				std::shared_ptr<base_rule> a_rule;

			public:
				whitespace(base_rule const &a_rule) : a_rule(a_rule.clone()) {}

				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new whitespace(*this));
				}
		};
	}
}

#endif // _UTIL_PARSER_WHITESPACE_
