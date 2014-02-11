#ifndef _UTIL_PARSER_CONCATENATION_
#define _UTIL_PARSER_CONCATENATION_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class concatenation : public base_rule {
			private:
				std::shared_ptr<base_rule> first;
				std::shared_ptr<base_rule> second;

			public:
				concatenation(base_rule const &first, base_rule const &second) : first(first.clone()), second(second.clone()) {}

				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new concatenation(*this));
				}
		};

	}
}

#endif // _UTIL_PARSER_CONCATENATION_
