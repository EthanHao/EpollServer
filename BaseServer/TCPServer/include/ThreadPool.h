/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ThreadPool.h
 * Author: ethan
 *
 * Created on February 25, 2017, 12:32 PM
 */

#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "ProducerConsumerQueue.h"
#include <thread>
namespace CTCPSERVER {
    template <class T>
    class ThreadPool{
        private:
            //The queue for dispatch event to the consumers( thread pool)
            ProducerConsumerQueue<T> mConsumerQueue;
            std::vector<std::unique_ptr<std::thread>> mThreads;
            int mnThreadNumber;
            std::atomic<bool> mbRunning; 
    public:

        ThreadPool(int nNum) throw(ThreadExceptionCreateFailed&) : mnThreadNumber(nNum), mbRunning(false) {

            for (int i = 0; i < mnThreadNumber; i++) {
                //Create this number of thread
               std::unique_ptr<std::thread> lThread (new std::thread(&ThreadPool::ThreadCallBack, this));
                if (!lThread || !lThread->joinable())
                    throw ThreadExceptionCreateFailed(errno);

                mThreads.push_back( std::move(lThread) );
            }
            mbRunning = true;

        }

        //Add item to the thread pool
        void AddItem(const T& nItem) {
            mConsumerQueue.enqueue(nItem);
        }

        bool ThreadCallBack() {
            if (mbRunning) {
                mConsumerQueue.dequeue().doit();
            }
        }
    };
}


#endif /* THREADPOOL_H */

