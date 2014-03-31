/*
 * Context.h
 *
 *  Created on: Oct 4, 2013
 *      Author: bmanson
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <boost/unordered_map.hpp>
#include <utility>
#include <stddef.h>
#include "cross/Service/Service.h"

namespace Cross
{

// used to retrieve Services
class Context
{
public:
	Context() : mParentContext(NULL) {}
	Context(Context* parent) : mParentContext(parent) {}
	virtual ~Context() {}

	//Context* GetParentContext() const { return mParentContext; }

	void RegisterService(Service::Key key, Service* serv);

	bool EnsureService(Service::Key key, Service* serv);

	// note: a given service requested *may not* exist
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



