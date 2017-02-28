/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest.cpp
 * Author: ethan
 *
 * Created on February 4, 2017, 7:05 PM
 */

#include <stdlib.h>
#include <iostream>

#include "../include/log.h"

/*
 * Simple C++ Test Suite
 */

int main(int argc, char** argv) {


    try {
        
        CLOG::Log::GetInstance()->Init("/home/ethan/log");

        for (int i = 0; i < 10; i++)
            CLOG::Log::GetInstance()->Logging(CLOG::LogFile::LogLevel::LogDebug, "try to output debug %d", i);

        for (int i = 0; i < 10; i++)
            CLOG::Log::GetInstance()->Logging(CLOG::LogFile::LogLevel::LogInfo, "try to output info %d", i);

        for (int i = 0; i < 10; i++)
            CLOG::Log::GetInstance()->Logging(CLOG::LogFile::LogLevel::LogWarnning, "try to output warning %d", i);

        for (int i = 0; i < 10; i++)
            CLOG::Log::GetInstance()->Logging(CLOG::LogFile::LogLevel::LogFatal, "try to output fatal %d", i);
        
    }    catch (CLOG::FileNotExistingException & e) {
        std::cout << e.what() << std::endl;
        return (EXIT_FAILURE);
    }    catch (CLOG::FileNotEditableException & e) {
        std::cout << e.what() << std::endl;
        return (EXIT_FAILURE);
    }    catch (CLOG::FileOpenFailedException & e) {
        std::cout << e.what() << std::endl;
        return (EXIT_FAILURE);
    }    catch (CLOG::FileWriteFailedException & e) {
        std::cout << e.what() << std::endl;
        return (EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}

