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

#ifndef _APPLICATIONS_CALCULATOR_
#define _APPLICATIONS_CALCULATOR_

#include <stack>
#include <string>
#include <exception>

#include <util/parser/parser.h>

using namespace util::parser;

namespace applications {
	/**
	 * Example grammar demonstrating the use of the SyntX framework realizing a simple calculator.
	 */
	class calculator {
		private:	
			/**
			 * Helper class for the processing the expressions using two stacks, one for the numbers and one for the operations. 
			 */
			struct evaluate {
				/**
				 * Exception thrown when a pop is performed on an empty stack.
				 */
				class empty_stack : public std::exception {
					public:
						/**
						 * Destructor.
						 */
						~empty_stack() noexcept {}

						/**
						 * Yields the error message of the exception.
						 * @return the error message of the exception.
						 */
						char const *what() const noexcept;
				};

				std::stack<int> &numbers;		/**< The reference of the stack containing the numbers. */
				std::stack<char> &operations;	/**< The reference of the stack containing the operations. */

				/**
				 * Constructor.
				 * @param numbers the stack containing the numbers
				 * @param operations the stack containing the operations
				 */
				evaluate(std::stack<int> &numbers, std::stack<char> &operations) :
					numbers(numbers), operations(operations) {}

				/**
				 * Function call operator performing the calculations.
				 * This is needed as the \ref evaluate struct is used as an
				 * action handler.
				 */
				void operator()(std::string const &);
			};

			rule sum;						/**< Rule representing a sum. */
			rule product;					/**< Rule representing a product. */
			rule multiplicand;				/**< Rule representing a multiplicand. */
			rule group;						/**< Rule representing a group. */
			std::stack<int> numbers;		/**< The stack containing the numbers. */
			std::stack<char> operations;	/**< The stack containing the operations. */


		public:
			/**
			 * Constructor.
			 * Defines and builds the grammar.
			 */
			calculator();

			/**
			 * Processes an expression and returns the result.
			 * @param expression the expression to process
			 * @param result reference of the variable to which the result is written
			 * @return true if the expression was correct and could be processed
			 */
			bool calculate(std::string const &expression, int &result);
	};
}

#endif // _APPLICATIONS_CALCULATOR_
