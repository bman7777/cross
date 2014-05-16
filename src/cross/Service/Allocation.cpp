/****************************************************************/
/// \class Cross::Allocation
/// \ingroup Service
/// \date Apr 5, 2014
/// \brief A service that provides allocation support for
///         flow-based entities.  This can create/destroy objects
///         from similar heaps or pools of memory across feature
///         lines.
/****************************************************************/

#include "cross/Service/Allocation.h"

namespace Cross
{

AllocTracker<Allocation::DestructionCallback> Allocation::sAllocTrack;

/// \brief deallocate memory created from allocate
/// \param alloc - the previously allocated ptr
void Allocation::Delete(void* alloc)
{
    DestructionCallback* cb = sAllocTrack.EndTrack(alloc);
    if(cb)
    {
        (*cb)();

        Allocator::rebind<DestructionCallback>::other(mGeneralAllocator).destroy(cb);
        Allocator::rebind<DestructionCallback>::other(mGeneralAllocator).deallocate(cb, 1);
    }
}

/// \brief helper for getting the allocation context
///         that will prevent/hide the need for static
///         casts.
/// \param context - which context to use for getting
///         the service
Allocation* Allocation::Get(Context* ctx)
{
    return static_cast<Allocation*>(Service::Get(typeid(Allocation), ctx));
}

}

