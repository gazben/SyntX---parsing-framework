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

#ifndef _APPLICATIONS_LOOKAHEAD_
#define _APPLICATIONS_LOOKAHEAD_

#include <string>

#include <util/parser/parser.h>

namespace applications {
	/**
	 * Example grammar demonstrating the use of the SyntX framework showing how an infinite look-ahead can be realized by the framework.
	 */
	class lookahead {
		private:
			util::parser::rule for_loop;			/**< Rule the represents a for loop of any type. */
			util::parser::rule range_for;			/**< Rule the represents a range-based for loop. */
			util::parser::rule iterator_for;		/**< Rule the represents an iterator for loop. */
			util::parser::rule declaration;			/**< Rule the represents a declaration. */
			util::parser::rule logic_expression;	/**< Rule the represents a logic expression. */
			util::parser::rule expression;			/**< Rule the represents an expression. */


		public:
			/**
			 * Constructor.
			 * Defines and builds the grammar.
			 */
			lookahead();

			/**
			 * Tests a piece of C++ code and determines whether it contains an iterator or a range-based for loop.
			 * @param text the text to process
			 * @param result reference of the variable to which the result is written
			 * @return true if the text was correct and could be processed
			 */
			bool test(std::string const &text, std::string &result);
	};
}
#endif // _APPLICATIONS_LOOKAHEAD_
