/*
 * Allocation.h
 *
 *  Created on: Oct 4, 2013
 *      Author: bmanson
 */

#ifndef ALLOCATION_H_
#define ALLOCATION_H_

#include "cross/Context/Context.h"
#include "cross/Service/Service.h"

namespace Cross
{

class Allocation : public Service
{
public:
	static const Service::Key KEY = 0xa110cc;

	Allocation(Context& ctx) : mContext(ctx) {}
	virtual ~Allocation() {}

	virtual void* Allocate();
	virtual void DeAllocate();

	static Allocation* Get(Context* ctx)
	{
		return static_cast<Allocation*>(Service::Get(KEY, ctx));
	}

private:
	Context mContext;
};

} //end namespace


#endif /* ALLOCATION_H_ */


