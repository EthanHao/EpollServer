/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectionInfo.cpp
 * Author: ethan
 * 
 * Created on January 30, 2017, 5:27 PM
 */

#include "ConnectionInfo.h"
#include <unistd.h>
#include "StreamCheckerInterface.h"
#include "ErrorCode.h"
#include <algorithm>
#include <string.h>
namespace CTCPSERVER {

    ConnectionInfo::ConnectionInfo() {
        mnSocketHandle = 0;
        mnReadLen = 0;
        mnUnwrittenLen = 0;
    }

    void ConnectionInfo::Set(int nSocket,EPollObject * npObject) {
        mnSocketHandle = nSocket;
        mpEpollObject = npObject;
        return;
    }

    void ConnectionInfo::ConcatenateBufferToUnwrittenBuffer(const char* npBuf,int nOffset,int nLen){
        int lnMin = std::min(static_cast<int> (mUnwrittenBuffer.capacity()), nLen);
        for (int i = 0; i < lnMin; i++)
            mUnwrittenBuffer[mnUnwrittenLen + i] = *(npBuf + nOffset + i);
        if (lnMin == mUnwrittenBuffer.capacity()) {
            for (int i = mUnwrittenBuffer.capacity(); i < nLen; i++)
                mUnwrittenBuffer.push_back(*(npBuf + nOffset + i));
        }
        mnUnwrittenLen += nLen;
    }

    void ConnectionInfo::CopyBufferToReadedBuffer(const char* npBuf,int nOffset, int nLen) {
        int lnMin = std::min(static_cast<int> (mReadBuffer.capacity()), nLen);
        for (int i = 0; i < lnMin; i++)
            mReadBuffer[i] = *(npBuf + nOffset + i);
        if (lnMin == mReadBuffer.capacity()) {
            for (int i = mReadBuffer.capacity(); i < nLen; i++)
                mReadBuffer.push_back(*(npBuf + nOffset + i));
        }
        mnReadLen = nLen;
    }

     eErrorCode ConnectionInfo::Send() throw(SocketExceptionWriteFaild&) {
        //check the unwrittenbuf 
        //send the unwrittenbuf first
        //if the kernal buffer is full , than we append the input buffer to the unwritten buf and set Epollout to wait the next available 
        //---writting time.
        //else write the input buffer to the kernal buffer until return successfully, if this time the kernal is also full,we need to 
        //----copy the rest of the input buffer to the unwritten buffer and set the epollout to wait next time.
        int lnWritten = 0;
        int n = mnUnwrittenLen;
        while (n > 0) {
            lnWritten = ::write(mnSocketHandle, &mUnwrittenBuffer[0] + mnUnwrittenLen - n, n);
            if (lnWritten < n) {
                if (lnWritten == -1 && errno != EAGAIN) {
                     throw new SocketExceptionWriteFaild(errno, mnSocketHandle, -1);
                }
                break;
            }
            n -= lnWritten;
        }
        
        if(n > 0 && n != mnUnwrittenLen){
            //We got some data in unwritten buffer unsent
            memmove(&mUnwrittenBuffer[0],&mUnwrittenBuffer[0]+ mnUnwrittenLen - n, n);
            mnUnwrittenLen = n;
            //Set epollout|epollin ,to get the next chance to write
            struct epoll_event ev;
            ev.events = EPOLLIN|EPOLLOUT; 
            ev.data.ptr = this;
            mpEpollObject->ModifyFileDescriptor(mnSocketHandle,ev);
            return eErrorCode::eBufferNotAllSent;
        }else{
            //we have send all Clear EpollOut
            struct epoll_event ev;
            ev.events = EPOLLIN| EPOLLET; 
            ev.data.ptr = this;
            mpEpollObject->ModifyFileDescriptor(mnSocketHandle,ev);
            return eErrorCode::eBufferAllSent;
        }
    }
    
    eErrorCode ConnectionInfo::Send(const char* npBuf, const int nLen)
            throw(std::invalid_argument&,SocketExceptionWriteFaild&,EpollExceptionCtlFailed&)  {
        //send the unwrittenbuf first
        //if the kernal buffer is full , than we append the input buffer to the unwritten buf and set Epollout to wait the next available 
        //---writting time.
        //else write the input buffer to the kernal buffer until return successfully, if this time the kernal is also full,we need to 
        //----copy the rest of the input buffer to the unwritten buffer and set the epollout to wait next time.
        if (npBuf == nullptr || nLen == 0)
            throw new std::invalid_argument("Buffer point is nullptr");
        if (eErrorCode::eBufferAllSent == Send()) {
            int lnWritten = 0;
            int n = nLen;
            while (n > 0) {
                lnWritten = ::write(mnSocketHandle, npBuf + nLen - n, n);
                if (lnWritten < n) {
                    if (lnWritten == -1 && errno != EAGAIN) {
                        throw new SocketExceptionWriteFaild(errno, mnSocketHandle, -1);
                    }
                    break;
                }
                n -= lnWritten;
            }
            if (n > 0 && n != mnUnwrittenLen) {
                //We got some data in unwritten buffer unsent
                //concatenate npbuf to the WrittenBuffer
                ConcatenateBufferToUnwrittenBuffer(npBuf, n, nLen);
                //Set epollout|epollin
                struct epoll_event ev;
                ev.events = EPOLLIN | EPOLLOUT | EPOLLET;
                ev.data.ptr = this;
                mpEpollObject->ModifyFileDescriptor(mnSocketHandle, ev);
            } else {
                //Clear epollout
                struct epoll_event ev;
                ev.events = EPOLLIN| EPOLLET;
                ev.data.ptr = this;
                mpEpollObject->ModifyFileDescriptor(mnSocketHandle, ev);
            }

            
        } else {
            //We only can wait next time to send,so need to save the input buffer to unwritten buffer
            ConcatenateBufferToUnwrittenBuffer(npBuf, 0, nLen);
            //Set epollout|epollin
            //Set epollout|epollin
            struct epoll_event ev;
            ev.events = EPOLLIN | EPOLLOUT| EPOLLET;
            ev.data.ptr = this;
            mpEpollObject->ModifyFileDescriptor(mnSocketHandle, ev);
        }


        
    }

    void ConnectionInfo::Recieve(void * npStreamChecker)
    throw (SocketExceptionReadFaild&, LogicalExceptionInvalidObject&, LogicalExceptionNoEngoughBuffer&) {
        //Read the buffer from the kernal buffer
        //combine the mreadbuf with the buffer we just copyed from the kernal buffer
        //call the upper level callback function and passing in the combined buffer
        //set epollin  
        if (npStreamChecker == nullptr)
            throw new LogicalExceptionInvalidObject(errno);
        if (mnReadLen >= MAX_BUFFER_SIZE) //this should be big disaster
            throw new LogicalExceptionNoEngoughBuffer(errno);
        char lsBuffer[MAX_BUFFER_SIZE] = {0};
        //Copy the data reading before
        if (mnReadLen > 0 && mnReadLen < MAX_BUFFER_SIZE)
            memcpy(lsBuffer, &mReadBuffer[0], mnReadLen);

        char * lp = lsBuffer + mnReadLen;
        int lnBufLen = MAX_BUFFER_SIZE - mnReadLen;
        while (true) {
            ssize_t lnReceiveBufferLength = ::read(mnSocketHandle, lp, lnBufLen);
            if (lnReceiveBufferLength < 0) {
                if (errno == EAGAIN /*|| errno == EWOULDBLOCK*/) {
                    //Finish reading the buffer
                    break;
                } else if (errno == EINTR) {
                    //Read function was interupt by the system call
                    continue;
                } else {
                    //Other Error 
                    throw new SocketExceptionReadFaild(errno, mnSocketHandle, -1);
                }
            } else if ((lnReceiveBufferLength == 0)) {
                /* socket was closed by peer */
                throw new SocketExceptionReadFaild(errno, mnSocketHandle, -2);
            } else {
                //Continue to read until EAGAIN
                lp += lnReceiveBufferLength;
                lnBufLen -= lnReceiveBufferLength;
            }
        }
        
        //Scan this stream to find valid packets and copy the not dealt data to the mReadBuffer
        {
            int lnAllBufferSize = MAX_BUFFER_SIZE - lnBufLen;
            IStreamChecker* lpStreamChecker = (static_cast<IStreamChecker*> (npStreamChecker));
            int lnReadedSize = (*lpStreamChecker)(lsBuffer, lnAllBufferSize);
            if( lnReadedSize ==  lnAllBufferSize){
                //all data has been dealt,so the rest of read buffer is empty
                mnReadLen = 0;
            }else{
                //No data of Part of data has been dealt, copy the local buffer not dealt back to the read buffer
                CopyBufferToReadedBuffer(lsBuffer,lnReadedSize,lnAllBufferSize - lnReadedSize);               
            }
        }
    }
}
