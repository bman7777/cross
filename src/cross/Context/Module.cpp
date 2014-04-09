/****************************************************************/
/// \class Cross::Module
/// \ingroup Context
/// \date Oct 4, 2013
/// \brief A base class for modules that allows allocations to
///         always draw from services.
/****************************************************************/

#include "cross/Context/Module.h"
#include "cross/Service/Allocation.h"

namespace Cross
{

/// \brief allocate a new module
/// \param size - the size of the module to be allocated
/// \param ctx - the context to use for the allocation
/// \return memory that can be used for the new module
void* Module::operator new (size_t size, Context* ctx)
{
    return Allocation::Get(ctx)->Allocate(size);
}

/// \brief this is the more common case of destruction
/// \param module - the module to be deleted
void Module::operator delete (void* module)
{
    if(module)
    {
        Allocation::Get(static_cast<Module*>(module)->GetContext())->DeAllocate(module);
    }
}

/// \brief this will only be called if the module constructor
///         throws an exception on construction of the module
/// \param module - the module to be deleted
/// \param ctx - the context to use for the deallocation
void Module::operator delete (void* module, Context* ctx)
{
    if(module)
    {
        Allocation::Get(ctx)->DeAllocate(module);
    }
}

}

