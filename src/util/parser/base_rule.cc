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

#include <fstream>
#include <iterator>
#include <algorithm>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		bool base_rule::match(match_range &context, match_range &the_match_range) {
			match_range a_range;

			if (test(context, a_range)) {
				the_match_range = a_range;

				if (the_semantic_action) {
					std::string the_matched_substring(the_match_range.first, the_match_range.second);
					the_semantic_action(the_matched_substring);
				}

				return true;
			}
			else return false;
		}

		base_rule &base_rule::operator[](semantic_action const &a_semantic_action) {
			the_semantic_action = a_semantic_action;
			return *this;
		}

		bool base_rule::file_to_string(std::string const &filename, std::string &the_contents) {
			std::fstream source(filename, std::ios::in);

			if (!source) return false;

			source >> std::noskipws;

			source.seekg (0, source.end);
			size_t length = source.tellg();
			source.seekg (0, source.beg);

			the_contents.reserve(length);
			std::copy(
					std::istream_iterator<char>(source),
					std::istream_iterator<char>(),
					std::inserter(
						the_contents,
						the_contents.end()
						)
					);

			return true;
		}
	}
}
