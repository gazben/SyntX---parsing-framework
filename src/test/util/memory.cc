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

#include <memory>
#include <iostream>

#include <util/tester/tester.h>

class test_class {
	private:
		int id;
		static int class_id;
		int *external;

	public:
		test_class(int &external) : id(class_id++), external(&external) {}

		~test_class() {
			std::cout << "~test_class(" << id << ")" << std::endl;
			*external -= 1;
		}

		int get_id() const {return id;}
};

int test_class::class_id = 0;

bool test_0() {
	int flag = 1;
	{
		std::shared_ptr<test_class> test_pointer_1(new test_class(flag));
		std::shared_ptr<test_class> test_pointer_2 = test_pointer_1;
		std::shared_ptr<test_class> test_pointer_3 = test_pointer_1;
		
		std::cout << test_pointer_1->get_id() << std::endl;
		std::cout << test_pointer_2->get_id() << std::endl;
		std::cout << test_pointer_3->get_id() << std::endl;
	}

	return flag == 0;
}

bool test_1() {
	std::shared_ptr<int> test(0);

	if (!test) {
		test.reset(new int(2));
		std::cout << *test << std::endl;
		return *test == 2;
	}
	else return false;
}

int main() {
	util::tester::tester the_tester(__FILE__);

	the_tester.add(test_0);
	the_tester.add(test_1);

	return the_tester.run();
}
