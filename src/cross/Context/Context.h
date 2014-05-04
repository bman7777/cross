/****************************************************************/
/// \class Cross::Context
/// \ingroup Context
/// \date Oct 4, 2013
/// \brief Context holds details about location of flow that are
///         hidden to concrete implementation.  Context is also
///         a container for services.
/****************************************************************/

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <boost/unordered_map.hpp>
#include <utility>
#include <stddef.h>
#include "cross/Context/AllocationContext.h"
#include "cross/Service/Service.h"

namespace Cross
{

class Context : public AllocationContext
{
public:
    explicit Context(Context* parentContext);
    virtual ~Context() {}

    void RegisterService(const Service::Type& t, Service* serv);

    bool EnsureService(const Service::Type& t, Service* serv);

    Service* GetService(const Service::Type& t) const;

    bool HasService(const Service::Type& t) const;

    void UnRegisterService(const Service::Type& t, Service* serv);

private:
    typedef boost::unordered_map<size_t, Service*> ServiceList;
    ServiceList mServices;

    Context* mParentContext;
};

}

#endif /* CONTEXT_H_ */
