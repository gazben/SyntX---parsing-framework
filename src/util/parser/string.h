#ifndef _UTIL_PARSER_STRING_
#define _UTIL_PARSER_STRING_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class string : public base_rule {
			private:
				char delimiter; /**< The string delimiter character. */
				char escape_character; /**< The escape_character. */
				
			public:
				string(char delimiter = '\"', char escape_character = '\\') :
					delimiter(delimiter),
					escape_character(escape_character) {}

				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new string(*this));
				}
		};
	}
}

#endif //_UTIL_PARSER_STRING_
