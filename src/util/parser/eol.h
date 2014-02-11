#ifndef _UTIL_PARSER_EOL_
#define _UTIL_PARSER_EOL_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class eol : public base_rule {
			public:
				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new eol(*this));
				}

		};
	}
}

#endif //_UTIL_PARSER_EOL_

