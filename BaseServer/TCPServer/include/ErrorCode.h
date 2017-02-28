/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ErrorCode.h
 * Author: ethan
 *
 * Created on January 30, 2017, 6:07 PM
 */

#ifndef ERRORCODE_H
#define ERRORCODE_H
namespace CTCPSERVER {
#define BASE_ERROR 0x400

    
enum eErrorCode {
        eSuccess = 0,
        eIsRunning = BASE_ERROR,
        eInvalidObject = BASE_ERROR + 1,
        eMemoryPoolIsFull ,
        eBufferAllSent,
        eBufferNotAllSent,

    };
}

#endif /* ERRORCODE_H */

