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
#include "cross/Context/DataContext.h"
#include "cross/Service/Service.h"

namespace Cross
{

class Context : public AllocationContext
{
public:
    explicit Context(Context* parentContext);
    virtual ~Context() {}

    void RegisterService(const DataContext::Key& key, Service* serv);

    bool EnsureService(const DataContext::Key& key, Service* serv);

    Service* GetService(const DataContext::Key& key) const;

    bool HasService(const DataContext::Key& key) const;

    void UnRegisterService(const DataContext::Key& key, Service* serv);

private:
    typedef boost::unordered_map<DataContext::Key, Service*> ServiceList;
    ServiceList mServices;

    Context* mParentContext;
};

}

#endif /* CONTEXT_H_ */
