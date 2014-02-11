#include <util/parser/option.h>

namespace util {
	namespace parser {
		bool option::test(base_rule::match_range &context, base_rule::match_range &the_match_range) {
			base_rule::match_range range;
			base_rule::match_range local_context = context;

			if (optional_rule->match(local_context, range)) {
				the_match_range.first = range.first;
				the_match_range.second = range.second;
				context = local_context;
			}
			else {
				the_match_range.first = the_match_range.second = context.first;
			}
			
			return true;
		}
	}
}
