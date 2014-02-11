#ifndef _UTIL_PARSER_BASERULE_
#define _UTIL_PARSER_BASERULE_

#include <string>
#include <memory>
#include <utility>
#include <functional>

namespace util {
	namespace parser {
		class base_rule {
			public:
				using semantic_action = std::function<void(std::string const &)>;
				using match_range = std::pair< std::string::const_iterator, std::string::const_iterator >;

			private:
				semantic_action the_semantic_action;

			public:
				virtual ~base_rule() {}

				/**
				 * The virtual method that defines the conditions of matching.
				 * This method is defined by every descendent of the @ref base_rule class.
				 * @param context the range to be matched (the first iterator is incremented if the rule matches, 
				 * the second points to the end of the text)
				 * @param the_match_range the beginning and end of the matched range -- this variable
				 * is only altered if there is a match
				 * @return true if there is a match
				 */
				virtual bool test(match_range &context, match_range &the_match_range) = 0;

				bool match(match_range &context, match_range &the_match_range);

				base_rule &operator[](semantic_action const &a_semantic_action);

				virtual std::shared_ptr<base_rule> clone() const = 0;

				static bool file_to_string(std::string const &filename, std::string &the_contents);
		};
	}
}

#endif // _UTIL_PARSER_BASERULE_
