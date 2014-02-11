#include <util/parser/alternation.h>

namespace util {
	namespace parser {
		bool alternation::test(base_rule::match_range &context, base_rule::match_range &the_match_range) {
			base_rule::match_range first_range, second_range;
			base_rule::match_range local_context = context;

			if (first->match(local_context, first_range)) {
				the_match_range.first = first_range.first;
				the_match_range.second = first_range.second;
				context = local_context;

				return true;
			}
			
			local_context = context;

			if (second->match(local_context, second_range)) {
				the_match_range.first = second_range.first;
				the_match_range.second = second_range.second;
				context = local_context;

				return true;
			}
			
			return false;
		}
	}
}

