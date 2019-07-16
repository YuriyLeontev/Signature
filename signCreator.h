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

#include <iostream>
#include <string>
#include <memory>
#include <atomic>
#include <stdexcept>

#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "checkSum.h"

using namespace boost::iostreams;
using namespace boost::interprocess;
using namespace std;

typedef __UINT32_TYPE__  uint32;   

class SignCreator {
public:
    SignCreator(std::shared_ptr<mapped_region> _region, const uint szBlock);
    ~SignCreator();

    SignCreator(const SignCreator&) = delete;
    SignCreator(const SignCreator&&) = delete;

    SignCreator& operator=(SignCreator&&) = delete;
    SignCreator& operator=(SignCreator&) = delete;

    void run();
    vector<uint32> & getResult();

   std::exception_ptr & getError();

private:
    std::shared_ptr<mapped_region> region;
    const size_t sizeBlock;
    std::unique_ptr<CheckSum<uint32>> checkSum;   
    vector<uint32> sig;
    
   std::exception_ptr eptr;
};



#endif /* SIGN_CREATOR_H */