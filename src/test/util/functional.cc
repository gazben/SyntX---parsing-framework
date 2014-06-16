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
#include <functional>

#include <util/tester/tester.h>

struct my_functor {
	int &i;

	my_functor(int &i) : i(i) {}

	void operator()(std::string const &s) {
		i = s.size();
	}
};

struct my_host {
	std::function<void(std::string const &)> f;

	void operator[](std::function<void(std::string const &)> const &f) {
		this->f = f;
	}

	void do_something(std::string const &s) {
		if (f) f(s);
	}

};

bool test_0() {
	int i1, i2;
	std::string a_string("hello");

	my_host host1, host2, host3;

	host1[ ([&i1](std::string const &s){i1 = s.size();}) ];
	host2[my_functor(i2)];

	host1.do_something(a_string);
	host2.do_something(a_string);

	try {
		host3.do_something(a_string);
	} catch (std::bad_function_call &bfc) {
		return false;
	}

	std::cout << "i1: " << i1 << " i2: " << i2 << std::endl;

	return i1 == 5 && i2 == 5;
}

int main() {
	util::tester::tester the_tester(__FILE__);

	the_tester.add(test_0);

	return the_tester.run();
}
