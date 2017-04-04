#ifndef CAT_HH
#define CAT_HH

#include <sstream>

template <typename S, typename T>
inline void cat_impl(S& ss, T&& x) {
  ss << std::forward<T>(x);
}

template <typename S, typename T, typename... TT>
inline void cat_impl(S& ss, T&& x, TT&&... xx) {
  ss << std::forward<T>(x);
  cat_impl(ss,std::forward<TT>(xx)...);
}

template <typename... TT>
inline std::string cat(TT&&... xx) {
  std::stringstream ss;
  cat_impl(ss,std::forward<TT>(xx)...);
  return ss.str();
}

#endif
