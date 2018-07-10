#ifndef SYS_IMPL_QUARK_H
#define SYS_IMPL_QUARK_H


#include <sys_abs.h>

#include <pthread.h>
#include <unistd.h>

#if defined(__linux__) && defined(__x86_64__)
#include "syscall_x86_64.h"
#else
#error "quark syscall wrapper for gettid(2) only supported in linux(x86_64)."
#endif

DEF_NS_HEAD_QUARK

namespace os {
using misc::uchar;
struct RawByteBuffer {
  uchar *b;
  int sz;
  RawByteBuffer(uchar *b_, int sz_) : b(b_), sz(sz_) {}
};

/// - fsync or fdatasync
class PosixWritableFile : public File<int, RawByteBuffer> {};
class PosixReadableFile : public File<int, RawByteBuffer> {};

/// NPTL Thread
///
template <typename T>
class nptl_thread : public Thread<T> {
 public:
  nptl_thread(T *u) : ucontext_(u) {
    int e;
    if (!Error::IsOK(e = pthread_attr_init(&a_))) {
      QuarkFatal("pthread_attr_init", e);
    }
    _init_fwd(typename T::detachstate());
  }
  ~nptl_thread() { pthread_attr_destroy(&a_); }
  virtual int Run();
  virtual void Block() {}
  virtual void Kill() {}
  virtual int Join() { return _join_fwd(typename T::detachstate()); }

 private:
  using typename Thread<T>::tag_joinable;
  using typename Thread<T>::tag_detached;
  inline void _init_fwd(tag_joinable) {
    pthread_attr_setdetachstate(&a_, PTHREAD_CREATE_JOINABLE);
  }
  inline void _init_fwd(tag_detached) {
    pthread_attr_setdetachstate(&a_, PTHREAD_CREATE_DETACHED);
  }

  inline int _join_fwd(tag_joinable) {
    /// Note - retval is not used. we don't need this here.
    int e = pthread_join(t_, NULL);
    if (!Error::IsOK(e)) {
      /// log & do something.
    }
    return e;
  }
  inline int _join_fwd(tag_detached) { return 0; }

  static void *routine(void *arg) {
    /* inside this thread */

    nptl_thread<T> *ctx = reinterpret_cast<nptl_thread<T> *>(arg);

    ctx->SetTid(static_cast<u64>(__gettid()));
    ctx->SetStatRunning();

    T *uc = ctx->ucontext_;
    uc->WorkLoop(uc);

    ctx->SetStatStopped();
    return NULL;
  }

 private:
  pthread_t t_;
  pthread_attr_t a_;

  T *ucontext_;
};

template <typename T>
int nptl_thread<T>::Run() {
  int e = pthread_create(&t_, &a_, &nptl_thread<T>::routine, this);
  if (!Error::IsOK(e)) {
    /// log & do something.
  }
  return e;
}

template <typename T>
Thread<T> *Thread<T>::NewThread(T *x) {
  return new nptl_thread<T>(x);
}

}  // namespace os

DEF_NS_TAIL_QUARK

#endif
