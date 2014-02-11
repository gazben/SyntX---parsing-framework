#include <util/parser/string.h>

namespace util {
	namespace parser {
		bool string::test(base_rule::match_range &context, base_rule::match_range &the_match_range) {
			if (context.first == context.second) return false;

			base_rule::match_range local_context = context;

			if (*local_context.first == delimiter) {
				++local_context.first;

				while (local_context.first != local_context.second && *local_context.first != delimiter) {
					if (*local_context.first == escape_character) ++local_context.first;
					++local_context.first;
				}

				++local_context.first;

				the_match_range.first = context.first;
				the_match_range.second = local_context.first;
				context = local_context;
				return true;
			}
			else return false;
		}
	}
}
