#include <cstdio>
#include <iostream>
#include <misc.h>
#include <string>
#include "tests_utils.h"


using namespace quark::misc;
using namespace quark::numberic;

int tst_01() { //misc
    printf("%d\n", is_same_type<int, float>::value);
    printf("%d\n", is_same_type<int, int>::value);
    
    int a = 0, b = 1;
    check_type_equal(a, b);
    
    u16 a1 = 0;
    u16 b1 = 1;
    check_type_equal(a1, b1);
    
    check_type_equal<u16>(b1);
    //check_type_equal<u32>(b1); //assert failed!
    std::string cc1;
    check_type_string(cc1);

    return 0;
}

using namespace quark::slice;

int tst_02() { //misc & slice
    const char *m1 = "abcdef";
    u64 x = 0x4142434445464748;
    std::string m2("xyz01234");
    
    slice *s0 = new slice((void*)(&x), sizeof(x)); //HGFEDCBA
    slice *s1 = new slice(m2);
    slice *s2 = new slice(m1, 2);
    slice *s3 = new slice("abcd");
    slice *s4 = new slice();
    
    std::cout << s0->ToString() << std::endl <<
        s1->ToString() << std::endl <<
        s2->ToString() << std::endl <<
        s3->ToString() << std::endl <<
        s4->ToString() << std::endl;
    std::string xx1 = s3->ToString();
    AddQuote(xx1);
    std::cout << xx1 << std::endl;

    delete s0;
    delete s1;
    delete s2;
    delete s3;
    delete s4;

    return 0;
}

int tst_03() {
    slice *s1 = new slice("100");
    slice *s2 = new slice("90");
    std::cout << s1->Compare(*s2) <<std::endl;
    return 0;
}

int tst_04() {
    int a1;

    u8  a00;
    u16 a01;
    u32 a02;
    
    int16_t a03;

    u64 a2;
    
    std::cout << quark::slice::ToString(IsSigned(a1)) << std::endl;
    std::cout << quark::slice::ToString(IsSigned(a2)) << std::endl;
    std::cout << quark::slice::ToString(IsSigned(a00)) << std::endl;
    std::cout << quark::slice::ToString(IsSigned(a01)) << std::endl;
    std::cout << quark::slice::ToString(IsSigned(a02)) << std::endl;

    std::cout << "max i32 " << quark::numberic::MaxValue(a1) << std::endl;
    std::cout << "min i32 " << quark::numberic::MinValue(a1) << std::endl;
    std::cout << "max u32 " << quark::numberic::MaxValue(a02) << std::endl;
    std::cout << "min u32 " << quark::numberic::MinValue(a02) << std::endl;
    std::cout << "max i16 " << quark::numberic::MaxValue(a03) << std::endl;
    std::cout << "min i16 " << quark::numberic::MinValue(a03) << std::endl;
    std::cout << "max u16 " << quark::numberic::MaxValue(a01) << std::endl;
    std::cout << "min u16 " << quark::numberic::MinValue(a01) << std::endl;
    

    return 0;
}

TESTSMAIN(tst_01, "type_checking",
        tst_02, "slice",
        tst_03, "slice_compare",
        tst_04, "numberic",
        NULL)
