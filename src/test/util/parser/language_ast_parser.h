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

#ifndef _LANGUAGE_AST_PARSER_
#define _LANGUAGE_AST_PARSER_

#include <string>
#include <memory>
#include <iostream>

#include <util/parser/parser.h>

using namespace util::parser;

class language_ast_parser {
	private:
		rule program;
		rule for_loop;
		rule range_for;
		rule iterator_for;
		rule declaration;
		rule variable_type;
		rule type_modifier;
		rule variable_name;
		rule variable_value;
		rule container_name;
		rule logic_expression;
		rule expression;
		rule preincrement;
		rule postincrement;
		rule logic_operator;
		rule block;
		rule block_start;
		rule block_end;

	public:
		language_ast_parser();
		bool match(std::string const &text, std::string &result, std::shared_ptr<base_rule::node> &ast_root);
		void traverse_tree(std::shared_ptr<base_rule::node> a_node);
};

#endif // _LANGUAGE_AST_PARSER_

