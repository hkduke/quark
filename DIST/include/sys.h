#ifndef QUARK_OS_ABS_H
#define QUARK_OS_ABS_H
/*
 * an abstraction layer of system regarding items.
 */

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <misc.h>

DEF_NS_HEAD_QUARK
namespace os {

using numberic::i32;
using numberic::u64;

class Error {
 public:
  static inline bool IsOK(int e) { return e == 0; }
  static std::string Msg() { return std::string(strerror(errno)); }
  static std::string Msg(int e) { return std::string(strerror(e)); }
  static void Fatal(const char *msg, int e, const char *file, const int line) {
    printf("Fatal @ [%s:%d] %s:%s\n", file, line, msg, Msg(e).c_str());
    abort();
  }
};

#define QuarkFatal(Msg, E)                    \
  do {                                        \
    quark::os::Error::Fatal(Msg, E, __FILE__, __LINE__); \
  } while (0)

/*
 * Directory Abstraction
 *  -
 */
class directory {};

/*
 * File Abstraction
 *  - Append-Only WriteFile
 *      Open
 *  - Random-Access ReadFile
 */
template <typename HT, typename BT,
          int PGSIZE = 4096>  /// Handler Type, Buffer Type
class File {                  ///  RedFS File/Posix File
 private:
  struct meta {
    HT handler_;

    int ref_;
    u64 ofs_;
    std::string filename_;
  };
 public:
  File() {}
  virtual ~File() { Close(); }

  virtual inline HT FetchHandler() const { return m_.handler_; }  ///
  virtual u64 GetCurrOfs() const { return m_.ofs_; }              ///
  virtual u64 Size() const = 0;

  virtual i32 Append(const BT *bptr, int sz = PGSIZE) = 0;  ///
  virtual i32 Read(BT *bptr,
                   int sz = PGSIZE) = 0;  /// Read a page from current offset.

  virtual int Close() = 0;  ///
  virtual int Sync() = 0;
  virtual int SetCurrOfs(u64 ofs) = 0;  /// only PGSIZE-alignment ofs accepted.

 protected:
  struct meta m_;

 public:
  inline void mput() { m_.ref_--; }
  inline File<HT, BT, PGSIZE> *mget() {
    m_.ref_++;
    return this;
  }
};
/// Template Parameter T
///  - Thread Object which user defined. Should include a field `WorkLoop`
///  - T::WorkLoop's prototype
///  -      void (*) (T*)
///  - the return value should be mantained by T itself.

template <typename T>
class Thread {
 public:
  typedef struct {
  } tag_joinable;  /// <--- if has this tag, then the thread can be join
  typedef struct {
  } tag_detached;
  struct jthread {
    typedef tag_joinable detachstate;
    virtual void WorkLoop (T*) = 0;
  };
  struct dthread {
    typedef tag_detached detachstate;
    virtual void WorkLoop (T*) = 0;
  };
  enum { Stopped, Running, Blocked };
  struct ThreadHandler {  /// Thread Local Data
    u64 tid;              ///
    int stat;             /// Stopped, Running, [Blocked* not impl.]
    u64 ts;               /// timestamp when it start.
  };
  Thread() {}
  virtual ~Thread() {}

  static Thread<T> *NewThread(T *);

  virtual int Run() = 0;     /// impl-ed. Start running as a new thread
  virtual void Block() = 0;  /// n/a
  virtual void Kill() = 0;   /// n/a
  virtual int Join() = 0;  /// impl-ed. Block the calling thread and wait until
                           /// this thread exit.

  inline u64 GetTid() { return th_.tid; }
  inline int GetStat() { return th_.stat; }

 protected:
  inline void SetTid(u64 i) { th_.tid = i; }
  inline void SetStatStopped() { th_.stat = Stopped; }
  inline void SetStatRunning() { th_.stat = Running; }
  inline void SetStatBlocked() { th_.stat = Blocked; }

 protected:
  ThreadHandler th_;
};

template <typename LockType>
class Locker {
 public:
  Locker(LockType *l1) : l_(l1) { l_->Lock(); }
  ~Locker() { l_->Unlock(); }

 private:
  LockType *l_;
};

/*
 * rcu, lock_guard, lock, load, acquire, atomic_*_t
 */
class Sync {  /// lock-based sync
};

class CASSync {  /// cas-based sync
};

}  // namespace os
DEF_NS_TAIL_QUARK

#include "./internal/sys_impl_quark.h"

#endif
