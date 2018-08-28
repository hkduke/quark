#ifndef QUARK_LOG_H
#define QUARK_LOG_H
#include <misc.h>

DEF_NS_HEAD_QUARK
namespace log {

enum { debug, info, warn, error };
const char * LogLvlStr [] = {
    "[DBG]",
    "[INF]",
    "[WRN]",
    "[ERR]",
};
/*
 * logger - a thread-safe, async-append logger which
 *  support rolling size, log level , async-append and thread-safe.
 *
 *  params:
 *      - roll_size     [50 MB]
 *      - level         [info ]   debug, info, warn, error
 *
 * FIXME thread-safe
 */
struct Config {
  int roll_size;
  int log_level;

};

class Logger;

}  // namespace log
DEF_NS_TAIL_QUARK

#endif
