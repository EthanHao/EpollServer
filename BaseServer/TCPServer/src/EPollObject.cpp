/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EPollObject.cpp
 * Author: ethan
 * 
 * Created on January 30, 2017, 5:26 PM
 */

#include "../include/EPollObject.h"

namespace CTCPSERVER {

    EPollObject::EPollObject(int nMaxSize)
    throw (EpollExceptionCreateFailed&) {

        mnEpollID = epoll_create(nMaxSize);
        if (mnEpollID == -1)
            throw EpollExceptionCreateFailed(errno);

        mnMaxSize = nMaxSize;
    }

    EPollObject::~EPollObject() {
        if (mnEpollID != -1) {
            int nRet = close(mnEpollID);
            if (nRet == -1) {
                //Log the reason
            }
        }
    }

    //Add a file handle to this epoll object

    eErrorCode EPollObject::AddFileDescriptor(int nfd, struct epoll_event & event)
    throw (EpollExceptionCtlFailed&) {

        if (-1 == ::epoll_ctl(mnEpollID, EPOLL_CTL_ADD, nfd, &event))
            throw EpollExceptionCtlFailed(errno, mnEpollID, nfd);

        return eErrorCode::eSuccess;
    }

    //remove a file handle from this epoll object

    eErrorCode EPollObject::RemoveFileDescriptor(int nfd, struct epoll_event & event)
    throw (EpollExceptionCtlFailed&) {
        if (-1 == ::epoll_ctl(mnEpollID, EPOLL_CTL_DEL, nfd, &event))
            throw EpollExceptionCtlFailed(errno, mnEpollID, nfd);

        return eErrorCode::eSuccess;
    }

    //Modify the fd

    eErrorCode EPollObject::ModifyFileDescriptor(int nfd, struct epoll_event & event)
    throw (EpollExceptionCtlFailed&) {
        if (-1 == ::epoll_ctl(mnEpollID, EPOLL_CTL_MOD, nfd, &event))
            throw new EpollExceptionCtlFailed(errno, mnEpollID, nfd);

        return eErrorCode::eSuccess;
    }
    //check this epoll object to get the file handles we are going to deal with
    //or there is something happened on this file handles.

    int EPollObject::Wait(struct epoll_event* events, int nMaxEvent, int nTimeOut)
    throw (EpollExceptionWaitFailed&) {
        int nRet = ::epoll_wait(mnEpollID, events, nMaxEvent, nTimeOut);
        if (nRet == -1)
            throw EpollExceptionWaitFailed(errno, mnEpollID);

        return nRet;
    }
}

