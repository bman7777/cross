/*
 * Service.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: bmanson
 */

#include "cross/Context/Context.h"
#include "cross/Service/Service.h"

namespace Cross
{

Service* Service::Get(Service::Key k, Context* ctx)
{
	assert(ctx);
	return ctx->GetService(k);
}

}
