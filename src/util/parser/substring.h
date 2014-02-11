#ifndef _UTIL_PARSER_SUBSTRING_
#define _UTIL_PARSER_SUBSTRING_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class substring : public base_rule {
			private:
				std::string the_word;

			public:
				substring(std::string const &the_word) : the_word(the_word) {}

				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new substring(*this));
				}
		};
	}
}

#endif //_UTIL_PARSER_SUBSTRING_

