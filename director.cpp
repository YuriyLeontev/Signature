/*
=============================================================================
   Signature - The program that generates the signature file
-----------------------------------------------------------------------------
   File: director.cpp   Created: 2019/07/15
-----------------------------------------------------------------------------
   Authors: Y. A. Leontev
=============================================================================
*/

/**
 \file director.cpp
 \brief Файл содержит реализацию класса Director
 \author Y. A. Leontev
 \date 2018.07.15
*/

#include "director.h"
#include "crc32Hash.h"

Director::~Director(){

}

void Director::start(const string src,const string dst,const uint szBlock){

    SignCreator sig(szBlock);
    
    this->pathSrc = src;
    this->pathDst = dst;

    try{
        this->sizeFile = fs::file_size(pathSrc);
        this->map_file = make_shared<file_mapping>(pathSrc.data(),read_only);

        int count1 = process-sizeFile%process; // sizeFile/proces элем
        int count2 = sizeFile%process; // sizeFile/proces +1 элем
        size_t offset{0};

        cout << "sizeFile " << sizeFile << " count1 " << count1 << " count2 " <<count2 << endl;

        while(count2--){
            regions.emplace_back(make_shared<mapped_region>(*(map_file.get()),read_only,
             offset, sizeFile/process + 1 ));
            offset += sizeFile/process + 1;
        }

        while(count1--){
            regions.emplace_back(make_shared<mapped_region>(*(map_file.get()),read_only,
             offset, sizeFile/process));            
            offset += sizeFile/process;
        }


    }catch(fs::filesystem_error& e) {
        std::cout << e.what() << '\n';
        return;
    }catch(interprocess_exception& e){
        std::cout << e.what() << '\n';
        return;
    }

    vector<std::thread> v;

      for (auto &it: regions){
        //sig.run(it);
        v.emplace_back(std::bind(&SignCreator::run, &sig, it));
      }

      for (auto &t : v) {t.join();}
        
      cout <<"fin" << endl; 
}