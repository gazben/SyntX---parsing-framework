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
	/**
	 * Example grammar demonstrating the use of the SyntX framework realizing a converter from the Spice Raw format to CSV (comma seperated values).
	 */
	class spice_raw_to_csv {
		private:
			util::parser::rule title;						/**< Rule that represents a title. */
			util::parser::rule date;						/**< Rule that represents a date. */
			util::parser::rule plotname;					/**< Rule that represents a plotname. */
			util::parser::rule flags;						/**< Rule that represents flags. */
			util::parser::rule variable_no;					/**< Rule that represents a variable number expression. */
			util::parser::rule points;						/**< Rule that represents points. */
			util::parser::rule variables;					/**< Rule that represents a variable list. */
			util::parser::rule variable_definition;			/**< Rule that represents variable definition. */
			util::parser::rule values;						/**< Rule that represents values. */
			util::parser::rule value_item;					/**< Rule that represents a value item. */
			util::parser::rule sentence;					/**< Rule that represents the entire Spice Raw file. */

			std::vector<std::string> the_variable_names;	/**< Container holding the variable names. */
			std::vector< std::vector<double> > the_values;	/**< Container hoolding the values. */

			size_t number_of_variables;						/**< The number of variables. */
			size_t number_of_points;						/**< The number of points. */
			size_t index;									/**< The index. */
			std::string name;								/**< The name of the plot. */
			std::string type;								/**< The type of the plot. */
			double a_value;									/**< A value. */
			char delimiter;									/**< Delimiter to be used in the CSV file. */

		public:
			/** 
		  	 * Constructor.
			 * @param delimiter the delimiter to be used in the CSV file
			 * Defines and builds the grammar.
			 */
			spice_raw_to_csv(char delimiter);

			/**
			 * Parses a file and processes the Spice Raw plot inside.
			 * @param filename the name of the file to be processed
			 * @return true if the file was correct and could be processed
			 */
			bool parse(std::string const &filename);
	};
}

#endif // _APPLICATIONS_SPICERAWTOCSV_

