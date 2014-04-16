/****************************************************************/
/// \class Cross::Allocation
/// \ingroup Service
/// \date Apr 5, 2014
/// \brief A service that provides allocation support for
///         flow-based entities.  This can create/destroy objects
///         from similar heaps or pools of memory across feature
///         lines.
/****************************************************************/

#include <malloc.h>
#include "cross/Service/Allocation.h"

namespace Cross
{

const DataContext::Key Allocation::KEY = DataContext::MakeKey();

/// \brief allocate memory for some module potentially from some
///         pooled memory
/// \param size - how much to allocate
/// \return ptr to new memory
void* Allocation::Allocate(size_t size)
{
    return malloc(size);
}

/// \brief deallocate memory created from allocate
/// \param the previously allocated ptr
void Allocation::DeAllocate(void* ptr)
{
    free(ptr);
}

/// \brief helper for getting the allocation context
///         that will prevent/hide the need for static
///         casts.
/// \param context - which context to use for getting
///         the service
Allocation* Allocation::Get(Context* ctx)
{
    return static_cast<Allocation*>(Service::Get(KEY, ctx));
}

}
