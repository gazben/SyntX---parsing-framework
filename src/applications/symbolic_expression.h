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
