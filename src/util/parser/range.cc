#include <util/parser/range.h>

namespace util {
	namespace parser {
		bool range::test(base_rule::match_range &context, base_rule::match_range &the_match_range) {
			if (context.first == context.second) return false;

			base_rule::match_range local_context = context;

			if (*local_context.first >= range_first && *local_context.first <= range_last) {
				++local_context.first;

				the_match_range.first = context.first;
				the_match_range.second = local_context.first;
				context = local_context;
				return true;
			}

			return false;
		}
	}
}
