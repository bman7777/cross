/****************************************************************/
/// \class Cross::Allocation
/// \ingroup Service
/// \date Apr 5, 2014
/// \brief A service that provides allocation support for
///         flow-based entities.  This can create/destroy objects
///         from similar heaps or pools of memory across feature
///         lines.
/****************************************************************/

#include "cross/Context/AllocationContext.h"
#include "cross/Service/Allocation.h"

namespace Cross
{

/// \brief deallocate memory created from allocate
/// \param the previously allocated ptr
void Allocation::Delete(AllocationContext* alloc)
{
    AllocInfo* info = alloc->GetAllocInfo();
    info->Callback();
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

