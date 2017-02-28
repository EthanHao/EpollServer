/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EventHandleInterface.h
 * Author: ethan
 *
 * Created on February 25, 2017, 3:32 PM
 */

#ifndef EVENTHANDLEINTERFACE_H
#define EVENTHANDLEINTERFACE_H

#include "Event.h"
namespace CTCPSERVER {
    class IEventHandler{
    public:
        virtual bool HandleEvent(const Event & nEvent,void * npReactor) = 0;
       
    };
}


#endif /* EVENTHANDLEINTERFACE_H */

