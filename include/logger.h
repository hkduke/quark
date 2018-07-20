#ifndef QUARK_LOG_H
#define QUARK_LOG_H
#include <misc.h>

DEF_NS_HEAD_QUARK
namespace log {

/*
 * logger - a thread-safe, async-append logger which
 *  support rolling size, log level , async-append and thread-safe.
 *
 *  params:
 *      - roll_size     [50 MB]
 *      - level         [info ]   info, debug, error
 *
 * FIXME thread-safe
 */
class logger {
 public:
  enum { debug, warn, info, error };

 private:
  int roll_size;
  int default_level;

  const char *dir_;
  static FILE *fp_;
};

}  // namespace log
DEF_NS_TAIL_QUARK

#endif
