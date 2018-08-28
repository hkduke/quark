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
        int res;
        TObject(TestHandler fp_, const char *n_) :
            fp(fp_), name(n_) { }
        const char * Result() {
            return res == 0 ? "Pass  " : "Failed";
        }

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


extern void TsAddTests(TestSet *ts, ...);
#define TESTSMAIN(...) int main() {    \
    quark::Tests::TestSet *ts = new quark::Tests::TestSet();    \
    quark::Tests::TsAddTests(ts, __VA_ARGS__);    \
    ts->Run();                      \
    return 0;                       \
}

} // namespace Tests

DEF_NS_TAIL_QUARK


#endif
