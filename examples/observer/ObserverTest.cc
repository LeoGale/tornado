#include <iostream>

#include "Observable.hh"

class Foo : public Observer
{
    public:
	void update()
	{
	    std::cout <<"Foo is updated." << std::endl;
	}
};

int main()
{
    Observable aSubject;
    Foo aFoo;
    aFoo.observe(&aSubject);
    aSubject.notifyObservers();
    return 0;
}
