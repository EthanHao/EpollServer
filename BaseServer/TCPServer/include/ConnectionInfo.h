/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectionInfo.h
 * Author: ethan
 *
 * Created on January 30, 2017, 5:27 PM
 */

#ifndef SOCKETINFO_H
#define SOCKETINFO_H
#include "CommonMacro.h"
#include "Exception.h"
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
 #include <fcntl.h>
#include <vector>
#include "EPollObject.h"
#include <stdexcept> 
namespace CTCPSERVER {
    constexpr int MAX_BUFFER_SIZE = 10240;
//store everything related to a socket handle
//like we can assign an unique name for this socket
//the ip address, port, receive buffer, send buffer etc these informations directly related to a socket

  
    class ConnectionInfo{
    public:
        ConnectionInfo();
        ConnectionInfo(const ConnectionInfo& orig) = delete;
        virtual ~ConnectionInfo() = default;

        static void SetNonBlock(int nfd)throw (SocketExceptionSetOptionFailed&) {
            int oldFcntl = ::fcntl(nfd, F_GETFD, 0);
            if (FAILED(::fcntl(nfd, F_SETFL, oldFcntl | O_NONBLOCK))) {
                  throw  SocketExceptionSetOptionFailed(errno,nfd);
            }
           
        }

        //TCP_NODELAY- If set, disable the Nagle algorithm. 
        //This means that segments are always sent as soon as possible,
        //even if there is only a small amount of data. When not set, 
        //data is buffered until there is a sufficient amount to send out,
        //thereby avoiding the frequent sending of small packets, which results in poor utilization of the network. This option is overridden by TCP_CORK;
        static inline void SetNoDelay(int nfd) throw (SocketExceptionSetOptionFailed&) {
            int flag = 1;
            socklen_t optLength = sizeof (flag);
            if (::setsockopt(nfd, IPPROTO_TCP, TCP_NODELAY,
                    reinterpret_cast<char*> (&flag), optLength) < 0) {
                throw  SocketExceptionSetOptionFailed(errno,nfd);
            }

        }

        //this setting will affect the close function, if enabled ,the close function will wait for the specified time to
        //let the system to send the pending data and close this connection successfully
        static inline void SetLinger(int nfd) throw (SocketExceptionSetOptionFailed&) {
            linger myLinger;
            myLinger.l_onoff = 1;
            myLinger.l_linger = 5;
            if (FAILED(::setsockopt(nfd, SOL_SOCKET, SO_LINGER,
                    reinterpret_cast<char*> (&myLinger), sizeof (linger)) ) ) {
                throw SocketExceptionSetOptionFailed(errno,nfd);
            }
        }
        

        //Reuse means this pair of ip and port will be reusable.
        static inline void SetReuseAddress(int nfd) throw(SocketExceptionSetOptionFailed&) {
            int opt = 1;
            int nRet = ::setsockopt(nfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt));
            if (FAILED(nRet))
                throw SocketExceptionSetOptionFailed(errno,nfd);
        }
        
        void ConcatenateBufferToUnwrittenBuffer(const char* npBuf,int nOffset,int nLen);
        void CopyBufferToReadedBuffer(const char* npBuf,int nOffset, int nLen);
    public:
        void Set(int nSocketm,EPollObject * nObject);
              
      
        //Send a input buffer
        eErrorCode Send() throw(SocketExceptionWriteFaild&);
        
        eErrorCode Send(const char* npBuf ,const int nLen) 
                throw(std::invalid_argument&,SocketExceptionWriteFaild&,EpollExceptionCtlFailed&);
        
        void Recieve(void * npEventHandler) 
          throw (SocketExceptionReadFaild&, LogicalExceptionInvalidObject&, LogicalExceptionNoEngoughBuffer&) ;
     private:
       
        int mnSocketHandle;
        int mnSizeOfKernalReadBuffer;
        int mnSizeOfKernalWriteBuffer;
        long mLastActiveTime;
        EPollObject * mpEpollObject;
        std::vector<char>  mReadBuffer;
        int  mnReadLen;
        std::vector<char> mUnwrittenBuffer;
        int mnUnwrittenLen;

    };
}
#endif /* SOCKETINFO_H */

