#ifndef _UTIL_PARSER_KEYWORD_
#define _UTIL_PARSER_KEYWORD_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class keyword : public base_rule {
			private:
				std::string the_word;
				std::string extra_characters;

			public:
				keyword(std::string const &the_word, std::string const &extra_characters = "_") : 
					the_word(the_word),
					extra_characters(extra_characters) {}

				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new keyword(*this));
				}
		};
	}
}

#endif //_UTIL_PARSER_KEYWORD_

