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

#ifndef _UTIL_PARSER_IDENTIFIER_
#define _UTIL_PARSER_IDENTIFIER_

#include <memory>
#include <string>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		/**
		 * Rule that matches identifiers of a formal language.
		 * The rule will match a sequence of characters that doesn't contain
		 * whitespace, starts with either a small or a capital letter or one element
		 * of the set of extra characters given at construction and continues with
		 * small or capital letters, numbers or elements of the set of extra characters.
		 */
		class identifier : public base_rule {
			private:
				std::string extra_characters; /**< The set of extra characters that may be consumed by this rule. */

			public:
				/**
				 * Constructor.
				 * @param extra_characters the set of extra characters that may be consumed by this rule
				 */
				identifier(std::string const &extra_characters = "_") : extra_characters(extra_characters) {}

				/**
				 * @copydoc util::parser::base_rule::test
				 */
				virtual bool test(base_rule::match_range &context, base_rule::match_range &the_match_range, std::shared_ptr<base_rule::node> &ast_root = base_rule::dont_build_ast) override;

				/**
				 * @copydoc util::parser::base_rule::clone
				 */
				virtual std::shared_ptr<base_rule> clone() const override {
					return std::shared_ptr<base_rule>(new identifier(*this));
				}
		};
	}
}

#endif //_UTIL_PARSER_IDENTIFIER_

