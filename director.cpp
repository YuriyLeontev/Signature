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

/* Количество потоков 
   P.S Есть смысл параллелить если SSD
*/
const uint Director::process{4};


/* -----   Director::~Director()     ------------------------------------------- */
///   Деструктор класса.
Director::~Director(){
    sigs.clear();
}


/* -----   Director::start()   ------------------------------------------------- */
///   Основной метод, выполняющий подготовку к вычислению sig
///   \param src Путь к исходному файлу
///   \param dst Путь к выходному файлу
///   \param szBlock Размер блока
void Director::start(const string src,const string dst,const uint szBlock){
    this->dstPath = dst;
    
    try{
        if (!szBlock) throw std::invalid_argument("size block 0 Mb");

        /* Размер файла */
        size_t sizeFile = fs::file_size(src);
        
        /* Указатель на файл */
        this->map_file = make_shared<file_mapping>(src.data(),read_only);

        /* Количество блоков */
        size_t countBlock = (sizeFile%szBlock) ? (sizeFile/szBlock) + 1 : (sizeFile/szBlock);
            
        /* 
           Деление файла на $process частей жадным алгоритмом
           И создание объекта SignCreator для каждой части файла
        */

        /* countBlock/process блоков */
        int count1 = process-countBlock%process;
        /* countBlock/process + 1 блоков */
        int count2 = countBlock%process;

        if (countBlock < process){
            /* Тогда в одном потоке */
            count1 = count2 = 0;
            sigs.emplace_back(make_shared<SignCreator>(
                make_shared<mapped_region>(*(map_file.get()),read_only),
                szBlock)
            );
        }

        size_t offset{0}; 

        while(count2--){
            sigs.emplace_back(make_shared<SignCreator>(
                make_shared<mapped_region>(*(map_file.get()),read_only, offset, (countBlock/process + 1)*szBlock ), 
                szBlock));
            offset += (countBlock/process + 1)*szBlock;
        }

        while(count1--){
            /* Для того чтобы обрезать последний блок */
            if (offset + ((countBlock/process)*szBlock) > sizeFile){
                sigs.emplace_back(make_shared<SignCreator>(
                    make_shared<mapped_region>(*(map_file.get()),read_only, offset, sizeFile - offset ),
                    szBlock));
            }
            else{
                sigs.emplace_back(make_shared<SignCreator>(
                    make_shared<mapped_region>(*(map_file.get()),read_only, offset, (countBlock/process)*szBlock ),
                    szBlock));        
            }
            offset += (countBlock/process)*szBlock;
        }
    }catch(fs::filesystem_error& e) {
        std::cout << e.what() << '\n';
        return;        
    }catch(interprocess_exception& e){
        std::cout << e.what() << '\n';
        return;
    }catch(exception & e){
        std::cout << "error: " << e.what() << endl;
        return;
    }
    run();
}


/* -----   Director::run()   ------------------------------------------------- */
///   Метод для создания потоков и расчёта sig
void Director::run(){
    cout<< "Calculate signature " << map_file.get()->get_name() << "\nPlease Wait" <<endl;

    /* Деление файла на потоки, каждый поток считает свой кусок файла */
    try{
        vector<std::thread> v;
        for (auto &it: sigs){
            v.emplace_back(std::bind(&SignCreator::run, it));
        }
                
        /* Ожидание подсчёта всеми потоками */
        for (auto &t : v) {t.join();}

    }catch(exception &e){
        std::cout << e.what() << '\n';
        return;
    }        

    /* обработка исключений из других потоков */
    for (auto &it: sigs){
        if (it->getError()){
            try
            {
                std::rethrow_exception(it->getError());
            }
            catch (const std::exception &e)
            {
                std::cout << "error " << e.what() << std::endl;
                return;
            }            
        }
    }
    save();
}

/* -----   Director::save()   ------------------------------------------------- */
///   Метод для записи sig в выходной файл
void Director::save(){
    try{
        std::ofstream dstFile(dstPath,ios::binary);
        dstFile.exceptions(ios::failbit|ios::badbit);

        std::ostream_iterator<uint32> out_it(dstFile);     
        for (auto &it: sigs){
            std::copy(it->getResult().begin(),it->getResult().end(),out_it );          
        }
        cout <<"Success\nFile sig: " << dstPath << endl;
    }catch(exception &e){
        std::cout << "ERROR WRITE FILE\n " << e.what() << std::endl;
        return;
    }  
}