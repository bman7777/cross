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

void Context::RegisterService(Service::Key key, Service* serv)
{
    mServices[key] = serv;
}

bool Context::EnsureService(Service::Key key, Service* serv)
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

// note: a given service requested *may not* exist
Service* Context::GetService(Service::Key key) const
{
    Service* serv = NULL;
    ServiceList::const_iterator iter = mServices.find(key);
    if(iter != mServices.end())
    {
        serv = iter->second;
    }

    // then look up the tree if we found nothing
    if(serv == NULL && mParentContext)
    {
        serv = mParentContext->GetService(key);
    }

    return serv;
}

bool Context::HasService(Service::Key key) const
{
    return (GetService(key) != NULL);
}

void Context::UnRegisterService(Service::Key key, Service* serv)
{
    ServiceList::const_iterator iter = mServices.find(key);
    if(iter != mServices.end() && iter->second == serv)
    {
        mServices.erase(iter);
    }
}

}


