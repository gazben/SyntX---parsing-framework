#include <iostream>
#include <string>

#include <applications/lookahead.h>

int main() {
	std::string for_loops[] = {
		"for ( int i = 5; i < 6; ++i)",
		"for ( int i : my_vector)",
		"for(char i=5;i<6;++i)",
		"for(unsigned i : a_random_container)"
	};

	applications::lookahead lookahead;

	for (auto &text : for_loops) {
		std::string result;
		if (lookahead.test(text, result)) {
			std::cout << " matched: " << result << std::endl;
		}
		else std::cout << "Didn't match." << std::endl;
	}


	return 0;
}
