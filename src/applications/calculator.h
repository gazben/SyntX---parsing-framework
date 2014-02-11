#ifndef _APPLICATIONS_CALCULATOR_
#define _APPLICATIONS_CALCULATOR_

#include <stack>
#include <string>
#include <exception>

#include <util/parser/parser.h>

using namespace util::parser;

namespace applications {
	class calculator {
		private:	
			struct evaluate {
				class empty_stack : public std::exception {
					public:
						~empty_stack() throw() {}

						char const *what() const throw();
				};

				std::stack<int> &numbers;
				std::stack<char> &operations;

				evaluate(std::stack<int> &numbers, std::stack<char> &operations) :
					numbers(numbers), operations(operations) {}

				void operator()(std::string const &);
			};

			rule sum, product, multiplicand, group;
			std::stack<int> numbers;
			std::stack<char> operations;

		public:
			calculator();
			bool calculate(std::string const &expression, int &result);
	};
}

#endif // _APPLICATIONS_CALCULATOR_
