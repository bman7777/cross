/*
 * GenesisContext.cpp
 *
 *  Created on: Mar 28, 2014
 *      Author: brian
 */

#include "cross/Service/SequenceFactory.h"
#include "cross/Context/Context.h"
#include "cross/Sequence/GenesisContext.h"

namespace Cross
{

static GenesisContext sGenesis;
static Context sContext;
static SequenceFactory sFactory(&sContext);
static bool sIsRegistered = false;

Context* GenesisContext::Get()
{
	if(!sIsRegistered)
	{
		sIsRegistered = true;
		sContext.EnsureService(SequenceFactory::KEY, &sFactory);
	}

	return &sContext;
}

}

