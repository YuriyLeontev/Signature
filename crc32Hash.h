/*
=============================================================================
   Signature - The program that generates the signature file
-----------------------------------------------------------------------------
   File: crc32Hash.h   Created: 2019/07/15
-----------------------------------------------------------------------------
   Authors: Y. A. Leontev
=============================================================================
*/

/**
 \file crc32Hash.h
 \brief Файл содержит объявление класса вычисления crc32
 \author Y. A. Leontev
 \date 2018.07.15
*/

#ifndef CRC_32_HASH_H
#define CRC_32_HASH_H

#include <iostream>

#include "checkSum.h"

typedef __UINT32_TYPE__  uint32;


/**
 \class Crc32Hash
 \brief Класс для расчёта Crc32
 \author Y. A. Leontev
 \date 2019.07.15
*/
template<class T>
class Crc32Hash: public CheckSum<T> {
public:   
   Crc32Hash() = default;
   ~Crc32Hash() = default;

   Crc32Hash(const Crc32Hash&) = delete;
   Crc32Hash(const Crc32Hash&&) = delete;

   Crc32Hash& operator=(Crc32Hash&&) = delete;
   Crc32Hash& operator=(Crc32Hash&) = delete;
   
   /* Метод для расчёта конртольной суммы */      
   virtual T calc(const unsigned char *pData,const size_t uSize) const  override final;   

private:
   static const unsigned long Crc32Tab[];
};


#endif /* CRC_32_HASH_H */
