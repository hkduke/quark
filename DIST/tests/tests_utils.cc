#include <misc.h>
#include <cstdio>
#include <stdarg.h>

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
                printf("---- test #%d: [%s] -----\n", idx, (*i)->name);
                (*i)->res = (*i)->fp();
                printf("---- test #%d: %s -----\n", idx, (*i)->Result());
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


    void TsAddTests(TestSet *ts, ...) {
        TestHandler th;
        const char* name;
        
        va_list vl;
        va_start(vl, ts);
        th = va_arg(vl, TestHandler);
        while(th != NULL) {
            name = va_arg(vl, const char*);
            ts->AddTest(th, name);
            th = va_arg(vl, TestHandler);
        }
    }


} // namespace Tests


DEF_NS_TAIL_QUARK

