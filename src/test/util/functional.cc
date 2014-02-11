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
