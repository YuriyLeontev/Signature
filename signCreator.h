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
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "checkSum.h"

using namespace boost::iostreams;
using namespace boost::interprocess;
using namespace std;

class SignCreator {
public:
    SignCreator(uint szBlock);
    ~SignCreator();

    SignCreator(const SignCreator&) = delete;
    SignCreator(const SignCreator&&) = delete;

    SignCreator& operator=(SignCreator&&) = delete;
    SignCreator& operator=(SignCreator&) = delete;

    void run(std::shared_ptr<mapped_region>  &region);

private:
    const uint sizeBlock;    
};



#endif /* SIGN_CREATOR_H */