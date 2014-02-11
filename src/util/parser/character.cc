#include <util/parser/character.h>

namespace util {
	namespace parser {
		bool character::test(base_rule::match_range &context, match_range &the_match_range) {
			if (context.first == context.second) return false;

			base_rule::match_range local_context = context;
			std::string::const_iterator allowed_character = allowed_characters.begin();

			for (; allowed_character != allowed_characters.end(); ++allowed_character) {
				if (*local_context.first == *allowed_character) {
					++local_context.first;

					the_match_range.first = context.first;
					the_match_range.second = local_context.first;
					context = local_context;
					return true;
				}
			}

			return false;
		}
	}
}
