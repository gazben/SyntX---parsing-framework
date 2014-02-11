#ifndef _APPLICATIONS_SPICERAWTOCSV_
#define _APPLICATIONS_SPICERAWTOCSV_

#include <string>
#include <vector>

#include <util/parser/parser.h>

namespace applications {
	class spice_raw_to_csv {
		private:
			util::parser::rule title;
			util::parser::rule date;
			util::parser::rule plotname;
			util::parser::rule flags;
			util::parser::rule variable_no;
			util::parser::rule points;
			util::parser::rule variables; 
			util::parser::rule variable_definition;
			util::parser::rule values;
			util::parser::rule value_item;
			util::parser::rule sentence;

			std::vector<std::string> the_variable_names;
			std::vector< std::vector<double> > the_values;

			size_t number_of_variables;
			size_t number_of_points;
			size_t index;
			std::string name, type;
			double a_value; 

			char delimiter;

		public:
			spice_raw_to_csv(char delimiter);

			bool parse(std::string const &filename);
	};
}

#endif // _APPLICATIONS_SPICERAWTOCSV_

