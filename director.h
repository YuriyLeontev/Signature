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
#include <string>
#include <memory>
#include <future>
#include <thread>
#include <vector>

#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <experimental/filesystem>

#include "signCreator.h"

namespace fs = std::experimental::filesystem;
using namespace boost::iostreams;
using namespace boost::interprocess;
using namespace std;

class Director {
public:
    Director() = default;
    ~Director();

    Director(const Director&) = delete;
    Director(const Director&&) = delete;

    Director& operator=(Director&&) = delete;
    Director& operator=(Director&) = delete;

    void start(const string src,const string dst, const uint szBlock=1);

    void run();

private:
    const uint process = 4;

    size_t sizeFile;
    string pathSrc;
    string pathDst;

    std::shared_ptr<file_mapping> map_file;

    std::vector<std::shared_ptr<mapped_region>> regions;
};



#endif /* SIGNATURE_DIRECTOR_H */