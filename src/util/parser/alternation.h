#ifndef _UTIL_PARSER_ALTERNATION_
#define _UTIL_PARSER_ALTERNATION_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		/**
		 * An alternation of two rules matches either the first or the second.
		 */
		class alternation : public base_rule {
			private:
				std::shared_ptr<base_rule> first; /**< Pointer to the first rule. */
				std::shared_ptr<base_rule> second; /**< Pointer to the second rule. */

			public:
				/**
				 * Constructor.
				 * @param first pointer to the first rule
				 * @param second pointer to the second rule
				 */
				alternation(base_rule const &first, base_rule const &second) : first(first.clone()), second(second.clone()) {}


				/**
				 * @copydoc util::parser::base_rule::test
				 */
				virtual bool test(base_rule::match_range &context, base_rule::match_range &the_match_range); /* @copydoc util::parser::base_rule */

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new alternation(*this));
				}
		};
	}
}

#endif // _UTIL_PARSER_ALTERNATION_
