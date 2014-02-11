#include <util/parser/eol.h>
#include <cctype>

namespace util {
	namespace parser {
		bool eol::test(base_rule::match_range &context, match_range &the_match_range) {
			if (context.first == context.second) return false;

			base_rule::match_range local_context = context;

			if (*local_context.first == '\n') {
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

