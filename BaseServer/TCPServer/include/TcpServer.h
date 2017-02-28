/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TcpServer.h
 * Author: ethan
 *
 * Created on January 30, 2017, 6:12 PM
 */

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "ConnectionListener.h"
#include "ReactorCenterInterface.h"
#include "ServerInfo.h"
#include <vector>
namespace CTCPSERVER {
    //Tcp server is a concrete Iserver.
    //get a connection lister object
    //get a DataDealerPool

    class TcpServer {
    public:
        TcpServer(const std::string& nIP, int nPort,int nNumDealer,int nMaxSocketSizePerReactor,int nNumOfWorkerPerReactor,const std::vector<ServerInfo> & nBackServers)throw(SocketExceptionCreateFailed&,
                SocketExceptionSetOptionFailed&,
                SocketExceptionBindFailed&,
                SocketExceptionListenFailed&,
                EpollExceptionCreateFailed&,
                EpollExceptionCtlFailed&,
                std::bad_alloc&,
                ThreadExceptionCreateFailed&,
                LogicalExceptionTooManyBackendServer&,
                LogicalExceptionNoBackendServer&) ;
        
        TcpServer(const TcpServer& orig) = delete;
        virtual ~TcpServer() = default;
      
        eErrorCode Stop();
    private:
        std::unique_ptr<ConnectionListener> mpListener;
        std::unique_ptr<IReactorCenterInterface> mpReactorCenter;
    };
}
#endif /* TCPSERVER_H */

