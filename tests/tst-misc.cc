#include <cstdio>
#include <misc.h>
#include <string>
#include "tests_utils.h"


using namespace quark::misc;
using namespace quark::numberic;

int tst_01() {
    printf("%d\n", is_same_type<int, float>::value);
    printf("%d\n", is_same_type<int, int>::value);
    
    int a = 0, b = 1;
    check_type_equal(a, b);
    
    u16 a1 = 0;
    u16 b1 = 1;
    check_type_equal(a1, b1);
    
    check_type_equal<u16>(b1);

    std::string cc1;
    check_type_string(cc1);

    return 0;
}

TESTSMAIN(tst_01, "type_checking", NULL)
