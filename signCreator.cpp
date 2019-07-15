/*
=============================================================================
   Signature - The program that generates the signature file
-----------------------------------------------------------------------------
   File: signCreator.cpp   Created: 2019/07/15
-----------------------------------------------------------------------------
   Authors: Y. A. Leontev
=============================================================================
*/

/**
 \file signCreator.cpp
 \brief Файл содержит реализацию класса SignCreator
 \author Y. A. Leontev
 \date 2018.07.15
*/

#include "signCreator.h"
#include "crc32Hash.h"

#include "pcout.h"

SignCreator::SignCreator(uint szBlock): sizeBlock(szBlock){}

SignCreator::~SignCreator(){

}

void SignCreator::run(std::shared_ptr<mapped_region>  &region){
    //cout << "region use"<< region.use_count()<<endl;

    void * addr       = region.get()->get_address();
    std::size_t size  = region.get()->get_size(); 

 //   pcout{} << "region size "<< size<<endl;

    const char *mem = static_cast<char*>(addr);

    vector<char> vec;
    for(std::size_t i = 0; i < size; i++){
        vec.emplace_back(mem[i]);;
    }      

    std::ostream_iterator<char> out_it (std::cout,", ");
    std::copy(vec.begin(),vec.end(),out_it  );  
    cout << endl;  
}