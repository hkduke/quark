#include <misc.h>
#include <cstdio>

DEF_NS_HEAD_QUARK
namespace time {

timestamp::timestamp(u64 ts) { this->decode(ts); }
#ifdef CLOCK_REALTIME_COARSE
#define QUARK_TIMESTAMP_CLOCK CLOCK_REALTIME_COARSE
#else
#define QUARK_TIMESTAMP_CLOCK CLOCK_REALTIME
#endif

#define QUARK_TIMESTAMP_VALID_BITS 48
#define QUARK_TIMESTAMP_BUFFER_SIZE 25

#define TIME_GET_YEAR(x) (x + 1900)
#define TIME_GET_MONTH(x) (x + 1)

timestamp::timestamp(bool precise, int resol)
    : raw_(::timespec{0, 0}), resol_(resol) {
  if (!precise) {
    ::time(&(raw_.tv_sec));
  } else {
    ::clock_gettime(QUARK_TIMESTAMP_CLOCK, &raw_);
  }
}

void timestamp::decode(u64 ux) {  /// FIXME - de/encode generic impl
  encoded x;
  x.line = ux;
  this->resol_ = x.bfm.resol_;
  this->_u64_to_raw(x.bfm.val << (64 - QUARK_TIMESTAMP_VALID_BITS));
}

u64 timestamp::encode() {
  u64 val = this->_raw_to_u64();
  encoded x;
  x.bfm.resol_ = this->resol_;  // 0, 1
  x.bfm.val = val >> (64 - QUARK_TIMESTAMP_VALID_BITS);
  /// FIXME - hardcoded resolution.
  return x.line;
}

u64 timestamp::_raw_to_u64() {
  u64 ret = 0;
  u64 sec_f = 1000;
  u64 usec_f = 1000 * 1000;
  if (resol_ == resol_usec) {
    sec_f = 1000 * 1000;
    usec_f = 1000;
  }
  ret += raw_.tv_sec * sec_f;
  ret += raw_.tv_nsec / usec_f;
  return ret;
}
void timestamp::_u64_to_raw(u64 ux) {
  u64 sec_f = resol_ == resol_milisec ? 1000 : 1000000;
  u64 nsec_f = resol_ == resol_milisec ? 1000000 : 1000;
  raw_.tv_sec = ux / sec_f;
  raw_.tv_nsec = (ux % sec_f) * nsec_f;
}

std::string timestamp::ToString(int fm) {
  struct tm *ti;
  std::string ret;
  ti = ::localtime(&(raw_.tv_sec));
  if (fm == format_0) {
    ret.resize(QUARK_TIMESTAMP_BUFFER_SIZE);
    ::snprintf(const_cast<char *>(ret.data()),
               QUARK_TIMESTAMP_BUFFER_SIZE,  /// if exceeds this length, the
                                             /// string would be truncated.
               "%d-%d-%d %d:%d:%d.%ld", TIME_GET_YEAR(ti->tm_year),
               TIME_GET_MONTH(ti->tm_mon), ti->tm_mday, ti->tm_hour, ti->tm_min,
               ti->tm_sec, raw_.tv_nsec);
  }
  return ret;  // copy
}

}  // namespace time
DEF_NS_TAIL_QUARK
