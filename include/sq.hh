#ifndef SQ_HH
#define SQ_HH

template <typename T> [[ gnu::const ]]
constexpr T sq(T x) noexcept { return x*x; }
template <typename T, typename... TT> [[ gnu::const ]]
constexpr T sq(T x, TT... xx) noexcept { return sq(x)+sq(xx...); }

#endif
