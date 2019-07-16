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

class Director {
public:
    Director() = default;
    ~Director();

    Director(const Director&) = delete;
    Director(const Director&&) = delete;

    Director& operator=(Director&&) = delete;
    Director& operator=(Director&) = delete;

    void start(const string src,const string dst, const uint szBlock= 1048576);
    
private:
    static const uint process;
    string dstPath;

    std::shared_ptr<file_mapping> map_file;
    std::vector<std::shared_ptr<SignCreator>> sigs;

    void run();
    void save();
};



#endif /* SIGNATURE_DIRECTOR_H */