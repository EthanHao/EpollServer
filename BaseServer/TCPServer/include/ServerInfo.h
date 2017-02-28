/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerInfo.h
 * Author: ethan
 *
 * Created on February 23, 2017, 11:49 AM
 */

#ifndef SERVERINFO_H
#define SERVERINFO_H

namespace CTCPSERVER {
    class ServerInfo {
        
        private:
            const std::string msName;
            const std::string msIP;
            const int mnPort;
            
        public:
            ServerInfo(const std::string& nsName,
                    const std::string & nsIp,
                    int nPort) :
                    msName(nsName),
                    msIP(nsIp),
                    mnPort(nPort){
                
            }
            const std::string & GetName() { return msName;}
            const std::string& GetIP() {return msIP;}
            const int GetPort() {return mnPort;}
            bool IsEnd() { return msIP.empty();}
            
    };
}

#endif /* SERVERINFO_H */

