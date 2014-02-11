#include <util/parser/range.h>
#include <util/parser/character.h>
#include <util/parser/keyword.h>

namespace util {
	namespace parser {
		bool keyword::test(base_rule::match_range &context, base_rule::match_range &the_match_range) {
			if (context.first == context.second) return false;

			base_rule::match_range local_context = context;
			base_rule::match_range a_range;

			range lower('a', 'z'), upper('A', 'Z'), numeric('0', '9');
			character extra(extra_characters);

			base_rule::match_range word_range(the_word.begin(), the_word.end());

			while (word_range.first != word_range.second && local_context.first != context.second && *word_range.first == *local_context.first) {
				++word_range.first;
				++local_context.first;
			}

			if (word_range.first == word_range.second && 
				!(
					lower.match(local_context, a_range) || upper.match(local_context, a_range) || 
					numeric.match(local_context, a_range) || extra.match(local_context, a_range)
				)
					
			) {
				the_match_range.first = context.first;
				the_match_range.second = local_context.first;
				context = local_context;
				return true;
			}
			else return false;
		}
	}
}
