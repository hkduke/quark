#ifndef QUARK_INTERNAL_ATOMIC_H
#define QUARK_INTERNAL_ATOMIC_H

#if !defined(QUARK_ATOMIC_H)
#error "user should not include this file directly!"
#endif

// check smp
#if defined(HAVESMP)
#warning "have smp config."
#define SMPLOCKPREFIX "lock "
#else
#define SMPLOCKPREFIX ""
#endif

/// We now support for 32 bit atomic variable
/// source operand must be a register.
///
qk_atomic_t fetch_and_add(qk_atomic_t *var, int add) {
    qk_atomic_t old;
    asm volatile(
        SMPLOCKPREFIX "xaddl %%eax, %0\n\t"
        : "+m"(*var), "=a"(old)
        : "a"(add)
        : "memory"
    );
    return old;
}

///
///
bool compare_and_set(qk_atomic_t *var, qk_atomic_t oldval, qk_atomic_t newval) {
    char res;
    asm volatile(
        SMPLOCKPREFIX "cmpxchgl %3,%1\n\t"
        "sete %%al\n\t"
        : "=a"(res), "+m"(*var)
        : "a"(oldval), "r"(newval)
        : "cc", "memory"
    );
    return res == 1;
}

#endif
