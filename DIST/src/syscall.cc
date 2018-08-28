#include <sys/syscall.h>
#include <unistd.h>

#include <internal/sys_impl_quark.h>

DEF_NS_HEAD_QUARK

namespace os {
/// quark system call wrapper.

int DoSysCall(uint64_t SysCallNR) {
  uint64_t ret;
  X86_64DefSysCall0(ret, SysCallNR);
  return (int)ret;
}

int __gettid() { return DoSysCall(SYS_gettid); }

}  // namespace os
DEF_NS_TAIL_QUARK
