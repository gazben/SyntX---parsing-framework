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
