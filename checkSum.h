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

/**
 \class CheckSum
 \brief Базовый класс для классов расчёта Sig
 \author Y. A. Leontev
 \date 2019.07.15
*/
template<class T>
class CheckSum {
public:
   CheckSum() = default;
   virtual ~CheckSum() = default;

   CheckSum(const CheckSum&) = delete;
   CheckSum(const CheckSum&&) = delete;

   CheckSum& operator=(CheckSum&&) = delete;
   CheckSum& operator=(CheckSum&) = delete;

   /* Метод для расчёта конртольной суммы */
   virtual T calc(const unsigned char *data, const size_t) const = 0;
};

#endif /* CHECK_SUM_H */