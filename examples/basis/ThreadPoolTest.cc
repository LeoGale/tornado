#include <iostream>
#include <chrono>
#include <thread>
#include "tornado/base/ThreadPool.hpp"
//#include "Observable.hh"

class Foo {
    public:
	void operator()()
	{
	    std::cout <<"execute foo" << std::endl;
	}
	
	void sayHello()
	{
	    std::cout <<"Foo say hello" << std::endl;
	}

	void printNum(int num)
	{
	    std::cout <<"print input number:" << num << std::endl;
	}
};

void func()
{
    std::cout <<"test thread" << std::endl;
}

void testThreadPool()
{
    Foo aFoo;
    Foo aFoo1;
    tornado::ThreadPool aThrPool(func, 2);
    tornado::ThreadPool aThrPool2(aFoo, 2);
    tornado::ThreadPool aThrPool3(std::bind(&Foo::sayHello, &aFoo1), 2);
    int num = 4;
    tornado::ThreadPool aThrPool4(std::bind(&Foo::printNum, &aFoo1, std::ref(num)), 2);
    //num = 5;
    // result is 5 stablely
    
    aThrPool.start();
    aThrPool2.start();
    aThrPool3.start();
    aThrPool4.start();
    num = 5;
    //result is 5 or 4 randomly. 

    //std::this_thread::sleep_for(std::chrono_literals::2s);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    aThrPool.stop();
    aThrPool2.stop();
    aThrPool3.stop();
    aThrPool4.stop();
}

int main()
{
    //Observable aSubject;
    //Foo aFoo;
    //aFoo.observe(&aSubject);
    //aSubject.notifyObservers();
    testThreadPool();
    return 0;
}
