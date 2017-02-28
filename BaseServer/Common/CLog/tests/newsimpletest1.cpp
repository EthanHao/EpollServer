/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newsimpletest1.cpp
 * Author: ethan
 *
 * Created on February 4, 2017, 7:40 PM
 */

#include <stdlib.h>
#include <iostream>
#include <thread>
#include "../include/log.h"
/*
 * Simple C++ Test Suite
 */
int log(int i)
{
     try {
        CLOG::Log::GetInstance()->Init("/home/ethan/log");
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        for (int i = 0; i < 1000; i++)
            CLOG::Log::GetInstance()->Logging(CLOG::LogFile::LogLevel::LogDebug, "thread try to output debug %d", i);

        for (int i = 0; i < 100; i++)
            CLOG::Log::GetInstance()->Logging(CLOG::LogFile::LogLevel::LogInfo, "thread try to output info %d", i);

        for (int i = 0; i < 1000; i++)
            CLOG::Log::GetInstance()->Logging(CLOG::LogFile::LogLevel::LogWarnning, "thread try to output warning %d", i);

        for (int i = 0; i < 100; i++)
            CLOG::Log::GetInstance()->Logging(CLOG::LogFile::LogLevel::LogFatal, "thread try to output fatal %d", i);
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
}

int main(int argc, char** argv) {
    
    std::vector<std::unique_ptr<std::thread>> lvec;
    for(int i = 0; i < 10 ;i++)
    {
        std::unique_ptr<std::thread>  t (new std::thread(log, i));
        lvec.push_back(std::move(t));
    }
    for(int i = 0; i < 10 ;i++)
    {
        lvec[i]->join();
    }   
    return (EXIT_SUCCESS);
}

