#include <util/parser/range.h>
#include <util/parser/character.h>
#include <util/parser/substring.h>

namespace util {
	namespace parser {
		bool substring::test(base_rule::match_range &context, base_rule::match_range &the_match_range) {
			if (context.first == context.second) return false;

			base_rule::match_range local_context = context;
			base_rule::match_range word_range(the_word.begin(), the_word.end());

			while (word_range.first != word_range.second && local_context.first != context.second && *word_range.first == *local_context.first) {
				++word_range.first;
				++local_context.first;
			}

			if (word_range.first == word_range.second) {
				the_match_range.first = context.first;
				the_match_range.second = local_context.first;
				context = local_context;
				return true;
			}
			else return false;
		}
	}
}
