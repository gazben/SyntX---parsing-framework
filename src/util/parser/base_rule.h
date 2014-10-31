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

#include <set>
#include <tuple>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <exception>
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

				/**
				 * Represents a node of the AST (Abstract Syntax Tree) that is automatically built while parsing if \ref build_ast is set to true.
				 */
				struct node {
					/**
					 * The type of the node.
					 */
					enum class type {
						/**
						 * The node represents a value (a leaf in the AST).
						 */
						value, 
						/**
						 * The node represents an \ref util::parser::alternation -- its child is the alternative that matched.
						 */
						alternation,
						/**
						 * The node represents a \ref util::parser::concatenation -- its children are the two elements that appear one after the other.
						 */
						concatenation,
						/**
						 * The node represents an \ref util::parser::option -- its child is the optional element or a null pointer.
						 */
						option,
						/**
						 * The node represents a \ref util::parser::repetition -- its children are the elements of the type that is repeated.
						 */
						repetition,
						/**
						 * The node represents a \ref util::parser::repetition_or_epsilon -- its children are the elements of the type that is repeated or a null pointer.
						 */
						repetition_or_epsilon,
						/**
						 * A node representing a named rule.
						 */
						named_rule};

					type the_type; /**< The \ref util::parser::base_rule::node::type of the node. */
					std::string the_value; /**< The value of the node. */
					std::vector<std::shared_ptr<node>> children; /**< The children of the node. */

					/**
					 * Constructs a value node.
					 * @param a_value the value of the node
					 */
					node(std::string a_value) :	the_type(type::value), the_value(a_value) {}

					/**
					 * Constructs a node of the given type (tipically used for tyeps other than value).
					 * @param a_type the type of the node
					 */
					node(type a_type) :	the_type(a_type) {}
				};

				/**
				 * Exception thrown when \ref base_rule::get_failure_cause is called on an empty failure log.
				 */
				class empty_failure_log : public std::exception {
					public:
						/**
						 * Destructor.
						 */
						~empty_failure_log() noexcept {}

						/**
						 * Yields the error message of the exception.
						 * @return the error message of the exception.
						 */
						char const *what() const noexcept;
				};

			private:
				semantic_action the_semantic_action; /**< The semantic action assigned to this rule. */
				static bool build_ast; /**< Stores whether an AST is to be built. */

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
				 * @param ast_root the pointer to the root of the AST that is built by the rule
				 * @return true if there is a match
				 * @note This method may throw an exception (\ref rule::test throws \ref rule::undefined_rule).
				 */
				virtual bool test(match_range &context, match_range &the_match_range, std::shared_ptr<node> &ast_root = dont_build_ast) = 0;

				/**
				 * Contains the operations performed when a rule is tried on the current position.
				 * The method first tries to apply the rule at the current position using the virtual
				 * \ref test method. If there is a match, the_match_range is set to represent the
				 * range consumed by the rule and \ref the_semantic_action is called (if one has been
				 * assigned to this rule).
				 * @param context the range to be matched
				 * @param the_match_range the consumed range
				 * @param ast_root the pointer to the root of the AST that is built by the rule
				 * @return true if there was a match
				 */
				bool match(match_range &context, match_range &the_match_range, std::shared_ptr<node> &ast_root = dont_build_ast);

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

				/**
				 * Sets \ref build_ast that stores whether an AST is built during the parsing process.
				 * @param a_value the new value of \ref build_ast.
				 */
				static void set_build_ast(bool a_value) {build_ast = a_value;}

				/**
				 * Returns the current value of \ref build_ast.
				 * @return the current value of \ref build_ast
				 */
				static bool get_build_ast() {return build_ast;}

				/**
				 * Returns the failure log entry of the rule that reached farthest in the text.
				 * @return the failure log entry of the rule that reached farthest in the text
				 * @throw base_rule::empty_failure_log if the failure_log is empty
				 */
				static std::tuple<std::string::const_iterator, std::string> const &get_failure_cause();

				/**
				 * Generates an error message based on the failure log.
				 * @param context the bounds of the parsed text
				 * @note The parameter is needed as the bounds of the text
				 * are lost during the parsing process.
				 * @return an error message based on the failure log
				 */
				static std::string get_error_message(match_range const &context);

				/**
				 * Clears the \ref failure_log.
				 * @note This method has to be called between parses. The failure_log is a 
				 * static variable and rules simply write it, so entries from two subsequent
				 * parses could get mixed up causing trouble.
				 */
				static void clear_failure_log() {failure_log.clear();}

				/**
				 * Gets the \ref failure_log.
				 * @return the \ref failure_log
				 */
				static std::set<std::tuple<std::string::const_iterator, std::string>> const &get_failure_log() {
					return failure_log;
				}

			protected:
				/**
				 * Rules corresponding to terminal symbols enter data in the failure log if they fail to match.
				 * Only the terminal rules need to act so it is defined as an empty method so as not to
				 * litter the code of other rules.
				 * @param position the position where the rule failed
				 */
				virtual void insert_failure_entry(std::string::const_iterator const &position) const {}

			protected:
				static std::shared_ptr<node> dont_build_ast; /**< The default value of AST root (used when the tree is not built). */
				static std::set<std::tuple<std::string::const_iterator, std::string>> failure_log; /**< The log where terminal symbols enter data when they fail.*/
		};
	}
}

#endif // _UTIL_PARSER_BASERULE_
