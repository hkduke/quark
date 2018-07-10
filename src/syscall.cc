#include <sys/syscall.h>
#include <unistd.h>

#include "syscall_x86_64.h"

DEF_NS_HEAD_QUARK

namespace os {
/// quark system call wrapper.

int __gettid() {
    return DoSysCall(SYS_gettid);
}

}
DEF_NS_TAIL_QUARK

