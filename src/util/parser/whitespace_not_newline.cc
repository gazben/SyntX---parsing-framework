#include <util/parser/whitespace_not_newline.h>

namespace util {
	namespace parser {

		char whitespace_not_newline::whitespace_characters[] = " \t\v\r\f";
		
		bool whitespace_not_newline::is_whitespace_not_newline(char c) {
			for (size_t i = 0; whitespace_characters[i] != 0; ++i) {
				if (c == whitespace_characters[i]) return true;
			}
			return false;
		}

		bool whitespace_not_newline::test(base_rule::match_range &context, base_rule::match_range &the_match_range) {
			if (context.first == context.second) return false;
			
			base_rule::match_range range;
			base_rule::match_range local_context = context;


			while (local_context.first != local_context.second && is_whitespace_not_newline(*local_context.first)) ++local_context.first;

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

