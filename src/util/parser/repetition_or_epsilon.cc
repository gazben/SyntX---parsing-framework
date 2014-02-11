#include <util/parser/repetition_or_epsilon.h>

namespace util {
	namespace parser {
		bool repetition_or_epsilon::test(base_rule::match_range &context, base_rule::match_range &the_match_range) {
			base_rule::match_range range;
			base_rule::match_range local_context = context;

			the_match_range.first = the_match_range.second = context.first;

			while (repeated_rule->match(local_context, range)) {
				the_match_range.second = range.second;
				context = local_context;
			}

			return true;
		}
	}
}
