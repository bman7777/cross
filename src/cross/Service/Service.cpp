/****************************************************************/
/// \class Cross::Service
/// \ingroup Service
/// \date Oct 4, 2013
/// \brief A base class for services that provides support for
///         service keys that index into contexts.
/****************************************************************/

#include "cross/Context/Context.h"
#include "cross/Service/Service.h"

namespace Cross
{

/// \brief get a service using its key and context
/// \param type - type of service being requested
/// \param context- where are you asking from?
/// \return ptr to service (or NULL if there is none.)
Service* Service::Get(const Type& t, Context* ctx)
{
    assert(ctx);
    return ctx->GetService(t);
}

}
