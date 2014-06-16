/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2013, Gergely Nagy
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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

