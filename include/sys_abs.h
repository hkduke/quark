#ifndef QUARK_OS_ABS_H
#define QUARK_OS_ABS_H
/*
 * an abstraction layer of os operations.
 */
#include <misc.h>
DEF_NS_HEAD_QUARK
namespace os {

using numberic::u64;




/*
 * Allow Append
 *
 *
 */
template<typename HT, typename BT, int PGSIZE = 4096>   /// Handler Type, Buffer Type
class File {   ///  RedFS File/Normal File
    public:
        File(HT* h) : handlerptr_(h) { }     /// open a file
        virtual ~File();                /// close file
        virtual inline HT FetchHandler() const { return handlerptr_; }  ///
        virtual int       Append(const BT *bptr, int sz = PGSIZE);         ///
        virtual int       Close();                                   ///
        virtual int       Size() const;

        virtual int       Read(BT *bptr, int sz = PGSIZE);           /// Read a page from current offset.
        virtual u64       GetCurrOfs() const {  return offset_; }    ///
        virtual int       SetCurrOfs(u64 ofs);                       /// only PGSIZE-alignment ofs accepted.

    protected:
        HT *handlerptr_;
        u64 offset_;
};

class Thread {  ///  

};

template<typename LockType>
class Locker {
    public:
        Locker(LockType *l1) : l_(l1) { 
            l_->Lock();
        }
        ~Locker() {
            l_->Unlock();
        }
    private:
        LockType *l_;
};

/*
 * lock_guard, lock, load, acquire, atomic_*_t
 */
class Sync {     /// lock-based sync
    public:

};

class CASSync {  /// cas-based sync      

};

} // namespace os
DEF_NS_TAIL_QUARK
#endif
