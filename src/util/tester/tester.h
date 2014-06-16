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

#ifndef _UTIL_TESTER_TESTER_
#define _UTIL_TESTER_TESTER_

#include <string>
#include <vector>

namespace util {
	namespace tester {
		/**
		 * Testing utility class.
		 */
		class tester {
			public:
				typedef bool(*test_function)(); /**< The type of the test functions. */

			private:
				std::string file_name; /**< The name of the file containing the tests. */
				std::vector<test_function> tests; /**< The vector that contains the test functions. */

			public:
				/**
				 * The contrcutor that needs the name of the file containing the tests.
				 * @param file_name the name of the files containing the tests
				 */
				tester(std::string const &file_name) : file_name(file_name) {}
				/**
				 * Adds a new function to the container.
				 * @param f pointer to the new function
				 */
				void add(test_function f) {
					tests.push_back(f);
				}

				/**
				 * Runs the tests.
				 * @return the number of failed tests
				 */
				unsigned run() const;
		};
	}
}

#endif // _UTIL_TESTER_TESTER_
