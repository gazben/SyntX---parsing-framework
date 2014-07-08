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
		bool rule::test(match_range &context, match_range &the_match_range, std::shared_ptr<base_rule::node> &ast_root) {
			if (!(*the_rule)) throw undefined_rule();
			return (*the_rule)->match(context, the_match_range, ast_root);
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
