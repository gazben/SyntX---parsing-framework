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

#include <tuple>
#include <sstream>

#include <util/parser/range.h>
#include <util/parser/character.h>
#include <util/parser/keyword.h>

namespace util {
	namespace parser {
		bool keyword::test(base_rule::match_range &context, base_rule::match_range &the_match_range, std::shared_ptr<base_rule::node> &ast_root) {
			if (context.first == context.second) return false;

			base_rule::match_range local_context = context;
			base_rule::match_range a_range;

			range lower('a', 'z'), upper('A', 'Z'), numeric('0', '9');
			character extra(extra_characters);

			base_rule::match_range word_range(the_word.begin(), the_word.end());

			while (word_range.first != word_range.second && local_context.first != context.second && *word_range.first == *local_context.first) {
				++word_range.first;
				++local_context.first;
			}

			if (word_range.first == word_range.second && 
				!(
					lower.match(local_context, a_range) || upper.match(local_context, a_range) || 
					numeric.match(local_context, a_range) || extra.match(local_context, a_range)
				)
					
			) {
				the_match_range.first = context.first;
				the_match_range.second = local_context.first;
				context = local_context;

				if (get_build_ast()) ast_root = std::make_shared<base_rule::node>(std::string(the_match_range.first, the_match_range.second)); 

				return true;
			}
			else return false;
		}

		void keyword::insert_failure_entry(std::string::const_iterator const &position) const {
			std::stringstream stream;
			stream << "the keyword: " << the_word; 
			failure_log.insert(std::make_tuple(position, stream.str()));	
		}
	}
}
