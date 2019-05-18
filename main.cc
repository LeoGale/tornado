#include <iostream>
#include <chrono>

#include "Config.h"
#include "ThreadPool.hpp"


#ifdef SEE_OBSERVE
#include "observer.hh"
#endif
void func()
{
    std::cout <<"test thread" << std::endl;
}
void testThreadPool()
{
    tornado::ThreadPool aThrPool(2, func);  

    aThrPool.start();
//std::this_thread::sleep_for(std::chrono_literals::2s);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    aThrPool.stop(); 
}

int main(int argc, char* argv[])
{
    std::cout <<"program " << argv[0]
        << "version " <<VERSION_MAJOR 
        <<"." << VERSION_MINOR << std::endl;
        
#ifdef SEE_OBSERVE
    //Observer observe;
    //observe.notify();
#endif

#if defined(HAVE_LOG) && defined(HAVE_EXP)
  double result = exp(log(x)*0.5);
#else // otherwise use an iterative approach
  double result = 0.00;
#endif
  testThreadPool();
  return 0;
}
