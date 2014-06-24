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

#ifndef _UTIL_PARSER_BASERULE_
#define _UTIL_PARSER_BASERULE_

#include <string>
#include <memory>
#include <utility>
#include <functional>

namespace util {
	namespace parser {
		/**
		 * The base class of the rules.
		 * The operation to be done when there is a match are defined in this class.
		 */
		class base_rule {
			public:
				using semantic_action = std::function<void(std::string const &)>; /**< The function type of semantic actions. */
				using match_range = std::pair< std::string::const_iterator, std::string::const_iterator >; /**< The type of ranges representing match results and ranges to match. */

			private:
				semantic_action the_semantic_action; /**< The semantic action assigned to this rule. */

			public:
				/**
				 * Destructor.
				 */
				virtual ~base_rule() {}

				/**
				 * The virtual method that defines the conditions of matching.
				 * This method is defined by every descendent of the @ref base_rule class.
				 * @param context the range to be matched (the first iterator is incremented if the rule matches, 
				 * the second points to the end of the text)
				 * @param the_match_range the beginning and end of the matched range -- this variable
				 * is only altered if there is a match
				 * @return true if there is a match
				 * @note This method may throw an exception (\ref rule::test throws \ref rule::undefined_rule).
				 */
				virtual bool test(match_range &context, match_range &the_match_range) = 0;

				/**
				 * Contains the operations performed when a rule is tried on the current position.
				 * The method first tries to apply the rule at the current position using the virtual
				 * \ref test method. If there is a match, the_match_range is set to represent the
				 * range consumed by the rule and \ref the_semantic_action is called (if one has been
				 * assigned to this rule).
				 * @param context the range to be matched
				 * @param the_match_range the consumed range
				 * @return true if there was a match
				 */
				bool match(match_range &context, match_range &the_match_range);

				/**
				 * Assigns a \ref semantic_action to the rule.
				 * @param a_semantic_action the \ref semantic_action to be assigned to the rule
				 * @return reference of the rule
				 */
				base_rule &operator[](semantic_action const &a_semantic_action);

				/**
				 * Returns a dynamically allocated copy of this object as base_rule pointer.
				 * @return a dynamically allocated copy of this object as base_rule pointer
				 */
				virtual std::shared_ptr<base_rule> clone() const = 0;

				/**
				 * Reads the contents of a text file to a std::string.
				 * @param filename the file to be read
				 * @param the_contents the std::string to be filled
				 * @return true if the operation was successful
				 */
				static bool file_to_string(std::string const &filename, std::string &the_contents);
		};
	}
}

#endif // _UTIL_PARSER_BASERULE_
