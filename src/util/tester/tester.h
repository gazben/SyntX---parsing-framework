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
