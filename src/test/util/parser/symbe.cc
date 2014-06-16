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

#include <util/parser/parser.h>
#include <string>
#include <iostream>
#include <list>

using namespace util::parser;

struct tree_node {
	std::string value;
	tree_node *parent;
	std::list<tree_node> children;

	tree_node(std::string const &value = "", tree_node *parent = nullptr) :
		value(value),
		parent(parent) {}

	tree_node *add_child(std::string const &value) {
		children.push_back(tree_node(value, this));
		return &children.back();
	}

	tree_node *get_parent() const {
		return parent;
	}

	std::list<tree_node> &get_children() {
		return children;
	}
};

void print_tree(tree_node *root) {
	if (root == nullptr) return;

	std::cout << root->value << std::endl;

	for (auto &n: root->get_children()) {
		print_tree(&n);
	}
}

int main() {
	std::string text = "(a)    		\n";
	//std::string text = "(abcd 234 \"keyw\" (a 2 +) hjk (ab jk 234 (akl sjl) ) )";
	//std::string text = "(cd 23)";
	rule expression;
	base_rule::match_range context(text.begin(), text.end()), result;

	tree_node root;
	tree_node *current = &root;

	expression <<= 
		-character("(")[(
					[&](std::string const &){current = current->add_child("");}
					)]
		<<	+((
					-identifier()
					|	-integer()
					|	-string()
					|	-character("+-*/")
			  )[(
				  [&](std::string const &s){current->add_child(s);}
				)]
				|	-expression)
		<< -character(")")[(
			[&](std::string const &){current = current->parent;}
			)]
		<< -epsilon();

	if (expression.match(context, result) && text.end() == result.second) {
		std::cout << "OK" << std::endl;
		print_tree(&root);
	}
	else std::cout << "NOK" << std::endl;

	return 0;
}
