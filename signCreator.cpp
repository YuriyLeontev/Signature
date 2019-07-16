/*
=============================================================================
   Signature - The program that generates the signature file
-----------------------------------------------------------------------------
   File: signCreator.cpp   Created: 2019/07/15
-----------------------------------------------------------------------------
   Authors: Y. A. Leontev
=============================================================================
*/

/**
 \file signCreator.cpp
 \brief Файл содержит реализацию класса SignCreator
 \author Y. A. Leontev
 \date 2018.07.15
*/

#include "signCreator.h"
#include "crc32Hash.h"

#include "pcout.h"

SignCreator::SignCreator(std::shared_ptr<mapped_region> _region,uint szBlock):
region(_region), 
sizeBlock(szBlock),
checkSum(make_unique<Crc32Hash<uint32>>()),
eptr(nullptr){
   
}

SignCreator::~SignCreator(){
   sig.clear();
}

void SignCreator::run(){
   try{
      sig.clear();
      std::size_t size  = region.get()->get_size(); 
      size_t countBlock = size / sizeBlock;    

      const unsigned char *mem = static_cast<unsigned char*>(region.get()->get_address());
      
      if (!countBlock){
         sig.emplace_back(checkSum.get()->calc(mem, size%sizeBlock));       
      }
      else{
         while (countBlock--){
            sig.emplace_back(checkSum.get()->calc(mem, sizeBlock));   
            mem+=sizeBlock;
         }
         if (size%sizeBlock)
            sig.emplace_back(checkSum.get()->calc(mem, size%sizeBlock));       
      }
   }catch(...){
      eptr = std::current_exception();
   }
}

vector<uint32> & SignCreator::getResult(){
   return sig;
}

std::exception_ptr & SignCreator::getError(){
   return eptr;
}