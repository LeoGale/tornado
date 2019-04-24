#pragma once

#include <memory>
#include <vector>

class Observable;

class Observer : std::enable_shared_from_this<Observer> {
public:
    void observe(Observable* subject);
    virtual void update() = 0;
private:
    Observable* subject_;
};

class Observable {
public:
    void register_(const std::shared_ptr<Observer>& observer);
    void notifyObservers();
private:
    mutable std::mutex mutex_;
    using Iterator = std::vector<std::weak_ptr<Observer>>::iterator;
    std::vector<std::weak_ptr<Observer>> observers_;
};

void Observer::observe(Observable* subject)
{
    subject->register_(shared_from_this());
    subject_ = subject;
}

void Observable::register_(const std::shared_ptr<Observer> & observer)
{
    std::lock_guard<std::mutex> aLock(mutex_);
    observers_.push_back(observer);
}

void Observable::notifyObservers()
{
    std::lock_guard<std::mutex> aLock(mutex_);
    Iterator aIter = observers_.begin();
    for(; aIter != observers_.end(); aIter++)
    {
        std::shared_ptr<Observer> aObserver = aIter->lock();
        if(aObserver)
        {
            aObserver->update();
        }
        else 
        {
            observers_.erase(aIter);
        }
    }
}
