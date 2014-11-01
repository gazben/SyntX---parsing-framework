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

#include <iostream>

#include <util/enum_set.h>
#include <util/tester/tester.h>

using util::enum_set;

class foo {
	public:
		enum class bar {foo_bar, bar_foo, foo_foo, bar_bar};
};

bool test_0() {
	enum_set<foo::bar> a_set({foo::bar::foo_bar});

	if (!a_set.has(foo::bar::foo_bar)) return false;
	if (a_set.has(foo::bar::bar_foo)) return false;

	a_set.insert(foo::bar::bar_foo);
	if (!a_set.has(foo::bar::foo_bar)) return false;
	if (!a_set.has(foo::bar::bar_foo)) return false;

	a_set.remove(foo::bar::foo_bar);
	if (a_set.has(foo::bar::foo_bar)) return false;
	if (!a_set.has(foo::bar::bar_foo)) return false;

	a_set.insert({foo::bar::foo_foo, foo::bar::bar_bar});
	if (!a_set.has(foo::bar::foo_foo)) return false;
	if (!a_set.has(foo::bar::bar_bar)) return false;

	a_set.remove({foo::bar::foo_foo, foo::bar::bar_bar});
	if (a_set.has(foo::bar::foo_foo)) return false;
	if (a_set.has(foo::bar::bar_bar)) return false;

	return true;
}

int main() {
	util::tester::tester the_tester(__FILE__);

	the_tester.add(test_0);

	return the_tester.run();
}
