#include <util/parser/repetition.h>

namespace util {
	namespace parser {
		bool repetition::test(base_rule::match_range &context, base_rule::match_range &the_match_range) {
			base_rule::match_range range;
			base_rule::match_range local_context = context;

			if (repeated_rule->match(local_context, range)) {
				the_match_range.first = range.first;
				the_match_range.second = range.second;

				while (repeated_rule->match(local_context, range)) {
					the_match_range.second = range.second;
				}

				context = local_context;
				return true;
			}

			return false;
		}
	}
}
