#ifndef CUKE_MAKE_UNIQUE_HPP_
#define CUKE_MAKE_UNIQUE_HPP_

#include <boost/version.hpp>

#if BOOST_VERSION >= 105700
# include <boost/move/make_unique.hpp>
namespace cucumber {
namespace internal {
using boost::movelib::make_unique;
}
}
#else
# include <boost/config.hpp>
# include "unique_ptr.hpp"
# ifndef BOOST_NO_VARIADIC_TEMPLATES
#  include <utility>
# endif

namespace cucumber {
namespace internal {

// SFINAE to disable our make_unique for array types
template <typename T>
struct enable_if_not_array {
    typedef typename unique<T>::ptr type;
};
template <typename T               > struct enable_if_not_array<T[ ]> {};
template <typename T, std::size_t N> struct enable_if_not_array<T[N]> {};

# ifdef BOOST_NO_VARIADIC_TEMPLATES
template <typename T>
typename enable_if_not_array<T>::type make_unique() {
    return typename unique<T>::ptr(new T);
}

template <typename T, typename A1>
typename enable_if_not_array<T>::type make_unique(const A1& a1) {
    return typename unique<T>::ptr(new T(a1));
}
# else
template <typename T, typename... A>
typename enable_if_not_array<T>::type make_unique(A&&... args) {
    return typename unique<T>::ptr(new T(std::forward<A>(args)...));
}
# endif

}
}
#endif

#endif /* CUKE_MAKE_UNIQUE_HPP_ */
