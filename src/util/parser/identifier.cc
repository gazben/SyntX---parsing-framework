#include <util/parser/range.h>
#include <util/parser/character.h>
#include <util/parser/identifier.h>

namespace util {
	namespace parser {
		bool identifier::test(base_rule::match_range &context, base_rule::match_range &the_match_range) {
			if (context.first == context.second) return false;

			base_rule::match_range local_context = context;
			base_rule::match_range a_range;

			range lower('a', 'z'), upper('A', 'Z'), numeric('0', '9');
			character extra(extra_characters);

			if (lower.match(local_context, a_range) || upper.match(local_context, a_range) || extra.match(local_context, a_range)) {
				while (lower.match(local_context, a_range) || 
					   upper.match(local_context, a_range) || 
					   extra.match(local_context, a_range) || 
					   numeric.match(local_context, a_range)) {}

				the_match_range.first = context.first;
				the_match_range.second = local_context.first;
				context = local_context;
				return true;
			}
			else {
				return false;
			}

		}
	}
}
