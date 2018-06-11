#include <cstdio>

#include "tests_utils.h"


DEF_NS_HEAD_QUARK
namespace Tests {

    void TestSet::AddTest( TestHandler fp, const char* name ) {
        TObject *t = new TObject(fp, name);
        tests_.push_back(t);
    }
    void TestSet::Run() {
        int idx = 0;
        for( itr i = tests_.begin(); i != tests_.end(); ++i, ++idx) {
            if (*i) {
                printf("---- test %d: %s -----\n", idx, (*i)->name);
                int ret = (*i)->fp();
                printf("---- res : %d  -----\n", ret);
            }
        }   
    }
    TestSet::~TestSet() {
        for(itr i = tests_.begin(); i != tests_.end(); ++i) {
            if (*i) {
                delete *i;
            }
        }
    }
}
DEF_NS_TAIL_QUARK

