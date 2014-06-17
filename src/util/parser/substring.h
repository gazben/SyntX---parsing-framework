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

#ifndef _UTIL_PARSER_SUBSTRING_
#define _UTIL_PARSER_SUBSTRING_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		/**
		 * Rule that tries to match the given word from the current position.
		 * This rule will match even if the given word is in the middle of a word, so
		 * it matches a substring of a word.
		 * @note This rule has nothing to do with a string literal -- those are matched
		 * by \ref string.
		 */
		class substring : public base_rule {
			private:
				std::string the_word; /**< The string to be matched. */

			public:
				/**
				 * Constructor.
				 * @param the_word the string to be matched
				 */
				substring(std::string const &the_word) : the_word(the_word) {}

				/**
				 * @copydoc util::parser::base_rule::test
				 */
				virtual bool test(base_rule::match_range &context, base_rule::match_range &the_match_range) override;

				/**
				 * @copydoc util::parser::base_rule::clone
				 */
				virtual std::shared_ptr<base_rule> clone() const override {
					return std::shared_ptr<base_rule>(new substring(*this));
				}
		};
	}
}

#endif //_UTIL_PARSER_SUBSTRING_

