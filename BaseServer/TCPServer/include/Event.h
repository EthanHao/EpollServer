/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Event.h
 * Author: ethan
 *
 * Created on February 25, 2017, 11:17 AM
 */

#ifndef EVENT_H
#define EVENT_H
#include "EPollObject.h"

namespace CTCPSERVER {
    
    class Event{
    private:
        struct epoll_event mepollEvent;
        void *mpEventHandler;
        void *mpReactor;
    public:
        Event(){
            memset(&mepollEvent,0,sizeof(mepollEvent));
            mpEventHandler = nullptr;
            mpReactor = nullptr;
        }
        Event(const struct epoll_event & nEpollEvent,void* npHandler,void * npReactor ){
            memcpy(&mepollEvent,&nEpollEvent,sizeof(mepollEvent));
            mpEventHandler = npHandler;
            mpReactor = npReactor;
        }
        void doit(); 
        
        uint32_t GetEventType() const {
            return mepollEvent.events;
        }
        void * GetConnectionInfo() const{
            return mepollEvent.data.ptr;
        }
        int GetSocketFileDescriptor() const{
            return mepollEvent.data.fd;
        }
        void* GetReactor() const{
            return mpReactor;
        }
        
    };
}

#endif /* EVENT_H */

