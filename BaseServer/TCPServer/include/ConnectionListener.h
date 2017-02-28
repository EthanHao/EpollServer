/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectionLister.h
 * Author: ethan
 *
 * Created on January 30, 2017, 5:29 PM
 */

#ifndef CONNECTIONLISTER_H
#define CONNECTIONLISTER_H
#include "ErrorCode.h"
#include "EPollObject.h"
#include <memory>
#include <atomic>
#include "Exception.h"
#include <thread>
#include "ReactorCenterInterface.h"

namespace CTCPSERVER {

    class ConnectionListener {
    public:
        ConnectionListener(const std::string& nIP, int nPort,int nMaxBacklogSize,IReactorCenterInterface* npDataCenter)
                throw(SocketExceptionCreateFailed&,
                SocketExceptionSetOptionFailed&,
                SocketExceptionBindFailed&,
                SocketExceptionListenFailed&,
                EpollExceptionCreateFailed&,
                EpollExceptionCtlFailed&,
                std::bad_alloc&,
                ThreadExceptionCreateFailed&);
        
        ConnectionListener(const ConnectionListener& orig) = delete;
        
        virtual ~ConnectionListener() ;

        //Run this listener
        eErrorCode Run() throw(ThreadExceptionCreateFailed&);
        
        //the callback function of thread
        void TheadCallback();
        void Accept(epoll_event * npEvent) throw(SocketExceptionAcceptFailed&,
                                                 SocketExceptionSetOptionFailed&,
                                                 EpollExceptionCtlFailed&);
        
        //Stop listening , means stopping the thread
        inline bool Stop() {
            if(mbRunning == false || !mThread.joinable()) 
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
    private: 
        const std::string msIP;
        const int mnPort;
        const int mnMaxBacklogSize;
        
        int mnListenFileDescriptor;
        std::unique_ptr<EPollObject> mpEpollObject;
        std::unique_ptr<struct epoll_event[]> mpEpollEvents; 
        //thread content
        std::thread mThread;
        std::atomic<bool> mbRunning;
        
        //The pointer to the dataCenter
        IReactorCenterInterface* mpReactorCenter;
    };
}
#endif /* CONNECTIONLISTER_H */

