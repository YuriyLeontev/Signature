/*
=============================================================================
   Signature - The program that generates the signature file
-----------------------------------------------------------------------------
   File: pcout.h   Created: 2019/07/15
-----------------------------------------------------------------------------
   Authors: Y. A. Leontev
=============================================================================
*/

/**
 \file pcout.h
 \brief Файл содержит объявление класса Pcout
    Отладочный класс для вывода данных в конкурентной борьбе за cout
 \author Y. A. Leontev
 \date 2018.07.15
*/



#ifndef P_COUT_H
#define P_COUT_H


#include <iostream>
#include <mutex>
#include <sstream>

using namespace std;

struct pcout : public stringstream {
    static inline mutex cout_mutex;
    ~pcout(){
        lock_guard<mutex> l {cout_mutex};
        cout << rdbuf();
        cout.flush();
    }
};


#endif /* P_COUT_H */