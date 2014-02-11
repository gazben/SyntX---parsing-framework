#include <util/parser/rule.h>
#include <util/parser/option.h>
#include <util/parser/repetition.h>
#include <util/parser/whitespace.h>
#include <util/parser/whitespace_not_newline.h>
#include <util/parser/alternation.h>
#include <util/parser/concatenation.h>
#include <util/parser/repetition_or_epsilon.h>

namespace util {
	namespace parser {
		bool rule::test(match_range &context, match_range &the_match_range) {
			if (!(*the_rule)) return false;
			return (*the_rule)->match(context, the_match_range);
		}

		rule &rule::operator <<=(base_rule const &rhs) {
			set_rule(rhs.clone());
			return *this;
		}

		rule operator <<(base_rule const &first, base_rule const &second) {
			return rule(std::shared_ptr<base_rule>(new concatenation(first, second)));
		}

		rule operator |(base_rule const &first, base_rule const &second) {
			return rule(std::shared_ptr<base_rule>(new alternation(first, second)));
		}

		rule operator !(base_rule const &optional_rule) {
			return rule(std::shared_ptr<base_rule>(new option(optional_rule)));
		}

		rule operator +(base_rule const &repeated_rule) {
			return rule(std::shared_ptr<base_rule>(new repetition(repeated_rule)));
		}

		rule operator *(base_rule const &repeated_rule) {
			return rule(std::shared_ptr<base_rule>(new repetition_or_epsilon(repeated_rule)));
		}

		rule operator -(base_rule const &a_rule) {
			return rule(std::shared_ptr<base_rule>(new whitespace(a_rule)));
		}

		rule operator ~(base_rule const &a_rule) {
			return rule(std::shared_ptr<base_rule>(new whitespace_not_newline(a_rule)));
		}
	}
}
