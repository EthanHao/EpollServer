/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../include/log.h"

using namespace CLOG;


Log* Log::_instance = nullptr;
std::mutex Log::_singleMutex;
