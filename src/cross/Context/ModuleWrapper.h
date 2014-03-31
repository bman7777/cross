/*
 * ModuleWrapper.h
 *
 *  Created on: Oct 4, 2013
 *      Author: bmanson
 */

#ifndef MODULE_WRAPPER_H_
#define MODULE_WRAPPER_H_

#include <cassert>
#include <stddef.h>
#include "cross/Context/IModuleWrapper.h"

namespace Cross
{

class Context;
class Continuer;
class Serial;

template <class T>
class ModuleWrapper : public IModuleWrapper
{
public:
	ModuleWrapper(Serial* s=NULL) :
		mFlow(NULL),
		mContext(NULL),
		mKey(MakeFlowKey()),
		mSerial(s)
	{}

	virtual ~ModuleWrapper()
	{
		if(mFlow)
		{
			delete mFlow;
			mFlow = NULL;
		}
	}

protected:
	virtual ModuleKey GetKey() const { return mKey; }

	void Run(Context* ctx, Continuer* cnt=NULL)
	{
		// make sure we never run a module twice!
		assert(!mFlow);

		mContext = ctx;
		mFlow = new(*ctx) T(ctx, cnt, mSerial);
	}

	Context* GetContext() const { return mContext; }

private:
	T* mFlow;
	Context* mContext;
	ModuleKey mKey;
	Serial* mSerial;
};

}

#endif // MODULE_WRAPPER_H_

