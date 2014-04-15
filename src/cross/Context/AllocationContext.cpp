/****************************************************************/
/// \class Cross::AllocationContext
/// \ingroup Context
/// \date Apr 11, 2014
/// \brief all classes that require use of allocation context
///         should derive from this base class
/****************************************************************/

#include "cross/Context/AllocationContext.h"
#include "cross/Service/Allocation.h"

namespace Cross
{

/// \brief allocate a new object
/// \param size - the size of the module to be allocated
/// \param ctx - the context to use for the allocation
/// \return memory that can be used for the new module
void* AllocationContext::operator new (size_t size, Context* ctx)
{
    return Allocation::Get(ctx)->Allocate(size);
}

/// \brief this is the more common case of destruction
/// \param allocCtx - the object to be deleted
void AllocationContext::operator delete (void* allocCtx)
{
    if(allocCtx)
    {
        Allocation::Get(static_cast<AllocationContext*>(allocCtx)->GetAllocContext())->DeAllocate(allocCtx);
    }
}

/// \brief this will only be called if the object constructor
///         throws an exception on construction
/// \param allocCtx - the object to be deleted
/// \param ctx - the context to use for the deallocation
void AllocationContext::operator delete (void* allocCtx, Context* ctx)
{
    if(allocCtx)
    {
        Allocation::Get(ctx)->DeAllocate(allocCtx);
    }
}

}
