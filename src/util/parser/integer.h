#ifndef _UTIL_PARSER_INTEGER_
#define _UTIL_PARSER_INTEGER_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		class integer : public base_rule {
			public:
				/**
				 * The type of the integer: signed or unsigned.
				 */
				enum integer_type {
					signed_int, /**< The type that represents signed integers. */
					unsigned_int /**< The type that represents unsigned integers. */
				};

			private:
				integer_type the_integer_type; /**< The integer type. */

			public:
				integer(integer_type the_integer_type = signed_int) : the_integer_type(the_integer_type) {}

				bool test(base_rule::match_range &context, base_rule::match_range &the_match_range);

				virtual std::shared_ptr<base_rule> clone() const {
					return std::shared_ptr<base_rule>(new integer(*this));
				}
		};
	}
}

#endif //_UTIL_PARSER_INTEGER_
