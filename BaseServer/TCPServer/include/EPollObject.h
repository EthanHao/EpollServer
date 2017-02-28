/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EPollObject.h
 * Author: ethan
 *
 * Created on January 30, 2017, 5:26 PM
 */

#ifndef EPOLLOBJECT_H
#define EPOLLOBJECT_H
#include <sys/epoll.h>
#include "Exception.h"
#include "ErrorCode.h"
#include <unistd.h>
namespace CTCPSERVER {

    class EPollObject {
    public:
        EPollObject(int nSize) throw (EpollExceptionCreateFailed&);
        EPollObject(const EPollObject& orig) = delete;
        virtual ~EPollObject();

        //Add a file handle to this epoll object
        eErrorCode AddFileDescriptor(int nfd,  struct epoll_event & event)
         throw(EpollExceptionCtlFailed&);

        //remove a file handle from this epoll object
        eErrorCode RemoveFileDescriptor(int nfd,  struct epoll_event & event)
         throw(EpollExceptionCtlFailed&);

        //Modify the fd
        eErrorCode ModifyFileDescriptor(int nfd,  struct epoll_event & event)
         throw(EpollExceptionCtlFailed&);
        //check this epoll object to get the file handles we are going to deal with
        //or there is something happened on this file handles.
        int Wait(struct epoll_event* events, int nMaxEvent, int nTimeOut = -1)
         throw(EpollExceptionWaitFailed&);
        
        //GetID
        int GetEpollID() {return mnEpollID;}
    private:
        int mnMaxSize;
        int mnEpollID;

    };
}

#endif /* EPOLLOBJECT_H */

