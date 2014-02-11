#include <util/parser/whitespace.h>
#include <cctype>

namespace util {
	namespace parser {
		bool whitespace::test(base_rule::match_range &context, base_rule::match_range &the_match_range) {
			if (context.first == context.second) return false;
			
			base_rule::match_range range;
			base_rule::match_range local_context = context;

			while (local_context.first != local_context.second && ::isspace(*local_context.first)) ++local_context.first;

			if (a_rule->match(local_context, range)) {
				the_match_range.first = range.first;
				the_match_range.second = range.second;
				context = local_context;

				return true;
			}

			return false;
		}
	}
}
