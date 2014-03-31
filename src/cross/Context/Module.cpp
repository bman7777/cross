/*
 * Module.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: bmanson
 */

#include <malloc.h>
#include "cross/Context/Module.h"

namespace Cross
{

void* Module::operator new (size_t size, Context& ctx)
{
	return malloc(size);
	// Cross::Allocation::Get(ctx).allocate(size);
}

// this will be called in most cases
void Module::operator delete (void* module)
{
	if(module)
	{
		// Cross::Allocation::Get(module->GetContext()).deallocate(module);
		free(module);
	}
}

// note: this will only be called if the module constructor
// throws an exception on construction of the module
void Module::operator delete (void* module, Context& cxt)
{
	if(module)
	{
		// Cross::Allocation::Get(cxt).deallocate(module);
		free(module);
	}
}

}


