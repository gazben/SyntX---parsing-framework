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

#include <fstream>
#include <cmath>

#include <util/parser/parser.h>

using namespace util::parser;

class ast_tree_svg_printer{
  private:
    std::shared_ptr<base_rule::node> root;
    size_t svg_width = 0;
    size_t svg_height = 0;
    std::string svg_file_content;

    size_t count_depth(std::shared_ptr<base_rule::node> const &node, size_t depth = 0){
        static size_t max_depth = 0;

        if( depth > max_depth)
            max_depth = depth;

        for(auto &a_node: node->children){
            count_depth(a_node, depth + 1);
        }

        return max_depth;
    }

    bool isLeaf(std::shared_ptr<base_rule::node> const &node){
        return (node->children.size() == 0)? true : false;
    }

    void create_svg(std::shared_ptr<base_rule::node> const &node, size_t depth, size_t level_pos = 1){
        if(node) {
            //TEXT
            std::string text;
            switch (node->the_type) {
                case base_rule::node::type::value:
                    text = node->the_value;
                    break;
                case base_rule::node::type::alternation:
                    text = "alternation";
                    break;
                case base_rule::node::type::concatenation:
                    text = "concatenation";
                    break;
                case base_rule::node::type::option:
                    text = "option";
                    break;
                case base_rule::node::type::repetition:
                    text = "repetition";
                    break;
                case base_rule::node::type::repetition_or_epsilon:
                    text = "repetition_or_epsilon";
                    break;
                case base_rule::node::type::named_rule:
                    text = "named_rule: " + node->the_value;
                    break;
            }
            //POSITION
            size_t x_pos;
            size_t y_pos;

            size_t offset = level_pos;
            if(offset % 2 == 0 )
                offset +=1;

            x_pos = ((svg_width / (std::pow(2, depth + 1))) * offset);
            y_pos = depth * 120 + 70;

            //SYMBOL
            svg_file_content +=
                    "<ellipse cx=\"" +
                    std::to_string(x_pos + (text.length() * 3.4)) +
                    "\" cy=\"" +
                    std::to_string(y_pos) +
                    "\" rx=\""+ std::to_string( 50 + text.length() * 1.6 ) + "\" ry=\"35\" " +
                    "style=\""
                            "stroke:#ff0000;stroke-width: 2;stroke: black;fill: none;\"/>";
            svg_file_content += "<text x=\"" + std::to_string(x_pos) + "\" y=\"" + std::to_string(y_pos) + "\"" + " fill=\"black\">";
            //svg_file_content += std::to_string(level_pos) + "</text>";
            svg_file_content += text + "</text>";
            svg_file_content += "\n";

            for (unsigned int i = 0; i < node->children.size(); i++){
                size_t temp_level_pos = level_pos * 2;
                if(i == 0)
                    temp_level_pos--;
                else
                    temp_level_pos++;
                create_svg(node->children[i], depth + 1, temp_level_pos);
            }
        }
    }
public:
    void write_svg(std::shared_ptr<base_rule::node> const &node, std::string path = "ast.html"){
        using namespace std;
        root = node;

        size_t depth = count_depth(root);
        svg_width = pow(2, depth)* 80;
        svg_height =  depth * 150 + 70;

        create_svg(root, 0);

        ofstream svg_file;
        svg_file.open(path);

        //svg_file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
        svg_file << "<html><head></head><body>" << endl;
        svg_file << "<svg width=\"" << to_string(svg_width) << "\"  " << "height=\"" << to_string(svg_height) << "\">" << std::endl;

        svg_file << svg_file_content << endl;

        svg_file << "</svg>" << endl;
        svg_file << "</body></html>";
        svg_file.close();

        cout << "SVG_Height: " << svg_height << endl;
        cout << "SVG_Width: " << svg_width << endl;
        cout << "AST_depth: " << depth << endl;
    }
};

void parse_tree(std::shared_ptr<base_rule::node> const &node, size_t depth = 0) {
    if (node) {

        for (size_t i = 0; i < depth; ++i) std::cout << "   ";

        switch (node->the_type) {
            case base_rule::node::type::value:
                std::cout << node->the_value << std::endl;
                break;

            case base_rule::node::type::alternation:
                std::cout << "alternation" << std::endl;
                break;

            case base_rule::node::type::concatenation:
                std::cout << "concatenation" << std::endl;
                break;

            case base_rule::node::type::option:
                std::cout << "option" << std::endl;
                break;

            case base_rule::node::type::repetition:
                std::cout << "repetition" << std::endl;
                break;

            case base_rule::node::type::repetition_or_epsilon:
                std::cout << "repetition_or_epsilon" << std::endl;
                break;

            case base_rule::node::type::named_rule:
                std::cout << "named_rule: " << node->the_value << std::endl;
                break;
        }

        for (auto &a_node: node->children)
            parse_tree(a_node, depth + 1);
    }

}

int main() {
    base_rule::set_build_ast(true);

    rule addition, addend("addend"), expression;

    addition <<= -addend << *(-character("+") << -addend);
    addend <<= -range('0', '9') | -expression;
    expression <<= -character("(") << -addition << -character(")");

    std::string input = "2 + 3 + 4\n";
    base_rule::match_range context(input.cbegin(), input.cend());
    base_rule::match_range result;
    std::shared_ptr<base_rule::node> root;

    if (addition.match(context, result, root)) {
        std::cout << "Matched: " << std::string(result.first, result.second) << std::endl;
        parse_tree(root);

        ast_tree_svg_printer printer;
        printer.write_svg(root);
    } else {
        std::cout << "Didn't match" << std::endl;
    }
}

