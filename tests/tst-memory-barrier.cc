#include <misc.h>
#include <sys.h>
#include <atomic.h>

#include <iostream>
#include <string.h>
#include <stdio.h>


#include "tests_utils.h"

// Part I. Tests for Memory Barrier.
// 
using quark::os::Thread;
using quark::atomic::qk_atomic_t;

qk_atomic_t ready;
const char *bptr;

class Producer : public Thread<Producer>::dthread { // is a non-joinable thread.
    public:
        Producer(const char* txt) : foo(txt){}
        void WorkLoop(Producer *) {
            // Work's own bussiness logic goes here.        
            while(ready != 0) {
            };

            bptr = foo;
            quark::atomic::memory_barrier();
            ready = 1;
        }

    private:
        const char *foo;
};


class Consumer : public Thread<Consumer>::jthread { 
    public:
        Consumer(const char* f) {
            fp = fopen(f, "w+");
            if (fp == NULL) {
                QuarkFatal(f, errno);
                abort();
            }
        }
        ~Consumer() {
            fclose(fp);
        }
        void WorkLoop(Consumer *) {
            while(1) {
                while(ready == 0) {
                };
                
                std::cout << "to flush: " << strlen(bptr) << std::endl;
                
                fwrite(bptr, strlen(bptr), 1, fp);
                std::cout << "flush buffer, wait again" << std::endl;
                
                quark::atomic::memory_barrier();
                ready = 0;
                bptr = nullptr;
                fflush(fp);
            }
        }
    private:
        FILE* fp;
};

void Test_For_MB1() {
    bptr = "Not this!";
    Producer p1("HelloHello,Test For MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM, barrier");
    Consumer c1("./output.txt");
    
    Thread<Producer> *t1 = Thread<Producer>::NewThread(&p1);
    Thread<Consumer> *t2 = Thread<Consumer>::NewThread(&c1);
    
    ready = 0;

    t2->Run();
    t1->Run();

    //
    t1->Run();

    t2->Join();
}


TESTSMAIN( Test_For_MB1, "test for memory barrier 01 ", 
    NULL)
