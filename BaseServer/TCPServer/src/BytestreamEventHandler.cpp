/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Event.h"
#include "ByteStreamEventHandler.h"
#include "ConnectionInfo.h"
#include "PacketHearder.h"
namespace CTCPSERVER {

    int BytestreamEevetHandler::BytestreamChecker::operator()(char * const lp, int nLen) noexcept{
        if(nLen < sizeof(PacketHeader))
            return 0;
        int lnOffset = 0;
        while(lnOffset <= nLen){
            //Jump some invalid data 
            while(!PacketHeader::IsValidPkg(lp+lnOffset,nLen-lnOffset)) 
                lnOffset++;
            
            //Find a valid packet and deal with this packet
            PacketHeader * lpHeader = reinterpret_cast<PacketHeader *>(lp+lnOffset);
            
            //Add the offset to find the next valid packet
            lnOffset += lpHeader->GetWholePacketLenght();
        }
        return lnOffset;
    }
    
    bool BytestreamEevetHandler::HandleEvent(const Event & nEvent,void * npReactor) {
        if(npReactor == nullptr || !mpBytestreamChecker)
            return false;
        
        ConnectionInfo * lpConInfo = static_cast<ConnectionInfo*>(nEvent.GetConnectionInfo());
        if(lpConInfo == nullptr)
            return false;
        
        uint32_t lnEventType = nEvent.GetEventType();
        if(lnEventType & EPOLLIN){
            lpConInfo->Recieve(mpBytestreamChecker.get());
        }else  if(lnEventType & EPOLLERR){
            //Close this socket
        }
        else  if(lnEventType & EPOLLOUT){
            lpConInfo->Send();
        }
        return true;
        
    }

}
