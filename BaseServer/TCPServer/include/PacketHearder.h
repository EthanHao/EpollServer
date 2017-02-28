/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PacketHearder.h
 * Author: ethan
 *
 * Created on February 24, 2017, 9:26 AM
 */

#ifndef PACKETHEARDER_H
#define PACKETHEARDER_H

namespace CTCPSERVER {
    
//Using Pack(1) to pack the structure, and using Big-endian
const unsigned int HEADID = 0x7caa5caa;
const unsigned int TAIDID =  0xaa55ca81;
#pragma pack(push)
#pragma pack(1)  

    struct PacketHeader {
        unsigned int mnHeadID;
        unsigned int mnContentLen;
        ushort mnContentType;
        ushort mnConpressType;
        long long mllSeq;
        

        //Test this buffer whether it is a valid package
        static bool IsValidPkg(const char* npBuffer, int nLen) {
            if (!npBuffer || nLen < (int) sizeof (PacketHeader) + sizeof(TAIDID))
                return false;

            const PacketHeader *lpHeader = (const PacketHeader*) npBuffer;
            if (lpHeader->mnHeadID != HEADID ||
                    nLen < (int) sizeof (PacketHeader) + lpHeader->mnContentLen + sizeof(TAIDID) ||
                    *reinterpret_cast<const unsigned int*> ( npBuffer + sizeof (PacketHeader) + lpHeader->mnContentLen) != TAIDID)
                return false;
            return true;
        }
        
        int GetWholePacketLenght() {
            return  (int) sizeof (PacketHeader) + mnContentLen + sizeof(TAIDID);
        }
        
       
    };
    
    
  
#pragma pack(pop)   
}

#endif /* PACKETHEARDER_H */

