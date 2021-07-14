///
#ifndef BELA_TYPES_HPP
#define BELA_TYPES_HPP
#include <cstddef>
#include <concepts>

namespace bela {
#ifndef __BELA__SSIZE_DEFINED_T
#define __BELA__SSIZE_DEFINED_T
using __bela__ssize_t = std::ptrdiff_t;
#endif
using ssize_t = __bela__ssize_t;

template <class _Ty, class... _Types>
inline constexpr bool is_any_of_v = // true if and only if _Ty is in _Types
    std::disjunction_v<std::is_same<_Ty, _Types>...>;

template <class T>
inline constexpr bool is_character_v =
    is_any_of_v<std::remove_cv_t<T>, char, signed char, unsigned char, wchar_t, char8_t, char16_t, char32_t>;

template <class T>
concept character = is_character_v<T>;

} // namespace bela

#endif