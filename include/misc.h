#ifndef QUARK_MISC_H
#define QUARK_MISC_H

#define DEF_NS_HEAD_QUARK  namespace quark {
#define DEF_NS_TAIL_QUARK  } //namespace quark

#include <string>
#include <stdint.h>

DEF_NS_HEAD_QUARK


/* 
 * misc ultilities
 *  - compile-time assert  --> quark_assert_static
 *  - type_traits          --> integer_constant
 *  - 
 */
namespace misc {

#if __cplusplus >= 201103L
#define quark_assert_static(Cond, c_string) do { \
    static_assert(Cond, c_string); \
} while(0)
#else
#define quark_assert_static(Cond, not_used) do { \
    enum {assert__ = 1/(Cond)}; \
} while(0)
#endif

#if __cplusplus >= 201103L
    template <typename T, T Val>
    struct integer_constant {
        typedef T value_type;
        static constexpr T value = Val;
    };
#else
    template <typename T, T Val>
    struct integer_constant {
        typedef T value_type;
        enum { value = Val };   
    };
#endif
    typedef integer_constant<bool, true> true_type;
    typedef integer_constant<bool, false> false_type;
    
    template <typename T1, typename T2>
    struct is_same_type {
        typedef false_type value_type;
        enum { value = value_type::value };
        //static constexpr bool value = false;
    };
    
    template <typename T1>
    struct is_same_type<T1, T1> {
        typedef true_type value_type;
        enum { value = value_type::value };
        //static constexpr bool value = true;
    };

    template <typename T1, typename T2>
    void check_type_equal(T1, T2) {
        quark_assert_static((is_same_type<T1, T2>::value), "type not equal!");
    }
    
    template <typename T1, typename T2>
    void check_type_equal(T2) {
        quark_assert_static((is_same_type<T1, T2>::value), "type not equal!");
    }
    
    template <typename T1, typename T2>
    void check_type_equal() {
        quark_assert_static((is_same_type<T1, T2>::value), "type not equal!");
    }
    
    template <typename T>
    void check_type_string(const T&) {
        check_type_equal<T, std::string>();
    }

#define CheckTypeTgt(Vars, Type) do { \
}while(0)

} // namespace misc

namespace time {

} // namespace time 

namespace numberic {

typedef uint8_t  u8; 
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

template <typename T>
bool IsSigned(const T) {
    T m_ = 0;
    m_ = ~m_;
    return int64_t(m_) == int64_t(-1);
}

template <typename T>
T MaxValue(const T) {
    T max_ = ~0;
    T mask_ = ~0;
    if(IsSigned(max_)){ //signed 
        mask_ = mask_ & ~(1 << ((sizeof(mask_) << 3) - 1));
    }
    uint64_t ret = max_ & mask_;
    return ret;
}

template <typename T>
T MinValue(const T) {
    T min_ = 0;
    T mask_ = 0;
    if(IsSigned(min_)) { //signed
        mask_ = 1 << ((sizeof(mask_) << 3) - 1);
    }
    //printf("%d %d %d\n", min_, rvmin_ , mask_);
    uint64_t ret = min_ | mask_;
    return ret;
}

template <typename T>
bool IsMin(const T var) {
    return var == MinValue(var);
}

template <typename T>
bool IsMax(const T var) {
    return var == MaxValue(var);
}

} // namespace numberic


DEF_NS_TAIL_QUARK

#endif
