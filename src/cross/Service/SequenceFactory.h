/*
 * SequenceFactory.h
 *
 *  Created on: Mar 25, 2014
 *      Author: brian
 */

#ifndef SEQUENCEFACTORY_H_
#define SEQUENCEFACTORY_H_

#include "cross/Context/Context.h"
#include "cross/Service/Service.h"

namespace Cross
{

class IModuleWrapper;
class Sequence;
class SeqNode;

class SequenceFactory : public Service
{
public:
	static const Service::Key KEY = 0x5e71ce;

	SequenceFactory(Context* ctx) : mContext(ctx) {}
	virtual ~SequenceFactory() {}

	Sequence* CreateSequence();
	SeqNode* CreateSeqNode(IModuleWrapper* m = NULL);

	static SequenceFactory* Get(Context* ctx)
	{
		return static_cast<SequenceFactory*>(Service::Get(KEY, ctx));
	}

private:
	Context* mContext;
};

}


#endif /* SEQUENCEFACTORY_H_ */
