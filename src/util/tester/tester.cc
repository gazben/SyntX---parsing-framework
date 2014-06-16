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

#include <iostream>
#include <util/tester/tester.h>

namespace util {
	namespace tester {
		unsigned tester::run() const {
			unsigned i, errors = 0, size = tests.size();
			char const * const single_line = "----------------------------------------------------------------------";
			char const * const double_line = "======================================================================";

			std::cerr << double_line << std::endl;
			std::cerr << " Running tests in " << file_name << std::endl;
			std::cerr << double_line << std::endl;

			for (i = 0; i < size; ++i) {
				std::cerr << single_line << std::endl;
				std::cerr << " Running test " << i << std::endl;
				std::cerr << single_line << std::endl;
				
				if (tests[i]()) {
					std::cerr << single_line << std::endl;
					std::cerr << " Test " << i << ": [OK]" << std::endl;
				}
				else {
					std::cerr << single_line << std::endl;
					std::cerr << " Test " << i << ": [FAILED]" << std::endl;
					++errors;
				}
				
				std::cerr << single_line << std::endl;
			}

			std::cerr << double_line << std::endl;
			std::cerr << " " << errors << ((errors > 1) ? " have" : " has") << " failed out of " << i << " test" << ((i > 1) ? "s " : " ") << "in " << file_name << std::endl;
			std::cerr << double_line << std::endl << std::endl;

			return errors;
		}
	}
}
