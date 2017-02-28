/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MemoryPool.h
 * Author: ethan
 *
 * Created on February 15, 2017, 7:29 PM
 */

#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H
#include <vector>
#include <memory>
namespace CTCPSERVER {
    template <typename T > class MemoryPool {
        public  :
            MemoryPool(int nSize) throw (std::bad_alloc&) : mnSize(nSize){
                std::unique_ptr<T[]> lp (new T[mnSize]);
                mArrayBuffer = std::move(lp);
                mnFreeSize = mnSize;
                for(int i = 0; i < mnSize ; i++)
                    mBitSet.push_back(false);
                    
            }
            
            T* alloc()  {
                if(!mArrayBuffer)
                    return nullptr;
                //check a empty slot in the bitset
                for(int i = 0 ; i < mnSize ; i++)
                {
                    if(mBitSet[i] == false)
                    {
                        mnFreeSize--;
                        mBitSet[i] = true;
                        return &mArrayBuffer[i]; 
                    }
                }
                return nullptr;
            }
            void free(T* np) {
                if(!mArrayBuffer)
                    return ;
                if(np != nullptr && 
                        ( np >= &mArrayBuffer[0] && np <= &mArrayBuffer[mnSize-1]) ){
                    int offset = (np- &mArrayBuffer[0]) % sizeof(T);
                    mBitSet[offset] = false;
                    mnFreeSize++;
                } 
            }
            int GetFreeSize() {return mnFreeSize;}
        private:
            const int mnSize;
            int mnFreeSize;
            std::vector<bool> mBitSet;
            std::unique_ptr<T[]> mArrayBuffer;
                   
    };
}

#endif /* MEMORYPOOL_H */

