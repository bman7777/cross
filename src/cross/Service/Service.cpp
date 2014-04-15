/****************************************************************/
/// \class Cross::Service
/// \ingroup Service
/// \date Oct 4, 2013
/// \brief A base class for services that provides support for
///         service keys that index into contexts.
/****************************************************************/

#include <boost/uuid/uuid_generators.hpp>
#include "cross/Context/Context.h"
#include "cross/Service/Service.h"

namespace Cross
{

/// \brief create a new key using a UUID to identify the service
///         uniquely.  This can be used to hash the service.
/// \return UUID that identifies the service
Service::Key Service::MakeKey()
{
    return boost::uuids::random_generator()();
}

/// \brief get a service using its key and context
/// \param key - this comes from MakeKey() and is a unique ID
///               for all services of its kind
/// \param context- where are you asking from?
/// \return ptr to service (or NULL if there is none.)
Service* Service::Get(const Service::Key& k, Context* ctx)
{
    assert(ctx);
    return ctx->GetService(k);
}

}
