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

#include <cctype>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		std::shared_ptr<base_rule::node> base_rule::dont_build_ast;
		bool base_rule::build_ast = false;
		std::set<std::tuple<std::string::const_iterator, std::string>> base_rule::failure_log;

		bool base_rule::match(match_range &context, match_range &the_match_range, std::shared_ptr<node> &ast_root) {
			match_range a_range;

			if (test(context, a_range, ast_root)) {
				the_match_range = a_range;

				if (the_semantic_action) {
					std::string the_matched_substring(the_match_range.first, the_match_range.second);
					the_semantic_action(the_matched_substring);
				}

				return true;
			}
			else {
				insert_failure_entry(context.first);
				return false;
			}
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
		
		char const *base_rule::empty_failure_log::what() const noexcept {
			return "The failure log is empty.";
		}

		std::string base_rule::get_error_message(match_range const &context) {
			if (failure_log.empty()) return "";

			auto error_entry = get_failure_cause();	
			
			size_t characters_before = 0;
			std::string::const_iterator i_before = std::get<0>(error_entry);
			std::string::const_iterator i_after = std::get<0>(error_entry);

			while (i_before > context.first && *i_before != '\n') {++characters_before; --i_before;}
			while (i_after < context.second && *i_after != '\n') ++i_after;

			std::stringstream message;

			message << "An error occured here:" << std::endl;
			message << std::string(i_before, i_after) << std::endl;

			for (size_t i = 0; i < characters_before; ++i) {
				char current = i_before[i];
				if (std::isspace(current) && current != '\n') message << current;
				else message << " ";
			}

			message << "^" << std::endl << "The parser was expecting " << std::get<1>(error_entry);

			return message.str();
		}
		
		std::tuple<std::string::const_iterator, std::string> const &base_rule::get_failure_cause() {
			if (failure_log.empty()) throw empty_failure_log();
			return *failure_log.crbegin();
		}

	}
}
