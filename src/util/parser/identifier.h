#ifndef _UTIL_PARSER_IDENTIFIER_
#define _UTIL_PARSER_IDENTIFIER_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class identifier : public base_rule {
			private:
				std::string extra_characters;

			public:
				identifier(std::string const &extra_characters = "_") : extra_characters(extra_characters) {}
				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new identifier(*this));
				}
		};
	}
}

#endif //_UTIL_PARSER_IDENTIFIER_

