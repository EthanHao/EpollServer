/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StreamCheckerInterface.h
 * Author: ethan
 *
 * Created on February 26, 2017, 12:53 PM
 */

#ifndef STREAMCHECKERINTERFACE_H
#define STREAMCHECKERINTERFACE_H
namespace CTCPSERVER {
   class  IStreamChecker{
        public:
            virtual int operator()(char * const lp, int nLen) noexcept = 0 ;
        };
}

#endif /* STREAMCHECKERINTERFACE_H */

