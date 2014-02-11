#include <fstream>
#include <sstream>
#include <iomanip>

#include <applications/spice_raw_to_csv.h>

namespace applications {
	spice_raw_to_csv::spice_raw_to_csv(char delimiter) : delimiter(delimiter) {
		using namespace util::parser;

		title <<= -keyword("Title:", ":") << *~identifier() << ~eol();

		date <<= 
				~keyword("Date:", ":") 
			<<	~identifier()
			<<	~identifier()
			<<	~integer()
			<<	~+range('0', '9') 
			<<	character(":")
			<<	+range('0', '9')
			<<	character(":")
			<<	+range('0', '9')
			<<	~integer()
			<<	~eol();

		plotname <<= ~keyword("Plotname:", ":")	<<	+~identifier() << ~eol();

		flags <<= ~keyword("Flags:", ":") << +~identifier() << ~eol();
		
		variable_no <<=
				~keyword("No. Variables:", ":")
			<< ~integer()[(
					[this](std::string const &value) {
						std::stringstream stream(value);
						stream >> number_of_variables;
						the_variable_names.resize(number_of_variables);
					}
				)]
			<< ~eol();
		
		points <<=
				~keyword("No. Points:", ":")
			<< ~integer()[(
					[this](std::string const &value) {
						std::stringstream stream(value);
						stream >> number_of_points;
						the_values.resize(number_of_points);
					}
				)]
			<< ~eol();
		
		variable_definition <<=
				~integer()[(
					[this](std::string const &value) {
						std::stringstream stream(value);
						stream >> index; 
					}
				)]
			<<	~identifier("_()-")[(
					[this](std::string const &value) {
						name = value;
					}
				)]
			<<	~identifier("_()")[(
					[this](std::string const &value) {
						type = value;
					}
				)]
			<<	~eol()[(
				[this](std::string const &) {
					std::stringstream stream;

					stream << name;

					if (type == "time") stream << " [s]";
					else if (type == "voltage") stream << " [V]";
					else if (type == "current") stream << " [A]";

					the_variable_names[index] = stream.str();
				}
			)];
		
		variables <<= ~keyword("Variables:", ":") << ~eol() << *variable_definition;
		
		value_item <<=
				~integer()[(
					[this](std::string const &value) {
						std::stringstream stream(value);
						stream >> index; 
					}
				)]

			<< *(
						~real()[(
							[this](std::string const &value) {
								std::stringstream stream(value);
								stream >> a_value;
								the_values[index].push_back(a_value);
							}
						)]
					<<	~eol()
				);
		
		values <<= ~keyword("Values:") << ~eol() << *(value_item << ~eol());

		sentence <<= title << date << plotname << flags << variable_no << points << variables << values << -epsilon();
	}

	bool spice_raw_to_csv::parse(std::string const &filename) {
		std::string contents;

		if (!util::parser::base_rule::file_to_string(filename, contents)) return false;

		util::parser::base_rule::match_range i(contents.begin(), contents.end());
		util::parser::base_rule::match_range a_range;
		if (sentence.match(i, a_range)) {
			/* //DEBUG PRINT//
			std::string s(a_range.first, a_range.second);
			std::cout << "Match: " << s << std::endl;
			std::cout << "number_of_variables: " << number_of_variables << std::endl;
			std::cout << "number_of_points: " << number_of_points << std::endl;
			for (auto variable : the_variable_names) std::cout << variable << std::endl;

			size_t i = 0;
			for (auto values : the_values) {
				std::cout << i++ << "\t";
				for (auto value : values) {
					std::cout << "\t" << std::setprecision(16) << value;
				}
				std::cout << std::endl;
			}
			*/
			if (a_range.second != contents.end()) std::cerr << "Not a full match!" << std::endl;

			std::stringstream stream;
			stream << filename << ".csv";

			std::fstream file(stream.str().c_str(), std::ios::out);
			bool first_element = true;

			for (auto variable : the_variable_names) {
				if (first_element) first_element = false;
				else file << delimiter << "\t";
				file << variable;
			}
			file << std::endl;


			for (auto values : the_values) {
				first_element = true;
				for (auto value : values) {
					if (first_element) first_element = false;
					else file << delimiter << "\t";
					file << std::setprecision(16) << value;
				}
				file << std::endl;
			}

			file.close();
			return true;
		}
		else {
			std::cout << "Did not match" << std::endl;
			return false;
		}
	}

}
