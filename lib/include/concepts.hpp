#pragma once

#include <concepts>
#include <type_traits>

#ifdef __APPLE__

namespace std {
namespace details {

template<class _Tp, class _Up>
concept same_as_impl = is_same_v<_Tp, _Up>;

}

template<class _Tp, class _Up>
concept same_as = details::same_as_impl<_Tp, _Up> && details::same_as_impl<_Up, _Tp>;

}

#endif
