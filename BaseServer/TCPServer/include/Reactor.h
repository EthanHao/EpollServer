/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Reactor.h
 * Author: ethan
 *
 * Created on February 14, 2017, 7:36 PM
 */

#ifndef DATADEALER_H
#define DATADEALER_H

#include "ErrorCode.h"
#include "EPollObject.h"
#include "MemoryPool.h"
#include <memory>
#include <mutex>
#include <atomic>
#include <map>
#include "Exception.h"
#include <thread>
#include "ConnectionInfo.h"
#include "ServerInfo.h"
#include "ThreadPool.h"
#include "Event.h"
namespace CTCPSERVER {

    class Reactor {
    public:
        Reactor(int nMaxNumOfSocket,int nNumOfWorkers) throw (EpollExceptionCreateFailed&,
                std::bad_alloc&,
                ThreadExceptionCreateFailed&);
        Reactor(const Reactor& orig) = delete;
        virtual ~Reactor();

        //GetFreeSize of MemoryPool
        int GetFreeSize() { return mpMemoryPool ?  mpMemoryPool->GetFreeSize() : 0;}
        
        //Connect to the backend Server
        eErrorCode Connect()throw (SocketExceptionCreateFailed&,
                SocketExceptionP2NWrongFormat&,
                SocketExceptionP2NFailed&,
                SocketExceptionConnectFailed&,
                SocketExceptionSetOptionFailed&);

        //Run this Dealer in his own thread
        eErrorCode Run() throw (ThreadExceptionCreateFailed&);
        //the callback function of thread
        void TheadCallback();

        //Stop Data Reading and Writing , means stopping the thread
        inline bool Stop() {
            if (mbRunning == false || !mThread.joinable())
                return false;
            mbRunning = false;
            return true;
        }
        
        inline bool StopAndWait() {
            if(mbRunning == false || !mThread.joinable())
                return false;
            mThread.join();
            mbRunning = false;
            return true;
        }
        //add a socket to this dealer
        eErrorCode AddSocketItem(int nfd) 
         throw (LogicalExceptionNoEmptyRoonInMemoryPool&,EpollExceptionCtlFailed&);
        //delete a socket from this dealer
        eErrorCode DeleteSoecktItem(int nfd) throw(EpollExceptionCtlFailed&);
        
        //Data things
        eErrorCode DataReadAndWritting( struct epoll_event& npEvent);
    
    private:
        const int mnMaxNumOfSocket;
        std::mutex mMutex;
        std::unique_ptr<EPollObject> mpEpollObject;
        std::unique_ptr<struct epoll_event[]> mpEpollEvents; 
        
        //thread content
        std::thread mThread;
        std::atomic<bool> mbRunning;
        
        std::unique_ptr<MemoryPool<ConnectionInfo>> mpMemoryPool;
        std::map<int,ConnectionInfo*> mMapSocket;
        //
        std::unique_ptr<ThreadPool<Event>> mpThreadPool;
        
    };
}
#endif /* DATADEALER_H */

