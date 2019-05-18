//
//  ThreadPool.cpp
//  
//
//  Created by leo on 2019/5/11.
//

#include "ThreadPool.hpp"

#include <iostream>

namespace tornado
{
ThreadPool::ThreadPool(ThreadFunc && func, size_t poolSize)
    :isStarted_(false),
    poolSize_(poolSize),
    func_(std::forward<ThreadFunc>(func))
{
    std::cout <<"ThreadPool::ThreadPool" << std::endl;
}
    
ThreadPool::~ThreadPool()
{
    if(isStarted_)
    {
        for(auto & thr : threads_)
        {
            assert(thr.jionable());
            thr.join();
        }
    }
}
    
    void ThreadPool::start()
    {
        size_t poolSize = poolSize_;
        while(poolSize > 0)
        {
            threads_.emplace_back(func_);
            --poolSize;
        }
        isStarted_ = true;
    }
    
    void ThreadPool::stop()
    {
        for(auto & thr : threads_)
        {
            thr.join();
        }
        isStarted_ = false;
    }
}
