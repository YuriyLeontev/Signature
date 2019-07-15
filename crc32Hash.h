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

#include "checkSum.h"

typedef __INT32_TYPE__  int32;

class Crc32Hash: public CheckSum {
public:   
    Crc32Hash() = default;
    ~Crc32Hash();

    Crc32Hash(const Crc32Hash&) = delete;
    Crc32Hash(const Crc32Hash&&) = delete;

    Crc32Hash& operator=(Crc32Hash&&) = delete;
    Crc32Hash& operator=(Crc32Hash&) = delete;

    virtual int calc(unsigned char *pData, size_t uSize) const  override final;   

private:
    static const unsigned long Crc32Tab[];
};


#endif /* CRC_32_HASH_H */
