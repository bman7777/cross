/****************************************************************/
/// \class Cross::Allocation
/// \ingroup Service
/// \date Oct 4, 2013
/// \brief A service that provides allocation support for
///         flow-based entities.  This can create/destroy objects
///         from similar heaps or pools of memory across feature
///         lines.
/****************************************************************/

#ifndef ALLOCATION_H_
#define ALLOCATION_H_

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <memory>
#include "cross/Service/AllocTracker.h"
#include "cross/Service/Service.h"

namespace Cross
{

class Context;

class Allocation : public Service
{
public:
    Allocation() {}
    virtual ~Allocation() {}

    template <class T, typename... Args>
    T* New(Args&&... args);

    void Delete(void* alloc);

    static Allocation* Get(Context* ctx);

private:

    typedef std::allocator<void> Allocator;
    typedef boost::function<void ()> DestructionCallback;

    template <class T>
    void Delete(Allocator* allocator, T* ptr);

    static AllocTracker<DestructionCallback> sAllocTrack;

    Allocator mGeneralAllocator;
};

template <class T, typename... Args>
T* Allocation::New(Args&&... args)
{
    T* mem = typename Allocator::rebind<T>::other(mGeneralAllocator).allocate(1);
    typename Allocator::rebind<T>::other(mGeneralAllocator).construct(mem, args...);

    DestructionCallback* cb = typename Allocator::rebind<DestructionCallback>::other(mGeneralAllocator).allocate(1);
    typename Allocator::rebind<DestructionCallback>::other(mGeneralAllocator).construct(cb);

    *cb = boost::bind(&Allocation::Delete<T>, this, &mGeneralAllocator, mem);

    sAllocTrack.StartTrack(mem, cb);

    return mem;
}

template <class T>
void Allocation::Delete(Allocator* allocator, T* ptr)
{
    typename Allocator::rebind<T>::other(*allocator).destroy(ptr);
    typename Allocator::rebind<T>::other(*allocator).deallocate(ptr, 1);
}

} //end namespace


#endif /* ALLOCATION_H_ */


