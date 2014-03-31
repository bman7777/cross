/*
 * IModuleWrapper.h
 *
 *  Created on: Oct 3, 2013
 *      Author: bmanson
 */

#ifndef FLOW_IMODULEWRAPPER_H_
#define FLOW_IMODULEWRAPPER_H_

#include "cross/Context/FlowDefine.h"

namespace Cross
{

class Context;
class Continuer;

class IModuleWrapper
{
public:
	virtual ~IModuleWrapper() {}
	virtual ModuleKey GetKey() const = 0;
	virtual void Run(Context* ctx, Continuer* cnt) = 0;
	virtual Context* GetContext() const = 0;
};

}

#endif // FLOW_IMODULEWRAPPER_H_
