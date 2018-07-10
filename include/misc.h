#ifndef QUARK_MISC_H
#define QUARK_MISC_H

#define DEF_NS_HEAD_QUARK namespace quark {
#define DEF_NS_TAIL_QUARK }  // namespace quark

#include <stdint.h>
#include <cstring>
#include <string>

#include <time.h>  // time_t, struct tm, time, localtime

DEF_NS_HEAD_QUARK

/*
 * misc ultilities
 *  - compile-time assert  --> quark_assert_static
 *  - type_traits          --> integer_constant
 *  -
 */
namespace misc {

/// assertion
#if defined(DEBUG)
#if __cplusplus >= 201103L
#define quark_assert_static(Cond, c_string) \
  do {                                      \
    static_assert(Cond, c_string);          \
  } while (0)
#else
#define quark_assert_static(Cond, not_used) \
  do {                                      \
    enum { assert__ = 1 / (Cond) };         \
  } while (0)
#endif
#else
#define quark_assert_static(NU1, NU2)
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
  // static constexpr bool value = false;
};

template <typename T1>
struct is_same_type<T1, T1> {
  typedef true_type value_type;
  enum { value = value_type::value };
  // static constexpr bool value = true;
};

/// check_type_equal(a, b)  check if a's Type == b's Type
template <typename T1, typename T2>
void check_type_equal(T1, T2) {
  quark_assert_static((is_same_type<T1, T2>::value), "type not equal!");
}

/// check_type_equal<T>(a)   check if a's Type == T
template <typename T1, typename T2>
void check_type_equal(T2) {
  quark_assert_static((is_same_type<T1, T2>::value), "type not equal!");
}

/// check_type_equal<T1,T2>()   check if T1 == T2
template <typename T1, typename T2>
void check_type_equal() {
  quark_assert_static((is_same_type<T1, T2>::value), "type not equal!");
}

template <typename T>
void check_type_string(const T &) {
  check_type_equal<T, std::string>();
}

template <typename T>
T min(const T &a, const T &b) {
  return a < b ? a : b;
}

template <typename T>
T max(const T &a, const T &b) {
  return a > b ? a : b;
}

typedef unsigned char uchar;

template <bool, typename T = void>
struct enable_if_my {
};

template <typename T>
struct enable_if_my<true, T> {
    typedef T type;
};

}  // namespace misc

/*
 * quark string implementation
 *
 */
namespace slice {
class slice {
 public:
  slice(void *memptr, size_t sz)
      : data_(reinterpret_cast<const char *>(memptr)), len_(sz) {}
  slice(const std::string &s) : data_(s.data()), len_(s.length()) {}
  slice(const char *sptr, size_t sz) : data_(sptr), len_(sz) {}
  slice(const char *c_sptr) : data_(c_sptr), len_(strlen(c_sptr)) {}
  slice() : data_(""), len_(0) {}

  inline std::string ToString() {
    return std::string(data_, len_);  // involve a copy operation.
  }
  inline const char *Data() const { return data_; }
  inline size_t Size() const { return len_; }

  /// [in]  Param
  ///
  /// [out] Return
  ///  >0 - this > s_
  ///  0  - this == s_
  ///  <0 - this < s_
  //   Note - if one is another's substring, longer one is larger than the
  //   other.
  //
  inline int Compare(const slice &s_) {
    size_t sz = misc::min(len_, s_.Size());
    int ret = ::memcmp(data_, s_.Data(), sz);
    if (0 == ret) {
      ret = len_ < s_.len_ ? -1 : 0;
      ret = len_ > s_.len_ ? +1 : 0;
    }
    return ret;
  }

  slice &operator=(const slice &s_) {
    data_ = s_.data_;
    len_ = s_.len_;
    return *this;
  }

 private:
  const char *data_;
  size_t len_;
};
/// Info  - xxxxx  --> [xxxxxx]
/// Param -
///   [in] p - the quoted char, char [ < ( { # and space are supported.
///
inline std::string &AddQuote(std::string &o, char p = '[') {
  const char *q;
  switch (p) {
    case '[':
      q = "]";
      break;
    case '<':
      q = ">";
      break;
    case '(':
      q = ")";
      break;
    case '{':
      q = "}";
      break;
    case '#':
      q = "#";
      break;
    case ' ':
      q = " ";
      break;
  };

  o = std::string(&p, 1) + o + q;
  return o;
}

template <typename T>
std::string ToString(T s1) {
  s1->ToString();  // copy
}

template <>
inline std::string ToString(bool s1) {
  return s1 ? std::string("True") : std::string("False");
}

}  // namespace slice

namespace numberic {

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

template <typename T>  /// FIXME - numberic type_traits, we can use template
                       /// specilize to do it. no need for calc.
bool IsSigned(const T) {
  T m_ = 0;
  m_ = ~m_;
  return int64_t(m_) == int64_t(-1);
}

template <>
inline bool IsSigned(int) {
  return true;
}
template <>
inline bool IsSigned(int64_t) {
  return true;
}

template <>
inline bool IsSigned(u8) {
  return false;
}
template <>
inline bool IsSigned(u16) {
  return false;
}
template <>
inline bool IsSigned(u32) {
  return false;
}
template <>
inline bool IsSigned(u64) {
  return false;
}

template <typename T>
T MaxValue(const T) {
  T max_ = ~0;
  T mask_ = ~0;
  if (IsSigned(max_)) {  // signed
    mask_ = mask_ & ~(1 << ((sizeof(mask_) << 3) - 1));
  }
  uint64_t ret = max_ & mask_;
  return ret;
}

template <>
inline u32 MaxValue(const u32) {
  return 0xFFFFFFFFU;
}
template <>
inline int32_t MaxValue(const int32_t) {
  return 0x7FFFFFFF;
}

template <>
inline u64 MaxValue(const u64) {
  return 0xFFFFFFFFFFFFFFFFULL;
}

template <typename T>
T MinValue(const T) {
  T min_ = 0;
  T mask_ = 0;
  if (IsSigned(min_)) {  // signed
    mask_ = 1 << ((sizeof(mask_) << 3) - 1);
  }
  // printf("%d %d %d\n", min_, rvmin_ , mask_);
  uint64_t ret = min_ | mask_;
  return ret;
}

template <>
inline u64 MinValue(const u64) {
  return 0ULL;
}
template <>
inline int64_t MinValue(const int64_t) {
  return 0x8000000000000000LL;
}

template <typename T>
bool IsMin(const T var) {
  return var == MinValue(var);
}

template <typename T>
bool IsMax(const T var) {
  return var == MaxValue(var);
}

}  // namespace numberic

namespace time {
using numberic::u64;

class timestamp {
 public:
  enum {
    format_0  /// "2018-04-18 16:08:05.xxxxxx"
  };
  enum {
    resol_milisec,  /// resolution: milisecond  ms
    resol_usec      /// resolution: microsecond μs
  };
  timestamp(u64);
  timestamp(bool precise = false, int resol = resol_milisec);

  std::string ToString(int fm = format_0);
  void decode(u64);
  u64 encode();

 private:
  union encoded {  /// FIXME - de/encode generic impl
    struct e1 {
      u64 resol_ : 2;
      u64 unused : 14;
      u64 val : 48;
    } bfm;     /// bit field member
    u64 line;  /// whole value
  };

  u64 _raw_to_u64();
  void _u64_to_raw(u64);

  struct timespec raw_;  /// timespec
  int resol_;            /// resolution FIXME - global? make it static?
};                       // class timestamp

}  // namespace time

DEF_NS_TAIL_QUARK

#endif
