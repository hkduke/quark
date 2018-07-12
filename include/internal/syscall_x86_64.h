#ifndef SYSCALL_X86_64_H
#define SYSCALL_X86_64_H

#include <misc.h>

DEF_NS_HEAD_QUARK

namespace os {

typedef numberic::u64 b8;

template <typename T>
struct is_b8 {
  typedef misc::false_type value_type;
  static const bool value = false;
};

template <>
struct is_b8<b8> {
  typedef misc::true_type value_type;
  static const bool value = true;
};

template <typename T>
void makeb8(b8* b, T* x) {
  memcpy(static_cast<void*>(b), static_cast<void*>(x), sizeof(T));
}

#define SysCallCmd0 "movq %1, %%rax\n\t"
#define SysCallCmd1 SysCallCmd0 "movq %2, %%rdi\n\t"
#define SysCallCmd2 SysCallCmd1 "movq %3, %%rsi\n\t"
#define SysCallCmd3 SysCallCmd2 "movq %4, %%rdx\n\t"
#define SysCallCmd4 SysCallCmd3 "movq %5, %%r10\n\t"
#define SysCallCmd5 SysCallCmd4 "movq %6, %%r8\n\t"
#define SysCallCmd6 SysCallCmd5 "movq %7, %%r9\n\t"

#define SysCallRet "movq %%rax,%0\n\t"

#define OutputReg(x) "=r"(x)
#define InputReg(x) "r"(x)
#define SysCallInRegList0(nr, ofs) InputReg(nr)
#define SysCallInRegList1(nr, a1) InputReg(nr), InputReg(a1)
#define SysCallInRegList2(nr, a1, a2) SysCallInRegList1(nr, a1), InputReg(a2)
#define SysCallInRegList3(nr, a1, a2, a3) \
  SysCallInRegList2(nr, a1, a2), InputReg(a3)
#define SysCallInRegList4(nr, a1, a2, a3, a4) \
  SysCallInRegList3(nr, a1, a2, a3), InputReg(a4)
#define SysCallInRegList5(nr, a1, a2, a3, a4, a5) \
  SysCallInRegList4(nr, a1, a2, a3, a4), InputReg(a5)
#define SysCallInRegList6(nr, a1, a2, a3, a4, a5, a6) \
  SysCallInRegList5(nr, a1, a2, a3, a4, a5), InputReg(a6)

#define SysCallCrobList0 "%rax"
#define SysCallCrobList1 SysCallCrobList0, "%rdi"
#define SysCallCrobList2 SysCallCrobList1, "%rsi"
#define SysCallCrobList3 SysCallCrobList2, "%rdx"
#define SysCallCrobList4 SysCallCrobList3, "%r10"
#define SysCallCrobList5 SysCallCrobList4, "%r8"
#define SysCallCrobList6 SysCallCrobList5, "%r9"

#define SysCallTemplateX8664(ret, NR, i, ...)  \
  do {                                         \
    asm(SysCallCmd##i "syscall\n\t" SysCallRet \
        : OutputReg(ret)                       \
        : SysCallInRegList##i(NR, __VA_ARGS__) \
        : SysCallCrobList##i);                 \
  } while (0)

#define X86_64DefSysCall0(ret, NR) SysCallTemplateX8664(ret, NR, 0)
#define X86_64DefSysCall1(ret, NR, a1) SysCallTemplateX8664(ret, NR, 1, a1)
#define X86_64DefSysCall2(ret, NR, a1, a2) \
  SysCallTemplateX8664(ret, NR, 2, a1, a2)

#define X86_64DefSysCall3(ret, NR, a1, a2, a3) \
  SysCallTemplateX8664(ret, NR, 3, a1, a2, a3)
#define X86_64DefSysCall4(ret, NR, a1, a2, a3, a4) \
  SysCallTemplateX8664(ret, NR, 4, a1, a2, a3, a4)
#define X86_64DefSysCall5(ret, NR, a1, a2, a3, a4, a5) \
  SysCallTemplateX8664(ret, NR, 5, a1, a2, a3, a4, a5)
#define X86_64DefSysCall6(ret, NR, a1, a2, a3, a4, a5, a6) \
  SysCallTemplateX8664(ret, NR, 6, a1, a2, a3, a4, a5, a6)

extern int DoSysCall(uint64_t SysCallNR);

template <typename T1>
int DoSysCall(uint64_t SysCallNR, T1 a1) {
  uint64_t ret;
  b8 x1;
  makeb8(&x1, &a1);
  X86_64DefSysCall1(ret, SysCallNR, (x1));
  return (int)ret;
}

template <typename T1, typename T2>
int DoSysCall(uint64_t SysCallNR, T1 a1, T2 a2) {
  uint64_t ret;
  b8 x1, x2;
  makeb8(&x1, &a1);
  makeb8(&x2, &a2);
  X86_64DefSysCall2(ret, SysCallNR, (x1), (x2));
  return (int)ret;
}

template <typename T1, typename T2, typename T3>
int DoSysCall(uint64_t SysCallNR, T1 a1, T2 a2, T3 a3) {
  uint64_t ret;
  b8 x1, x2, x3;
  makeb8(&x1, &a1);
  makeb8(&x2, &a2);
  makeb8(&x3, &a3);
  X86_64DefSysCall3(ret, SysCallNR, (x1), (x2), (x3));
  return (int)ret;
}

template <typename T1, typename T2, typename T3, typename T4>
int DoSysCall(uint64_t SysCallNR, T1 a1, T2 a2, T3 a3, T4 a4) {
  uint64_t ret;
  b8 x1, x2, x3, x4;
  makeb8(&x1, &a1);
  makeb8(&x2, &a2);
  makeb8(&x3, &a3);
  makeb8(&x4, &a4);
  X86_64DefSysCall4(ret, SysCallNR, (x1), (x2), (x3), (x4));
  return (int)ret;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
int DoSysCall(uint64_t SysCallNR, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) {
  uint64_t ret;
  b8 x1, x2, x3, x4, x5;
  makeb8(&x1, &a1);
  makeb8(&x2, &a2);
  makeb8(&x3, &a3);
  makeb8(&x4, &a4);
  makeb8(&x5, &a5);
  X86_64DefSysCall5(ret, SysCallNR, (x1), (x2), (x3), (x4), (x5));
  return (int)ret;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6>
int DoSysCall(uint64_t SysCallNR, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) {
  uint64_t ret;
  b8 x1, x2, x3, x4, x5, x6;
  makeb8(&x1, &a1);
  makeb8(&x2, &a2);
  makeb8(&x3, &a3);
  makeb8(&x4, &a4);
  makeb8(&x5, &a5);
  makeb8(&x6, &a6);
  X86_64DefSysCall6(ret, SysCallNR, (x1), (x2), (x3), (x4), (x5), (x6));
  return (int)ret;
}

extern int __gettid();

}  // namespace os
DEF_NS_TAIL_QUARK

#endif
