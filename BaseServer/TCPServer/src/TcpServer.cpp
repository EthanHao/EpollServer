/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TcpServer.cpp
 * Author: ethan
 * 
 * Created on January 30, 2017, 6:12 PM
 */

#include "TcpServer.h"
#include "ReactorCenter.h"
namespace CTCPSERVER {

    TcpServer::TcpServer(const std::string& nIP, int nPort,int nNumDealer,int nMaxSocketSizePerReactor,int nNumOfWorkerPerReactor,const std::vector<ServerInfo> & nBackServers)throw(SocketExceptionCreateFailed&,
                SocketExceptionSetOptionFailed&,
                SocketExceptionBindFailed&,
                SocketExceptionListenFailed&,
                EpollExceptionCreateFailed&,
                EpollExceptionCtlFailed&,
                std::bad_alloc&,
                ThreadExceptionCreateFailed&,
                LogicalExceptionTooManyBackendServer&,
                LogicalExceptionNoBackendServer&) {
        
        std::unique_ptr<IReactorCenterInterface> lpCenter(new ReactorCenter(nNumDealer,
                nMaxSocketSizePerReactor,
                nNumOfWorkerPerReactor,
                nBackServers));
        mpReactorCenter = std::move(lpCenter);
        
        std::unique_ptr<ConnectionListener> lpListener(new ConnectionListener(nIP,
                nPort,
                nNumDealer*nMaxSocketSizePerReactor,
                mpReactorCenter.get()));
        mpListener = std::move(lpListener);
    }


    
    eErrorCode TcpServer::Stop(){
        if(mpListener)
            mpListener->StopAndWait();
        if(mpReactorCenter)
            mpListener->StopAndWait();
    }
            
}
