#include <util/parser/character.h>
#include <util/parser/range.h>
#include <util/parser/integer.h>
#include <util/parser/real.h>

namespace util {
	namespace parser {
		bool real::test(base_rule::match_range &context, base_rule::match_range &the_match_range) {
			if (context.first == context.second) return false;

			base_rule::match_range local_context = context;
			base_rule::match_range a_range;

			range numeric('0', '9');
			character neg_sign("-"), pos_sign("+"), zero("0");
			character dot("."), exponent("eE"); 
			integer an_integer;
			bool matched_int = false, matched_float = false, matched_exponent = false;

			matched_int = an_integer.match(local_context, a_range);

			if (dot.match(local_context, a_range)) {
				if ((matched_float = numeric.match(local_context, a_range))) {
					while (numeric.match(local_context, a_range));
				}
			}

			if ((matched_int || matched_float) && (matched_exponent = exponent.match(local_context, a_range))) {
				if (!neg_sign.match(local_context, a_range)) pos_sign.match(local_context, a_range);
				zero.match(local_context, a_range);
				while (numeric.match(local_context, a_range));
			}

			if (matched_int || matched_float) {
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
