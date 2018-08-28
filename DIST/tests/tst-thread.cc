#include <misc.h>
#include <sys.h>
#include <iostream>
#include <unistd.h>

#include "tests_utils.h"
#include <internal/syscall_x86_64.h>

using quark::os::Thread;

class worker1 : public Thread<worker1>::dthread {
    public:
        worker1(int i) : i_(i) {}
        void WorkLoop(worker1 * w);
    private:
        int i_;
};

void worker1::WorkLoop(worker1 * w) {
    for (;;) {
        sleep(5);
        std::cout << "w" << w->i_ << " sleep" << std::endl;
    }
}

class worker2 : public Thread<worker2>::jthread {
    public:
        worker2(int i) : i_(i) {}
        void WorkLoop(worker2 * w);
    private:
        int i_;
};

void worker2::WorkLoop(worker2 * w) {
    int c = 0;
    for (;;) {
        c++;
        sleep(5);
        if ( c > 20) {
            break;
        }
        std::cout << "w" << w->i_ << " sleep" << std::endl;
    }
}


int tst_01() {// dthread basic.
  worker1 w1(0);
  Thread<worker1> *t1 = Thread<worker1>::NewThread(&w1);
  t1->Run();
  std::cout << "[####] main thread id:" << quark::os::__gettid() << std::endl;
  std::cout << "[####] worker thread id:" << t1->GetTid() << std::endl;
  //wait
  for(;;) {
    ;
  }
  return 0;
}

int tst_02() { // jthread basic.
  worker2 w1(0);
  Thread<worker2> *t1 = Thread<worker2>::NewThread(&w1);
  t1->Run();
  std::cout << "[####] main thread id:" << quark::os::__gettid() << std::endl;
  std::cout << "[####] worker thread id:" << t1->GetTid() << std::endl;
  return 0;
}

TESTSMAIN( tst_01, "detached thread basic test", 
    NULL)
