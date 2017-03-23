#ifndef CUKE_UNIQUE_PTR_
#define CUKE_UNIQUE_PTR_

#include <boost/version.hpp>

#if BOOST_VERSION >= 105700
# include <boost/move/unique_ptr.hpp>
# include <boost/move/utility_core.hpp>

namespace cucumber {
namespace internal {

template <typename T>
struct unique
{
    typedef ::boost::movelib::unique_ptr<T> ptr;
};

}
}

namespace boost {
namespace movelib {

/// Alternative for boost::interprocess::unique_ptr's operator= which doesn't support assignment from prvalues when relying on move emulation
template <typename T>
unique_ptr<T>& assign(unique_ptr<T>& lhs, unique_ptr<T> rhs) {
    return lhs = ::boost::move(rhs);
}

}
}
#else
# include <boost/checked_delete.hpp>
# include <boost/interprocess/detail/move.hpp>
# include <boost/interprocess/smart_ptr/unique_ptr.hpp>

namespace cucumber {
namespace internal {

template <typename T>
struct unique
{
    typedef ::boost::interprocess::unique_ptr<T, ::boost::checked_deleter<T> > ptr;
};

}
}

namespace boost {
namespace interprocess {

/// Alternative for unique_ptr's operator= which doesn't support assignment from prvalues when relying on move emulation
template <typename T>
unique_ptr<T, checked_deleter<T> >& assign(
        unique_ptr<T, checked_deleter<T> >& lhs, unique_ptr<T, checked_deleter<T> > rhs)
{
    return lhs = ::boost::interprocess::move(rhs);
}

}
}
#endif

#endif /* CUKE_UNIQUE_PTR_ */
