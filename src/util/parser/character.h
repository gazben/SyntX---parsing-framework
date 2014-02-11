#ifndef _UTIL_PARSER_CHARACTER_
#define _UTIL_PARSER_CHARACTER_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class character : public base_rule {
			private:
				std::string allowed_characters;

			public:
				character(std::string const &allowed_characters) : allowed_characters(allowed_characters) {}

				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new character(*this));
				}
		};
	}
}

#endif //_UTIL_PARSER_CHARACTER_
