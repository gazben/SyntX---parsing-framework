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

#include <util/parser/integer.h>
#include <util/parser/range.h>
#include <util/parser/character.h>

namespace util {
	namespace parser {
		bool integer::test(base_rule::match_range &context, match_range &the_match_range) {
			if (context.first == context.second) return false;

			base_rule::match_range local_context = context;
			base_rule::match_range a_range;
			range non_zero('1', '9'), numeric('0', '9');
			character neg_sign("-"), pos_sign("+"), zero("0");
			bool has_sign = false;

			if (the_integer_type == signed_int) has_sign = neg_sign.match(local_context, a_range);
			if (!has_sign) pos_sign.match(local_context, a_range);

			if (zero.match(local_context, a_range)) {
				the_match_range.first = context.first;
				the_match_range.second = a_range.second;
				context = local_context;

				return true;
			}
			else if (non_zero.match(local_context, a_range)) {
				while (numeric.match(local_context, a_range));

				the_match_range.first = context.first;
				the_match_range.second = a_range.second;
				context = local_context;

				return true;
			}

			return false;
		}
	}
}
