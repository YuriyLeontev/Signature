/*
=============================================================================
   Signature - The program that generates the signature file
-----------------------------------------------------------------------------
   File: checkSum.h   Created: 2019/07/15
-----------------------------------------------------------------------------
   Authors: Y. A. Leontev
=============================================================================
*/

/**
 \file checkSum.h
 \brief Файл содержит объявление базового класса CheckSum
 \author Y. A. Leontev
 \date 2018.07.15
*/

#ifndef CHECK_SUM_H
#define CHECK_SUM_H

#include <iostream>

class CheckSum {
public:
    CheckSum() = default;
    virtual ~CheckSum();

    CheckSum(const CheckSum&) = delete;
    CheckSum(const CheckSum&&) = delete;

    CheckSum& operator=(CheckSum&&) = delete;
    CheckSum& operator=(CheckSum&) = delete;

    virtual int calc(unsigned char *data, size_t) const = 0;
};



#endif /* CHECK_SUM_H */