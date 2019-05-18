//
//  Thread.hpp
//  
//
//  Created by leo on 2019/5/11.
//

#pragma once
#include <functional>

namespace tornado {
class Thread
{
public:
    using ThreadFunc = std::function<void()>;
    Thread(ThreadFunc && threadFunc);
    void join();
    void start();
private:
    bool joined_;
};
    
}
