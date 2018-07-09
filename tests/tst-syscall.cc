
/*
 *
 *
 * from the glibc wiki page https://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linux
- int 0x80
On both Linux x86 and Linux x86_64 systems you can make a syscall by calling interrupt 0x80 using the int $0x80 command. Parameters are passed by setting the general purpose registers as following:

Param 1	Param 2	Param 3	Param 4	Param 5	Param 6
eax	ebx	ecx	edx	esi	edi	ebp
Return value
eax
The syscall numbers are described in the Linux generated file $build/arch/x86/include/generated/uapi/asm/unistd_32.h or $build/usr/include/asm/unistd_32.h. The latter could also be present on your Linux system, just omit the $build.
All registers are preserved during the syscall.

- syscall
The x86_64 architecture introduced a dedicated instruction to make a syscall. It does not access the interrupt descriptor table and is faster. Parameters are passed by setting the general purpose registers as following:

Param 1	Param 2	Param 3	Param 4	Param 5	Param 6
rax	rdi	rsi	rdx	r10	r8	r9
Return value
rax
The syscall numbers are described in the Linux generated file $build/usr/include/asm/unistd_64.h. This file could also be present on your Linux system, just omit the $build.
All registers, except rcx and r11 (and the return value, rax), are preserved during the syscall.
 * */

/// for x86 & x86_64
#include <iostream>
#include <cstring>
#include <cstdio>
#include <sys/syscall.h>



struct b4 {
    char buf[4];
};
struct b8 {
    char buf[8];
};

#if __cplusplus >= 201103L

#include <type_traits>
typedef std::true_type true_type;
typedef std::false_type false_type;

#else
template <typename T, T Val>                      
struct integer_constant {                         
    typedef T value_type;                         
    enum { value = Val };                         
};                                                
typedef integer_constant<bool, true> true_type;   
typedef integer_constant<bool, false> false_type; 
#endif

template <typename T>
struct is_b4 {
    typedef false_type value_type;
    const bool value = false;
};

template <>
struct is_b4<b4> {
    typedef true_type value_type;
    const bool value = true;
};

template <typename T>
struct is_b8 {
    typedef false_type value_type;
    static const bool value = false;
};

template <>
struct is_b8<b8> {
    typedef true_type value_type;
    static const bool value = true;
};

template <bool, typename T = void>
struct enable_if_my {
};
template <typename T>
struct enable_if_my<true, T> {
    typedef T type;
};


template<typename T>
void makeb48(b4* b, T* x) {
    memcpy(static_cast<void*>(b->buf), static_cast<void*>(x), sizeof(T));
}
template<typename T>
void makeb48(b8* b, T* x) {
    memcpy(static_cast<void*>(b->buf), static_cast<void*>(x), sizeof(T));
}
template<typename T, typename enable_if_my<is_b4<T>::value, T>::type* = nullptr>
uint32_t* CtnPtr(T *b){
    return reinterpret_cast<uint32_t*>(b->buf);
}
template<typename T, typename enable_if_my<is_b8<T>::value, T>::type* = nullptr>  /// should be ::type* , or compiler cannot infer the tempalte argument.
uint64_t* CtnPtr(T *b){
    return reinterpret_cast<uint64_t*>(b->buf);
}


#define SysCallCmd0 "movq %1, %%rax\n\t"
#define SysCallCmd1 SysCallCmd0 "movq %2, %%rdi\n\t"
#define SysCallCmd2 SysCallCmd1 "movq %3, %%rsi\n\t"
#define SysCallCmd3 SysCallCmd2 "movq %4, %%rdx\n\t"
#define SysCallCmd4 SysCallCmd3 "movq %5, %%r10\n\t"
#define SysCallCmd5 SysCallCmd4 "movq %6, %%r8\n\t"
#define SysCallCmd6 SysCallCmd5 "movq %7, %%r9\n\t"

template<typename T1, typename T2, typename T3>
int DoSysCall0(uint64_t SysCallNR, T1 a1, T2 a2, T3 a3)
{
    uint64_t ret;
    b8 x1;
    b8 x2;
    b8 x3;
    const char * ptr;
    makeb48(&x1, &a1);
    makeb48(&x2, &a2);
    makeb48(&x3, &a3);

    printf("%d %s %d\n", *(reinterpret_cast<int*>(CtnPtr(&x1))),
            (ptr = reinterpret_cast<const char*>(*(CtnPtr(&x2)))) == NULL ? "NULL" : ptr, 
            *(reinterpret_cast<int*>(CtnPtr(&x3))));

    asm(
    "movq %1, %%rax\n\t" /// SysCall Number
    "movq %2, %%rdi\n\t" /// Para 1
    "movq %3, %%rsi\n\t" /// Para 2
    "movq %4, %%rdx\n\t" /// Para 3
    "syscall\n\t"     /// Call it
    "movq %%rax, %0\n\t" /// Fetch Return Value
    :"=r"(ret)
    :"r"(SysCallNR),"r"(*(CtnPtr(&x1))), "r"(*(CtnPtr(&x2))), "r"(*(CtnPtr(&x3)))
    :"%rax","%rdi", "%rsi", "%rdx"
    );
    return (int)ret;
}


int Write(int fd, const char* str, int num) {
    return DoSysCall0(SYS_write, fd, str, num);
}

int main() {
    int ret;
    const char * str1 = "Hello Syscall\n";
    ret = Write(1, str1, strlen(str1));
    std::cout << "Ret: " << ret << std::endl;
    return 0;
}
