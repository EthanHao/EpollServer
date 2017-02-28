/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "Event.h"
#include "EventHandleInterface.h"
namespace CTCPSERVER {
    //Do this event in the context of threadpool
    void Event::doit(){
            if(mpEventHandler)
                static_cast<IEventHandler*>(mpEventHandler)->HandleEvent(*this,mpReactor);
        }
}