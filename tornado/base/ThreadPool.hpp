//
//  ThreadPool.hpp
//  
//
//  Created by leo on 2019/5/11.
//

#pragma once
#include <vector>
#include <functional>
#include <thread>

namespace tornado
{
class ThreadPool {
public:
    using ThreadFunc  = std::function<void()>;
    ThreadPool(ThreadFunc && func, size_t poolSize);
    ~ThreadPool();
    void start();
    void stop();
    inline size_t size() { return poolSize_;}
private:
    bool isStarted_;
    size_t poolSize_;
    ThreadFunc func_;
    std::vector<std::thread> threads_;
};
}
