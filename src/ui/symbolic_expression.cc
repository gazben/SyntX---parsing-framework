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

#include <string>
#include <iostream>

#include <util/parser/parser.h>
#include <applications/symbolic_expression.h>

enum error_code {OK, FILE_NOT_FOUND, DIDNT_MATCH};

void print_tree(applications::symbolic_expression::tree_node &root, std::ostream &stream = std::cout) {
	stream << root.value << std::endl;

	for (auto p : root.children) {
		print_tree(*p, stream);
	}
}

int main() {
	std::string contents;

	if (!util::parser::base_rule::file_to_string("test_data/se.tt", contents)) return FILE_NOT_FOUND;

	applications::symbolic_expression se;

	if (se.test(contents)) {
		print_tree(se.get_root());
		return OK;

	}
	else return DIDNT_MATCH;
	
	return OK;
}
