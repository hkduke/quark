#include <sys_abs.h>
DEF_NS_HEAD_QUARK
namespace os {
    using misc::uchar;
    struct RawByteBuffer {
        uchar* b;
        int sz;
        RawByteBuffer(uchar *b_, int sz_) : b(b_), sz(sz_) {}
    };

    class PosixFile : public File<FILE, RawByteBuffer> {
        
    
    };

} // namespace os
DEF_NS_TAIL_QUARK

