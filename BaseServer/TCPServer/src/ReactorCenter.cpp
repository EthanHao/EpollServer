/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReactorCenter.cpp
 * Author: ethan
 * 
 * Created on February 14, 2017, 7:34 PM
 */

#include "../include/ReactorCenter.h"
#include <limits>
namespace CTCPSERVER {

    ReactorCenter::ReactorCenter(int nNum,int nMaxSocketSizePerReactor,int nNumOfWorks,const std::vector<ServerInfo> & nBackServers)throw (EpollExceptionCreateFailed&,
                std::bad_alloc&,
                ThreadExceptionCreateFailed&,
                LogicalExceptionTooManyBackendServer&,
                LogicalExceptionNoBackendServer&,
                SocketExceptionCreateFailed&,
                SocketExceptionP2NWrongFormat&,
                SocketExceptionP2NFailed&,
                SocketExceptionConnectFailed&,
                SocketExceptionSetOptionFailed&):
                    mnNumOfReactors(nNum),
                    mnMaxSocketSizePerReactor(nMaxSocketSizePerReactor){
        
        if(nBackServers.size() > nNum)
            throw LogicalExceptionTooManyBackendServer(0,nBackServers.size());
        if(nBackServers.size() == 0)
            throw LogicalExceptionNoBackendServer(0);
        
        //Create a bunch of dealer
        int nSizeOfBackendServer = nBackServers.size();
        for(int i = 0 ; i < mnNumOfReactors ; i++)
        {
            std::unique_ptr<Reactor> lpReactor(new Reactor(nMaxSocketSizePerReactor,nNumOfWorks));
            mpReactors.push_back(std::move(lpReactor));
        }
    }


    eErrorCode  ReactorCenter::DispatchSocket(int nfd)
            throw(LogicalExceptionNoEmptyRoonInMemoryPool&,EpollExceptionCtlFailed&){
        //Lock
        std::lock_guard<std::mutex> lock(mMutex);
        
        //Check Paremeters
        if( mpReactors.size() != mnNumOfReactors)
            return eErrorCode::eInvalidObject;
        //Find the least one using BF way, because of the small number of dealers
        int nMinSize = std::numeric_limits<int>::max();
        int nIndex = -1;
        for(int i = 0; i < mpReactors.size() ; i++)
        {
            int lnTemp = mpReactors[i]->GetFreeSize();
            if(lnTemp < nMinSize)
            {
                nMinSize = lnTemp;
                nIndex = i;
            }
        }
        //Assign this nfd to a Data Dealer
        return mpReactors[nIndex]->AddSocketItem(nfd);
        
    }
  
    //Stop the dealer
    eErrorCode ReactorCenter::StopDealers()
    {
        for(auto& p : mpReactors)
            p->StopAndWait();
        return eErrorCode::eSuccess;
    }
}

