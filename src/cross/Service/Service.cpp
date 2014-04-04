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

Service* Service::Get(Service::Key k, Context* ctx)
{
    assert(ctx);
    return ctx->GetService(k);
}

}
