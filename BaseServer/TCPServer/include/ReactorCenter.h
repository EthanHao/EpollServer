/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReactorCenter.h
 * Author: ethan
 *
 * Created on February 14, 2017, 7:34 PM
 */

#ifndef DATADEALERCENTER_H
#define DATADEALERCENTER_H
#include "ErrorCode.h"
#include "Reactor.h"
#include "ConnectionInfo.h"
#include <vector>
#include <map>
#include <mutex>
#include "MemoryPool.h"
#include "ReactorCenterInterface.h"
//Create a bunch of Dealers 
//Dispatch socket to a specified dealer
//for simplicity this class could be singleton 
namespace CTCPSERVER {

    class ReactorCenter : public IReactorCenterInterface{
    public:
        ReactorCenter(int nNum,int nMaxSocketSizePerReactor,int nNumOfWorks,const std::vector<ServerInfo> & nBackServers)throw (EpollExceptionCreateFailed&,
                std::bad_alloc&,
                ThreadExceptionCreateFailed&,
                LogicalExceptionTooManyBackendServer&,
                LogicalExceptionNoBackendServer&,
                SocketExceptionCreateFailed&,
                SocketExceptionP2NWrongFormat&,
                SocketExceptionP2NFailed&,
                SocketExceptionConnectFailed&,
                SocketExceptionSetOptionFailed&);
        ReactorCenter(const ReactorCenter& orig) = delete;
        virtual ~ReactorCenter() = default;
        
        //Add a Socket File Descriptor to deal with its reading or writing operation
        virtual eErrorCode DispatchSocket(int nfd) 
            throw(LogicalExceptionNoEmptyRoonInMemoryPool&,EpollExceptionCtlFailed&);
       
        //Stop the dealer
        eErrorCode StopDealers();
    private:

        const int mnNumOfReactors;
        const int mnMaxSocketSizePerReactor;
     
        std::vector<std::unique_ptr<Reactor>> mpReactors;
        std::mutex mMutex;
        
    };
}
#endif /* DATADEALERCENTER_H */

