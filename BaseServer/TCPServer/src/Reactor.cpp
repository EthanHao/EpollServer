/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Reactor.cpp
 * Author: ethan
 * 
 * Created on February 14, 2017, 7:36 PM
 */

#include "Reactor.h"
#include "MemoryPool.h"
#include <netinet/in.h>
#include <arpa/inet.h>
namespace CTCPSERVER {

    Reactor::Reactor(int nMaxNumOfSocket,int nNumOfWorkers) throw (EpollExceptionCreateFailed&,
            std::bad_alloc&,
            ThreadExceptionCreateFailed&) :
    mnMaxNumOfSocket(nMaxNumOfSocket + 1) {

      
        std::unique_ptr<EPollObject> lpEpoll(new EPollObject(mnMaxNumOfSocket));
        mpEpollObject = std::move(lpEpoll);

        //allocate memory for the event array
        std::unique_ptr<struct epoll_event[] > lpEvents(new epoll_event[mnMaxNumOfSocket], std::default_delete<struct epoll_event[]>());
        mpEpollEvents = std::move(lpEvents);

        //Allocate a chunk of memory to store the socket info list
        std::unique_ptr<MemoryPool < ConnectionInfo >> lpMemoryPool(new MemoryPool<ConnectionInfo>(mnMaxNumOfSocket));
        mpMemoryPool = std::move(lpMemoryPool);

        //Create the workers
        std::unique_ptr<ThreadPool<Event>> lpThreadPool(new ThreadPool<Event>(nNumOfWorkers));
        mpThreadPool = std::move(lpThreadPool);
        
        

        //Run
        mbRunning = false;
        Run();
    }

    Reactor::~Reactor() {
        //Wait the termination of the thread
        StopAndWait();
    }
   

    //Thread call back function

    void Reactor::TheadCallback() {

        while (mbRunning && mpEpollObject && mpEpollEvents) {
            try {
                //Wait
                int nfds = mpEpollObject->Wait(&mpEpollEvents[0], mnMaxNumOfSocket);
                //accept this client one by one
                for (int i = 0; i < nfds; i++) {
                    Event lEvent(mpEpollEvents[i], nullptr,this);
                    mpThreadPool->AddItem(lEvent);
                }

            } catch (EpollExceptionWaitFailed& e) {

                //If it is system call interrupt then continue
                if (e.GetErrorNo() == EINTR)
                    continue;

                //Else Exit this thread,
                //Log the reason to exit the thread
                mbRunning = false;
                break;
            } catch (std::exception& e) {
                //Log the reason
                //Continue
            }
        }
    }

   
    eErrorCode Reactor::Run() throw (ThreadExceptionCreateFailed&) {
        if (mbRunning || mThread.joinable())
            return eErrorCode::eIsRunning;
        mThread = std::thread(&Reactor::TheadCallback, this);
        if (mThread.joinable()) {
            mbRunning = true;
            return eErrorCode::eSuccess;
        } else throw ThreadExceptionCreateFailed(errno);
    }


    //add a socket to this dealer

    eErrorCode Reactor::AddSocketItem(int nfd)
    throw (LogicalExceptionNoEmptyRoonInMemoryPool&, EpollExceptionCtlFailed&) {

        //Because this function will be called in context of other threads
        //so we should keep the shared data safe.
        std::lock_guard<std::mutex> lock(mMutex);

        if (!mpEpollObject)
            return eInvalidObject;

        //Assign a index of Connection info for this file descriptor
        ConnectionInfo * lpCon = mpMemoryPool->alloc();
        if (lpCon == nullptr)
            throw LogicalExceptionNoEmptyRoonInMemoryPool(errno, nfd);
        //Construct this chunk of memory
        lpCon->Set(nfd,mpEpollObject.get());

        struct epoll_event ev;
        ev.events = EPOLLIN|EPOLLET; //use the Edge triggered mode to monitor the reading event
        ev.data.ptr = lpCon;
        try {
            mpEpollObject->AddFileDescriptor(nfd, ev);
        } catch (EpollExceptionCtlFailed& e) {
            mpMemoryPool->free(lpCon);
            throw e;
        }
        return eErrorCode::eSuccess;
    }

    //delete a socket from this dealer

    eErrorCode Reactor::DeleteSoecktItem(int nfd) throw (EpollExceptionCtlFailed&) {

        std::lock_guard<std::mutex> lock(mMutex);
        if (!mpEpollObject)
            return eInvalidObject;

        //Check Parameters
        if (!mpMemoryPool || mMapSocket.find(nfd) != mMapSocket.end())
            return eErrorCode::eInvalidObject;
        //Free the memory from the memorypool
        mpMemoryPool->free(mMapSocket[nfd]);

        //Delete this nfd from the map
        mMapSocket.erase(nfd);

        struct epoll_event ev;
        return mpEpollObject->RemoveFileDescriptor(nfd, ev);
    }

}

