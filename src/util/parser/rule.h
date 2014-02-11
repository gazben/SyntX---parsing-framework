#ifndef _UTIL_PARSER_RULE_
#define _UTIL_PARSER_RULE_

#include <string>
#include <memory>
#include <utility>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class rule : public base_rule {
			private:
				std::shared_ptr< std::shared_ptr<base_rule> > the_rule;

			public:	
				rule(std::shared_ptr<base_rule> a_rule = std::shared_ptr<base_rule>()) : the_rule(new std::shared_ptr<base_rule>(a_rule)) {}

				void set_rule(std::shared_ptr<base_rule> a_rule) {
					*the_rule = a_rule;
				}

				std::shared_ptr<base_rule> get_rule() {return *the_rule;}

				bool test(match_range &context, match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new rule(*this));
				}

				rule &operator <<=(base_rule const &rhs);
		};

		rule operator <<(base_rule const &first, base_rule const &second);
		rule operator |(base_rule const &first, base_rule const &second);
		rule operator !(base_rule const &optional_rule);
		rule operator +(base_rule const &repeated_rule);
		rule operator *(base_rule const &repeated_rule);
		rule operator -(base_rule const &a_rule);
		rule operator ~(base_rule const &a_rule); //whitespace - new_line
	}
}

#endif // _UTIL_PARSER_RULE_

