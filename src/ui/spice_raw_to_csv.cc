#include <string>
#include <iostream>

#include <applications/spice_raw_to_csv.h>

enum return_value {ok, invalid_arguments, parsing_error};

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <spice raw file>" << std::endl;
		return invalid_arguments;
	}

	applications::spice_raw_to_csv sptc(';');

	if (sptc.parse(argv[1])) {
		std::cout << "Output saved to csv file." << std::endl;
		return ok;
	}
	else {
		std::cout << "A parsing error occured." << std::endl;
		return parsing_error;
	}

	return 0;
}

