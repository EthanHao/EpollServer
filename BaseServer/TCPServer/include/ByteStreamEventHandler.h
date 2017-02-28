/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ByteStreamEventHandler.h
 * Author: ethan
 *
 * Created on February 25, 2017, 5:55 PM
 */

#ifndef BYTESTREAMEVENTHANDLER_H
#define BYTESTREAMEVENTHANDLER_H
#include <memory>
#include "EventHandleInterface.h"
#include "StreamCheckerInterface.h"

namespace CTCPSERVER {

    class BytestreamEevetHandler : public IEventHandler {

        class  BytestreamChecker : public IStreamChecker{
        public:
            BytestreamChecker() {
            };
            virtual int operator()(char * const lp, int nLen) noexcept;
        };

    public:
        BytestreamEevetHandler() {
            std::unique_ptr<IStreamChecker> lpChecker(new BytestreamChecker());
            mpBytestreamChecker = std::move(lpChecker);
        }
        virtual bool HandleEvent(const Event & nEvent, void * npReactor);
        
    private:
        std::unique_ptr<IStreamChecker> mpBytestreamChecker;

    };
}

#endif /* BYTESTREAMEVENTHANDLER_H */

