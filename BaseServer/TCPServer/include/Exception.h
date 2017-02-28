/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.h
 * Author: ethan
 *
 * Created on February 14, 2017, 7:50 AM
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <errno.h>
#include <string.h> 
#include <exception>
namespace CTCPSERVER {

    class EpollException : public std::exception {
    public:

        EpollException(const int nErrorNo, const int nEpollHandle = 0,const int nSocketHandle = 0) : 
            _errorno(nErrorNo), 
            _epollHandle(nEpollHandle),
            _socketHandle(nSocketHandle) {
        }

        const char* what() const throw () {
            return strerror(_errorno);
        }
        const int GetErrorNo() {
            return _errorno;
        }
        const int GetSocketHandle() {
            return _socketHandle;
        }
        const int GetEpollHandle() {
            return _epollHandle;
        }
    private:
        const int _errorno;
        const int _epollHandle;
        const int _socketHandle;
      
    };

    class EpollExceptionCreateFailed : public EpollException {
    public:
        EpollExceptionCreateFailed(const int nErrorNo,const int nEpollHandle = 0,const int nSocketHandle = 0) : 
            EpollException(nErrorNo,nEpollHandle,nSocketHandle) {
        }
    };

    class EpollExceptionCloseFailed : public EpollException {
    public:
        EpollExceptionCloseFailed(const int nErrorNo,const int nEpollHandle = 0,const int nSocketHandle = 0) : 
            EpollException(nErrorNo,nEpollHandle,nSocketHandle) {
        }

    };
    
    class EpollExceptionCtlFailed : public EpollException {
    public:
        EpollExceptionCtlFailed(const int nErrorNo,const int nEpollHandle = 0,const int nSocketHandle = 0) : 
            EpollException(nErrorNo,nEpollHandle,nSocketHandle) {
        }

    };
    
    class EpollExceptionWaitFailed : public EpollException {
    public:
        EpollExceptionWaitFailed(const int nErrorNo,const int nEpollHandle = 0,const int nSocketHandle = 0) : 
            EpollException(nErrorNo,nEpollHandle,nSocketHandle) {
        }

    };
    class EpollExceptionEventFailed : public EpollException {
    public:
        EpollExceptionEventFailed(const int nErrorNo,const int nEpollHandle = 0,const int nSocketHandle = 0) : 
            EpollException(nErrorNo,nEpollHandle,nSocketHandle) {
        }

    };
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Socket Exception
    ////////////////////
    class SocketException : public std::exception {
    public:

        SocketException(const int nErrorNo,const int nSocketHandle = 0,const int nCustomeErrorNo = 0) :
        _errorno(nErrorNo),_socketHandle(nSocketHandle),_customeErrorNo(nCustomeErrorNo) {
        }

        const char* what() const throw () {
            return strerror(_errorno);
        }
        const int GetErrorNo() const{
            return _errorno;
        }
        const int GetSocketHandle()const {
            return _socketHandle;
        }
        const int GetCustomeErrorNo()const{
            return _customeErrorNo;
        }
    private:
        const int _errorno;
        const int _socketHandle;
        const int _customeErrorNo;

    };
    
    class SocketExceptionCreateFailed : public SocketException {
    public:
        SocketExceptionCreateFailed(const int nErrorNo,const int nSocketHandle = 0,const int nCustomeErrorNo = 0) :
        SocketException(nErrorNo,nSocketHandle,nCustomeErrorNo) {
        }
    };
    class SocketExceptionSetOptionFailed : public SocketException {
    public:
        SocketExceptionSetOptionFailed(const int nErrorNo,const int nSocketHandle = 0,const int nCustomeErrorNo = 0) :
        SocketException(nErrorNo,nSocketHandle,nCustomeErrorNo){
        }
    };
    class SocketExceptionBindFailed : public SocketException {
    public:
        SocketExceptionBindFailed(const int nErrorNo,const int nSocketHandle = 0,const int nCustomeErrorNo = 0) :
        SocketException(nErrorNo,nSocketHandle,nCustomeErrorNo) {
        }
    };
    class SocketExceptionListenFailed : public SocketException {
    public:
        SocketExceptionListenFailed(const int nErrorNo,const int nSocketHandle = 0,const int nCustomeErrorNo = 0) :
        SocketException(nErrorNo,nSocketHandle,nCustomeErrorNo){
        }
    };
    class SocketExceptionAcceptFailed : public SocketException {
    public:
        SocketExceptionAcceptFailed(const int nErrorNo,const int nSocketHandle = 0,const int nCustomeErrorNo = 0) :
        SocketException(nErrorNo,nSocketHandle,nCustomeErrorNo){
        }
    };
    class SocketExceptionP2NFailed : public SocketException {
    public:
        SocketExceptionP2NFailed(const int nErrorNo,const int nSocketHandle = 0,const int nCustomeErrorNo = 0) :
        SocketException(nErrorNo,nSocketHandle,nCustomeErrorNo) {
        }
    };
    class SocketExceptionP2NWrongFormat : public SocketException {
    public:
        SocketExceptionP2NWrongFormat(const int nErrorNo,const int nSocketHandle = 0,const int nCustomeErrorNo = 0) :
        SocketException(nErrorNo,nSocketHandle,nCustomeErrorNo) {
        }
    };
    class SocketExceptionH2SFailed : public SocketException {
    public:
        SocketExceptionH2SFailed(const int nErrorNo,const int nSocketHandle = 0,const int nCustomeErrorNo = 0) :
        SocketException(nErrorNo,nSocketHandle,nCustomeErrorNo) {
        }
    };
    class SocketExceptionConnectFailed : public SocketException {
    public:
        SocketExceptionConnectFailed(const int nErrorNo,const int nSocketHandle = 0,const int nCustomeErrorNo = 0) :
        SocketException(nErrorNo,nSocketHandle,nCustomeErrorNo) {
        }
    };
    class SocketExceptionInvalidDescriptor : public SocketException {
    public:
        SocketExceptionInvalidDescriptor(const int nErrorNo,const int nSocketHandle = 0,const int nCustomeErrorNo = 0) :
        SocketException(nErrorNo,nSocketHandle,nCustomeErrorNo) {
        }
    };
    
    class SocketExceptionReadFaild : public SocketException {
    public:
        SocketExceptionReadFaild(const int nErrorNo,const int nSocketHandle = 0,const int nCustomeErrorNo = 0) :
        SocketException(nErrorNo,nSocketHandle,nCustomeErrorNo) {
        }
    };
    class SocketExceptionWriteFaild : public SocketException {
    public:
        SocketExceptionWriteFaild(const int nErrorNo,const int nSocketHandle = 0,const int nCustomeErrorNo = 0) :
        SocketException(nErrorNo,nSocketHandle,nCustomeErrorNo) {
        }
    };
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Thread Exception
    class ThreadException : public std::exception {
    public:

        ThreadException(const int& nErrorNo) : _errorno(nErrorNo) {
        }

        const char* what() const throw () {
            return strerror(_errorno);
        }
        const int GetErrorNo() {
            return _errorno;
        }
    private:
        const int _errorno;

    };
    
    class ThreadExceptionCreateFailed : public ThreadException {
    public:
        ThreadExceptionCreateFailed(const int& nErrorNo) : ThreadException(nErrorNo) {
        }
    };
    
    
    ////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Logical Exception
    class LogicalException : public std::exception {
    public:

        LogicalException(const int& nErrorNo,const int& nSocketHandle) : _errorno(nErrorNo),_socketHandle(nSocketHandle) {
        }

        const char* what() const throw () {
            return strerror(_errorno);
        }
        const int GetErrorNo() {
            return _errorno;
        }
        const int GetSocketHandle() {
            return _socketHandle;
        }
    private:
        const int _errorno;
        const int _socketHandle;

    };
    
    class LogicalExceptionTooManyBackendServer : public LogicalException {
    public:
        LogicalExceptionTooManyBackendServer(const int& nErrorNo,const int& SocketHandle = 0) : LogicalException(nErrorNo,SocketHandle) {
        }
    };
    class LogicalExceptionNoBackendServer : public LogicalException {
    public:
        LogicalExceptionNoBackendServer(const int& nErrorNo,const int& SocketHandle = 0) : LogicalException(nErrorNo,SocketHandle) {
        }
    };
     class LogicalExceptionNoEmptyRoonInMemoryPool : public LogicalException {
    public:
        LogicalExceptionNoEmptyRoonInMemoryPool(const int& nErrorNo,const int& SocketHandle = 0) : LogicalException(nErrorNo,SocketHandle) {
        }
    };
     class LogicalExceptionNoEngoughBuffer: public LogicalException {
    public:
        LogicalExceptionNoEngoughBuffer(const int& nErrorNo,const int& SocketHandle = 0) : LogicalException(nErrorNo,SocketHandle) {
        }
    };
     class LogicalExceptionInvalidObject : public LogicalException {
    public:
        LogicalExceptionInvalidObject(const int& nErrorNo,const int& SocketHandle = 0) : LogicalException(nErrorNo,SocketHandle) {
        }
    };
}

#endif /* EXCEPTION_H */

