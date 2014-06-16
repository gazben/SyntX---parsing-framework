/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2013, Gergely Nagy
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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

