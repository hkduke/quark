#ifndef QUARK_TESTS_UTILS_H
#define QUARK_TESTS_UTILS_H

#include <misc.h>
#include <vector>

DEF_NS_HEAD_QUARK

namespace Tests {
    typedef int (* TestHandler) ();

    struct TObject {
        TestHandler fp;
        const char *name;
        TObject(TestHandler fp_, const char *n_) :
            fp(fp_), name(n_) { }

    };

    class TestSet {
        public:
            void AddTest(TestHandler , const char*);
            void Run();
            ~TestSet();
        private:
            typedef std::vector<TObject*>::iterator itr;
            std::vector<TObject*> tests_;
    };


#define ADD_Test(TS, FP) do {   \
                                \
}while(0)


} // namespace Tests

DEF_NS_TAIL_QUARK


#endif
