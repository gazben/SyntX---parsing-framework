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
	/**
	 * Example grammar demonstrating the use of the SyntX framework realizing a LISP-like <a href="http://en.wikipedia.org/wiki/S-expression">Symbolic Expression</a> parser.
	 */
	class symbolic_expression {
		public:
			/**
			 * Helper class representing a node in a tree data structure.
			 * The S-expression parser builds a parsing tree automatically in which the nodes
			 * are \ref tree_node objects.
			 */
			struct tree_node {
				std::string value;					/**< The value of the node. */
				tree_node *parent;					/**< The address of the parent node. */
				std::vector<tree_node *> children;	/**< Conatainer holding the addresses of this node's children. */

				/**
				 * Constructor.
				 * @param value the value of this node
				 * @param parent the address of this node's parent
				 */
				tree_node(std::string const &value = "", tree_node *parent = nullptr) :
					value(value),
					parent(parent) {}

				/**
				 * Adds a new child to the node.
				 * @param value the valu of the new child
				 * @return the address of the new child
				 */
				tree_node *add_child(std::string const &value) {
					tree_node *new_child = new tree_node(value, this);
					children.push_back(new_child);
					return new_child;
				}

				/**
				 * Destructor.
				 * Deletes the children of this node. Their
				 * destructors will delete their children and
				 * so on. The tree is recursively freed when the
				 * root node's destructor is executed.
				 */
				~tree_node() {
					for (tree_node *node : children) {
						delete node;
					}
				}
			};

		private:
			tree_node root;					/**< The root node of the tree. */
			tree_node *current_root;		/**< The position in the tree during parsing. */
			util::parser::rule expression;	/**< The rule that describes a generic symbolic expression. */

		public:
			/**
			 * Constructor.
			 * Defines and builds the grammar.
			 */
			symbolic_expression();

			/**
			 * Parses a string containing an arbitrarily complex symbolic expression and builds the parsing tree.
			 * @param text the symbolic expression
			 * @return true if the parsing was successful
			 */
			bool test(std::string const &text);

			/**
			 * Gets the root of the parsing tree.
			 * @return the root of the parsing tree
			 */
			tree_node &get_root() {return root;}
	};
}

#endif // _APPLICATIONS_SYMBOLICEXPRESSION_
