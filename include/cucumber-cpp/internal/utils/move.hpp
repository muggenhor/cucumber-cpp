#ifndef CUKE_MOVE_HPP_
#define CUKE_MOVE_HPP_

#if __cplusplus >= 201103L
#include <utility> // for std::move
#else
#include <algorithm> // for std::swap
#endif

namespace cucumber {
namespace internal {

#if __cplusplus >= 201103L
using std::move;
#else
template <typename T>
T move(T& a) {
    using std::swap; // fallback implementation, performance is no worse than copying if destroying
                     // default constructed T is cheap

    T r; // expects: both default construction of T and destruction of a default constructed T to be
         // cheap
    swap(r, a);
    return r; // expects: NRVO to elide copy on return
}
#endif
}
}

#endif /* CUKE_MOVE_HPP_ */
