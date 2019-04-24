#include <iostream>

#include "Config.h"

#ifdef SEE_OBSERVE
#include "observer.hh"
#endif

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
  return 0;
}
