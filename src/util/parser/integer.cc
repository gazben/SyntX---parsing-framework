#include <util/parser/integer.h>
#include <util/parser/range.h>
#include <util/parser/character.h>

namespace util {
	namespace parser {
		bool integer::test(base_rule::match_range &context, match_range &the_match_range) {
			if (context.first == context.second) return false;

			base_rule::match_range local_context = context;
			base_rule::match_range a_range;
			range non_zero('1', '9'), numeric('0', '9');
			character neg_sign("-"), pos_sign("+"), zero("0");
			bool has_sign = false;

			if (the_integer_type == signed_int) has_sign = neg_sign.match(local_context, a_range);
			if (!has_sign) pos_sign.match(local_context, a_range);

			if (zero.match(local_context, a_range)) {
				the_match_range.first = context.first;
				the_match_range.second = a_range.second;
				context = local_context;

				return true;
			}
			else if (non_zero.match(local_context, a_range)) {
				while (numeric.match(local_context, a_range));

				the_match_range.first = context.first;
				the_match_range.second = a_range.second;
				context = local_context;

				return true;
			}

			return false;
		}
	}
}
