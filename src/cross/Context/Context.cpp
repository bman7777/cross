/****************************************************************/
/// \class Cross::Context
/// \ingroup Context
/// \date Oct 4, 2013
/// \brief Context holds details about location of flow that are
///         hidden to concrete implementation.  Context is also
///         a container for services.
/****************************************************************/

#include "cross/Context/Context.h"

namespace Cross
{
/// \brief construct the context that will be a link to all
///         services and flow.  This will be passed/forked
///         through various flows.  A link to immediate
///         parent must always be maintained.  Never allow
///         a NULL parent to be passed.
/// \param parentContext - a link to parent context.
Context::Context(Context* parentContext) :
    mParentContext(parentContext), AllocationContext(parentContext)
{
    assert(mParentContext);
}

/// \brief register a service with this context.  This is hashed
///         with a key that can later be used to retrieve this
///         service
/// \param key - a unique key that identifies the service
/// \param service - a service implementation that provides some
///         functionality
void Context::RegisterService(const DataContext::Key& key, Service* serv)
{
    mServices[key] = serv;
}

/// \brief register a service ONLY if no one has previously
///         registered this service.  This might occur in
///         situations where the client is satisfied with a
///         default service, but will instantiate one if the
///         need arises.
/// \param key - a unique key that identifies the service
/// \param service - a service implementation that provides some
///         functionality
bool Context::EnsureService(const DataContext::Key& key, Service* serv)
{
    bool serviceAdded = false;
    ServiceList::const_iterator iter = mServices.find(key);
    if(iter == mServices.end())
    {
        if(!mParentContext || !mParentContext->HasService(key))
        {
            RegisterService(key, serv);
            serviceAdded = true;
        }
    }

    return serviceAdded;
}

/// \brief get a service from this context (or a parent
///         context) if one exists.  This allows decouples
///         foreign functionality from the modules that use
///         them.  NOTE: a service may not exist.
/// \param key - a unique key that identifies the service
/// \return service - a service implementation that provides some
///         functionality.  NULL will be returned if none exists
Service* Context::GetService(const DataContext::Key& key) const
{
    Service* serv = NULL;
    ServiceList::const_iterator iter = mServices.find(key);
    if(iter != mServices.end())
    {
        serv = iter->second;
    }

    // then look up the tree if we found nothing
    // IFF we are not ourselves a parent (like GenesisContext)
    if(serv == NULL && mParentContext && this != mParentContext)
    {
        serv = mParentContext->GetService(key);
    }

    return serv;
}

/// \brief Determine if a service can be obtained.
/// \param key - a unique key that identifies the service
/// \return T: this service is available; F: this
///         service has not been registered.
bool Context::HasService(const DataContext::Key& key) const
{
    return (GetService(key) != NULL);
}

/// \brief unregister a service that was registered with
///         this context.  We will tolerate unregistering
///         a service that does not exist in this context.
/// \param key - a unique key that identifies the service
/// \param service - a service implementation that provides some
///         functionality
void Context::UnRegisterService(const DataContext::Key& key, Service* serv)
{
    ServiceList::const_iterator iter = mServices.find(key);
    if(iter != mServices.end() && iter->second == serv)
    {
        mServices.erase(iter);
    }
}

}


