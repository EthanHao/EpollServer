/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exception.h
 * Author: ethan
 *
 * Created on February 1, 2017, 9:25 AM
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <string>

namespace CLOG {

    class FileException : public std::exception {
    public:

        FileException(const std::string& nsMsg) : _errorMsg(nsMsg) {
        }
        // overriden what() method from exception class

        const char* what() const throw () {
            return _errorMsg.c_str();
        }
    private:
        const std::string _errorMsg;
     
    };

    class FileNotExistingException : public FileException {
    public:

        FileNotExistingException(const std::string& nfilepath) : FileException(nfilepath + " File Not Existing") {
        }
     
    };

    class FileNotEditableException : public FileException {
    public:

        FileNotEditableException(const std::string& nfilepath) : FileException(nfilepath + " File Not Editable") {
        }
   
    };

    class FileOpenFailedException : public FileException {
    public:

        FileOpenFailedException(const std::string& nfilepath) : FileException(nfilepath + " File Open Failed") {
        }
       
    };

    class FileWriteFailedException : public FileException {
    public:

        FileWriteFailedException(const std::string& nfilepath) : FileException(nfilepath+ " File Write Failed") {
        }
      

    };

}
#endif /* EXCEPTION_H */

