///==============================================================
///	Cross::Context
/// Created on: Oct 4, 2013
///
/// \brief Context holds details about location of flow that are
///			hidden to concrete implementation.  Context is also
///			a container for services.
///==============================================================

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <boost/unordered_map.hpp>
#include <utility>
#include <stddef.h>
#include "cross/Service/Service.h"

namespace Cross
{

class Context
{
public:
	Context() : mParentContext(NULL) {}
	Context(Context* parent) : mParentContext(parent) {}
	virtual ~Context() {}

	void RegisterService(Service::Key key, Service* serv);

	bool EnsureService(Service::Key key, Service* serv);

	Service* GetService(Service::Key key) const;

	bool HasService(Service::Key key) const;

	void UnRegisterService(Service::Key key, Service* serv);

private:
	typedef boost::unordered_map<Service::Key, Service*> ServiceList;

	ServiceList mServices;
	Context* mParentContext;
};

}

#endif /* CONTEXT_H_ */
