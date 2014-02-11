#ifndef _UTIL_PARSER_WHITESPACE_NOT_NEWLINE_
#define _UTIL_PARSER_WHITESPACE_NOT_NEWLINE_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class whitespace_not_newline : public base_rule {
			private:
				std::shared_ptr<base_rule> a_rule;
				static char whitespace_characters[];

			public:
				whitespace_not_newline(base_rule const &a_rule) : a_rule(a_rule.clone()) {}

				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new whitespace_not_newline(*this));
				}

			private:
				bool is_whitespace_not_newline(char c);
		};
	}
}

#endif // _UTIL_PARSER_WHITESPACE_NOT_NEWLINE_

