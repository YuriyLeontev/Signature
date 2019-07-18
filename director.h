/*
=============================================================================
   Signature - The program that generates the signature file
-----------------------------------------------------------------------------
   File: director.h   Created: 2019/07/15
-----------------------------------------------------------------------------
   Authors: Y. A. Leontev
=============================================================================
*/

/**
 \file director.h
 \brief Файл содержит объявление класса Director
 \author Y. A. Leontev
 \date 2018.07.15
*/

#ifndef SIGNATURE_DIRECTOR_H
#define SIGNATURE_DIRECTOR_H

#include <iostream>
#include <fstream> 
#include <functional>
#include <iterator>
#include <string>
#include <memory>
#include <thread>
#include <vector>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <experimental/filesystem>

#include "signCreator.h"

namespace fs = std::experimental::filesystem;
using namespace boost::interprocess;
using namespace std;

/**
 \class Director
 \brief Основной класс-распорядитель
 \author Y. A. Leontev
 \date 2019.07.15
*/
class Director {
public:
   Director() = default;
   ~Director();

   Director(const Director&) = delete;
   Director(const Director&&) = delete;

   Director& operator=(Director&&) = delete;
   Director& operator=(Director&) = delete;

   /* Основной метод, выполняющий подготовку к вычислению sig */
   void start(const string src,const string dst, const uint szBlock= 1048576);

private:
   static const uint process; /* Количество процессов */
   string dstPath; /* Путь к выходному файлу */

   std::shared_ptr<file_mapping> map_file; /* Указатель на FileMapping */
   std::vector<std::shared_ptr<SignCreator>> sigs; /* Вектор экземпляров класса расчёта Sig */

   void run();  /* Метод расчёта Sig */
   void save(); /* Метод для сохранения резульата в выходной файл */
};



#endif /* SIGNATURE_DIRECTOR_H */