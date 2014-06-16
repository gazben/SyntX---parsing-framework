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

#ifndef _APPLICATIONS_SYMBOLICEXPRESSION_
#define _APPLICATIONS_SYMBOLICEXPRESSION_

#include <string>
#include <vector>

#include <util/parser/parser.h>

namespace applications {
	class symbolic_expression {
		public:
			struct tree_node {
				std::string value;
				tree_node *parent;
				std::vector<tree_node *> children;

				tree_node(std::string const &value = "", tree_node *parent = nullptr) :
					value(value),
					parent(parent) {}

				tree_node *add_child(std::string const &value) {
					tree_node *new_child = new tree_node(value, this);
					children.push_back(new_child);
					return new_child;
				}

				~tree_node() {
					for (tree_node *node : children) {
						delete node;
					}
				}
			};

		private:
			tree_node root;
			util::parser::rule expression;

		public:
			symbolic_expression();

			bool test(std::string const &text);

			tree_node &get_root() {return root;}
	};
}

#endif // _APPLICATIONS_SYMBOLICEXPRESSION_
