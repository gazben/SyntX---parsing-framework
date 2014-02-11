#ifndef _UTIL_PARSER_DEBUGACTION_
#define _UTIL_PARSER_DEBUGACTION_

#include <string>
#include <iostream>

namespace util {
	namespace parser {
		class debug_action {
			private:
				std::string text_before;
				std::string text_after;
				std::ostream &stream;

			public:
				debug_action(std::string const &text_before = "", std::string const &text_after = "", std::ostream &stream = std::cout) :
					text_before(text_before),
					text_after(text_after),
					stream(stream) {}

				void operator()(std::string const &match) {
					stream << text_before << match << text_after;
				}
		};
	}
}
#endif // _UTIL_PARSER_DEBUGACTION_
