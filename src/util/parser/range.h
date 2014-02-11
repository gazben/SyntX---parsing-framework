#ifndef _UTIL_PARSER_RANGE_
#define _UTIL_PARSER_RANGE_

#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class range : public base_rule {
			private:
				char range_first;
				char range_last;

			public:
				range(char range_first, char range_last) throw (std::invalid_argument) :
					range_first(range_first),
					range_last(range_last) {
						if (range_first > range_last) {
							std::stringstream str;
							str << "Range's lower bound (" << range_first << ") greater than upper bound (" << range_last << ").";
							throw std::invalid_argument(str.str());
						}
				}

				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new range(*this));
				}
		};
	}
}

#endif // _UTIL_PARSER_RANGE_
