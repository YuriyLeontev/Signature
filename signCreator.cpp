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

//#include <boost/crc.hpp>
//#include "pcout.h"


/* -----   SignCreator::SignCreator()   ------------------------------------------------- */
///   Конструктор класса
///   \param _region Регион файла
///   \param szBlock Размер блока
SignCreator::SignCreator(std::shared_ptr<mapped_region> _region,uint szBlock):
region(_region), 
sizeBlock(szBlock),
checkSum(std::make_unique<Crc32Hash<uint32>>()),
eptr(nullptr){
   
}

/* -----   SignCreator::~SignCreator()   ------------------------------------------------- */
///   Деструктор класса
SignCreator::~SignCreator(){
   sig.clear();
}

/* -----   SignCreator::run()   ------------------------------------------------- */
///   Метод высисления sig
void SignCreator::run(){
   sig.clear();
   std::size_t size  = region.get()->get_size(); 
   const unsigned char *mem = static_cast<unsigned char*>(region.get()->get_address());

   try{
      if (!sizeBlock) throw std::invalid_argument("size block 0 Mb");
      size_t countBlock = size / sizeBlock; 

      sig.reserve(countBlock); /* Заранее зарезирвируем память */

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

/* -----   SignCreator::getResult()   ------------------------------------------------- */
///   Метод возвращающий константную ссылку на вектор поситанных sig
///   @return ссылка на вектор с результатами вычислений
const std::vector<uint32> & SignCreator::getResult() const{
   return sig;
}

/* -----   SignCreator::getError()   ------------------------------------------------- */
///   Метод возвращающий константную ссылку на exception_ptr
///   @return ссылка на exception_ptr
const std::exception_ptr & SignCreator::getError() const{
   return eptr;
}