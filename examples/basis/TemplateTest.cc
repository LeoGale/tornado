#include <iostream>
#include <functional>
#include <string.h>

#include "tornado/base/sum.hh"
#include "tornado/base/type_traits.hh"
#include "tornado/base/tuple.hh"

class Foo {
    public:
	void say(){
	    std::cout<<"I'm Foo, my age is " << age_ << std::endl;	
	};

	void setAge(int age)
	{
	    age_ = age;
	}
    private:
	int age_ {1};
};

using FooSayFunc = std::function<void(Foo)>;
using FooMemPtr = void(Foo::*)();
void testIsMemberPointer()
{
    //static_assert(std::is_member_pointer<void(Foo::*)>::value, "T should be a member pointer");
    static_assert(tornado::is_member_pointer<int(Foo::*)>::value, "T should be a member pointer");
    //static_assert(tornado::is_member_function_pointer<decltype(&Foo::say)>::value, "T should be a member pointer");
    static_assert(tornado::is_member_function_pointer<decltype(&Foo::setAge)>::value, "T should be a member pointer");
    static_assert(std::is_same<decltype(tornado::is_member_function_pointer<decltype(&Foo::setAge)>::u_), Foo>::value, "U is not a Foo");
}



void testTuple()
{
    //tornado::tuple<double, int, std::string> tt(1.22, 2, "heck");
    //tornado::tuple<double, int, std::string> tt1 = tornado::make_tuple(1.23, 4, "tidous");
}

void testCount()
{
    std::cout <<"count value:" <<  tornado::Count<char, int>::value << std::endl;
}

int main()
{
    testCount();
    int a,b = 20;
    double c,d = 12.245;

    Foo aFoo;
    FooSayFunc aFunc = &Foo::say;
    aFunc(std::ref(aFoo));
    aFoo.setAge(2);

    aFunc(aFoo);//ok with reference definition
    //aFunc(std::ref(aFoo));
    aFoo.setAge(3);

    FooMemPtr aMemFunc = &Foo::say;
    (aFoo.*aMemFunc)();

    //std::cout <<"integer sum:" << add(a, b) << std::endl;
    //std::cout <<"double sum:" << add(c, d) << std::endl;
}
