#ifndef QUARK_ATOMIC_H
#define QUARK_ATOMIC_H

#include <misc.h>

DEF_NS_HEAD_QUARK
namespace atomic {

typedef volatile numberic::u32 qk_atomic_t;

/*
 * 
 * <B>Atomicly</B> increase the @var with @add.
 * para - 
 *   var[in] - pointer to the atomic variable.
 *   add[in] - the value to add.
 * return -
 *   the old value of @var.
 */
qk_atomic_t fetch_and_add(qk_atomic_t *var, int add);



/*
 * <B>Atomicly</B> compare @var with @oldval, 
 * if equal, set @var with @newval and return true,
 * otherwise, nothing is changed and return false.
 * para - 
 *   var[in] - pointer to the atomic variable.
 *   oldvalue[in] - the old value to compare.
 *   newvalue[in] - the new value to set.
 * return - 
 *   the result of CAS operation. true for success cas, false for failed cas. 
 *
 */
bool compare_and_set(qk_atomic_t *var, qk_atomic_t oldval, qk_atomic_t newval);

#if defined(__linux__) && defined(__x86_64__)
#include "./internal/atomic_x86_64.h"
#else
#error "quark atomic operation is now only availiable for x86_64"
#endif 

}
DEF_NS_TAIL_QUARK
#endif
