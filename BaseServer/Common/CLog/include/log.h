/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   log.h
 * Author: ethan
 *
 * Created on February 1, 2017, 1:34 PM
 */

#ifndef LOG_H
#define LOG_H

#include <cstdio>
#include <stdarg.h>
#include "LogFile.h"
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <memory>
#include <atomic>
#include <mutex>
namespace CLOG {

    //this log class will generate some log files everyday
    //each day we get a debug20170201.log , Info20170201.log, etc
    //the regulation of filename is using the prefix of LogLevle and plus the date of that day
    //the extension of all logs file is .log
    //and the log library is thread safety and well interfaced.

    //singleton pattern

    class Log {
    public:

    private:
        static Log* _instance;
        static std::mutex _singleMutex;

        //can not be constructed outside explicitly
        Log() = default;

        //can not be copy constructed
        Log(const Log&) = delete;
        //can not be copy assigned
        Log& operator=(const Log&) = delete;

        //No move constructor
        Log(Log&&) = delete;

        //No Move assignment
        Log& operator=(Log&&) = delete;

    
    private:
        std::string _fileDir = "";
        std::string _processId;
        std::mutex _initMutex;
        std::atomic<bool> _Initilized ;
        std::vector<std::unique_ptr<LogFile>> _vecFile;

    public:


        static Log* GetInstance() {
            //Double check
            if (_instance == nullptr) {
                //lock
                std::lock_guard<std::mutex> llock(_singleMutex);
                if (_instance == nullptr) {
                    _instance = new Log();
                    return _instance;
                }
            }
            return _instance;

        }
        
        //Init
        inline void Init(const std::string & nsDir)
        throw (FileNotExistingException&,
                FileNotEditableException&,
                std::invalid_argument&) {
            if (false != _Initilized)
                return;
            //Lock
            std::lock_guard<std::mutex> llock(_initMutex);
            
            //Add the LogFile ptr to the vector
            for (int i = LogFile::LogLevel::LogDebug; i <= LogFile::LogLevel::LogFatal; i++) {
                std::unique_ptr<LogFile> lp1(new LogFile(nsDir, static_cast<LogFile::LogLevel>(i)));
                _vecFile.push_back(std::move(lp1));
            }
            _Initilized = true;
        }

        //Log Debug
        inline bool Logging(const LogFile::LogLevel& nLogLevel,
                 const char *format,
                 ...) noexcept{
            
            if(_Initilized == false)
                return false;
            bool lbRet = true;
            try{
                va_list args;
                va_start(args, format);
                _vecFile[nLogLevel]->write(format,args);
                va_end(args);
               
            }
            catch(std::exception e){
                lbRet = false;
            }
            return lbRet;
            
        }

      
    };

}
#endif /* LOG_H */

