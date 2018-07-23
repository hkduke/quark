#include <misc.h>

DEF_NS_HEAD_QUARK 

namespace log {

class Logger {
 public:

 private:

  const char *dir_;
  static FILE *fp_;
};

} // namespace log

DEF_NS_TAIL_QUARK 
