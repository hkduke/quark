#include <atomic.h>
#include <iostream>
#include "tests_utils.h"

using namespace quark::atomic;

int tst_01() {
    qk_atomic_t a1 = 0, old;
    qk_atomic_t a2 = 1, olda2 = 1;

    bool res;
    old = fetch_and_add(&a1, 10);
    std::cout << old << "," << a1 << std::endl;
    

    res = compare_and_set(&a2, olda2, 20);
    std::cout << res << "," << a2 << std::endl; //expected success

    res = compare_and_set(&a2, olda2, 20);
    std::cout << res << "," << a2 << std::endl; //expected success


    return 0;
}

TESTSMAIN(tst_01, "atomic_basic_test",
        NULL)
