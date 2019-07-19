/*
=============================================================================
   Signature - The program that generates the signature file
-----------------------------------------------------------------------------
   File: signCreator.h   Created: 2019/07/15
-----------------------------------------------------------------------------
   Authors: Y. A. Leontev
=============================================================================
*/

/**
 \file signCreator.h
 \brief Файл содержит объявление класса SignCreator предназначенный для генерации Sig файла
 \author Y. A. Leontev
 \date 2018.07.15
*/

#ifndef SIGN_CREATOR_H
#define SIGN_CREATOR_H

#include <memory>
#include <vector>
#include <stdexcept>

#include <boost/interprocess/mapped_region.hpp>

#include "checkSum.h"

using namespace boost::interprocess;

typedef __UINT32_TYPE__  uint32;   


/**
 \class SignCreator
 \brief Класс расчёта sig региона файла
 \author Y. A. Leontev
 \date 2019.07.15
*/
class SignCreator {
public:
   /* Конструктор класса */
   SignCreator(std::shared_ptr<mapped_region> _region, const uint szBlock);
   ~SignCreator();

   SignCreator(const SignCreator&) = delete;
   SignCreator(const SignCreator&&) = delete;

   SignCreator& operator=(SignCreator&&) = delete;
   SignCreator& operator=(SignCreator&) = delete;

   void run(); /* Метод высисления sig */

   const std::vector<uint32> & getResult() const; /* Возвращает ссылку на вектор поситанных sig */
   const std::exception_ptr & getError() const; /* Возвращает ссылку на exception_ptr */

private:
   std::shared_ptr<mapped_region> region; /* Регион файла */
   const size_t sizeBlock; /* размер блока */
   std::unique_ptr<CheckSum<uint32>> checkSum;   /* Экземпляр класса для подсчёта sig */
   std::vector<uint32> sig; /* Результирующий вектор, содержащий sig */
    
   std::exception_ptr eptr; /* переменная для сохранения ошибки и передачи в основной поток */
};



#endif /* SIGN_CREATOR_H */