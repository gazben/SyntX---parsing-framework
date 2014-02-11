#include <fstream>
#include <iterator>
#include <algorithm>

#include <util/parser/base_rule.h>

namespace util {
	namespace parser {
		bool base_rule::match(match_range &context, match_range &the_match_range) {
			match_range a_range;

			if (test(context, a_range)) {
				the_match_range.first = a_range.first;
				the_match_range.second = a_range.second;

				if (the_semantic_action) {
					std::string the_matched_substring(the_match_range.first, the_match_range.second);
					the_semantic_action(the_matched_substring);
				}

				return true;
			}
			else return false;
		}

		base_rule &base_rule::operator[](semantic_action const &a_semantic_action) {
			the_semantic_action = a_semantic_action;
			return *this;
		}

		bool base_rule::file_to_string(std::string const &filename, std::string &the_contents) {
			std::fstream source(filename, std::ios::in);

			if (!source) return false;

			source >> std::noskipws;

			source.seekg (0, source.end);
			size_t length = source.tellg();
			source.seekg (0, source.beg);

			the_contents.reserve(length);
			std::copy(
					std::istream_iterator<char>(source),
					std::istream_iterator<char>(),
					std::inserter(
						the_contents,
						the_contents.end()
						)
					);

			return true;
		}
	}
}
