/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ProducerConsumeQueue.h
 * Author: ethan
 *
 * Created on February 25, 2017, 11:33 AM
 */

#ifndef PRODUCERCONSUMEQUEUE_H
#define PRODUCERCONSUMEQUEUE_H
#include <mutex>
#include <condition_variable>
#include <queue>
namespace CTCPSERVER {

    template<class T>
    class ProducerConsumerQueue {
    private:
        std::queue<T> mQueue;
        std::mutex mMutex;
        std::condition_variable mCondition;
    public:
        
        void enqueue(const T& nValue) {
            std::unique_lock<std::mutex> lock(mMutex);
            mQueue.push(nValue);
            //Notify one thread to handle this item
            mCondition.notify_one();
        }

        T dequeue() {
            std::unique_lock<std::mutex> lock(mMutex);
            //Avoid spurious waken
            mCondition.wait(lock,[this]{return !mQueue.empty();} );
           
            T lFrontItem = mQueue.front();
            mQueue.pop();
            return lFrontItem;
        }


    };
}


#endif /* PRODUCERCONSUMEQUEUE_H */

