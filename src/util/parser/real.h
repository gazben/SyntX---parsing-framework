#ifndef _UTIL_PARSER_REAL_
#define _UTIL_PARSER_REAL_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class real : public base_rule {
			public:
				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new real(*this));
				}
		};
	}
}

#endif //_UTIL_PARSER_REAL_

