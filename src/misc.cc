#include <misc.h>

DEF_NS_HEAD_QUARK
namespace time {
    
    timestamp::timestamp(u64 ts) {
        this->decode(ts);
    }
#ifdef CLOCK_REALTIME_COARSE
#define QUARK_TIMESTAMP_CLOCK CLOCK_REALTIME_COARSE
#else
#define QUARK_TIMESTAMP_CLOCK CLOCK_REALTIME
#endif
#define QUARK_TIMESTAMP_VALID_BITS 48
#define QUARK_TIMESTAMP_BUFFER_SIZE 64

    timestamp::timestamp(bool precise, int resol) : raw_(::timespec{0, 0}), resol_(resol) {
        if (!precise) { 
            ::time(&(raw_.tv_sec));
        } else {
            ::clock_gettime(QUARK_TIMESTAMP_CLOCK, &raw_);
        }
    }
    
    void timestamp::decode(u64 ux) {
        encoded x;
        x.line = ux;
        this->_u64_to_raw(x.bfm.val);
        this->resol_ = x.bfm.resol_;
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
        u64 sec_f  = 1000; 
        u64 usec_f = 1000 * 1000;
        if (resol_ == resol_usec) {
            sec_f  = 1000 * 1000;
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
            snprintf
        }
    }

} // namespace time
DEF_NS_TAIL_QUARK
