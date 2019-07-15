
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