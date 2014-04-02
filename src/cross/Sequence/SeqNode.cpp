/*
 * SeqNode.cpp
 *
 *  Created on: Jan 31, 2014
 *      Author: brian
 */

#ifndef SEQNODE_CPP_
#define SEQNODE_CPP_

#include "cross/Context/Continuer.h"
#include "cross/Context/IModuleWrapper.h"
#include "cross/Sequence/SeqNode.h"

namespace Cross
{

SeqNode::SeqNode(Context* ctx, IModuleWrapper* module) :
	SeqConnect(ctx), mModule(module)
{
}

SeqNode::SeqNode(Context* ctx, SeqNode* node) :
	SeqConnect(ctx), mModule(node->GetModule())
{
}

void SeqNode::Run(Context* ctx, Continuer* cnt)
{
	if(mModule)
	{
		mModule->Run(ctx, cnt);
	}
	else
	{
		cnt->Continue(ctx, ERR_NONE);
	}
}

bool SeqNode::operator==(IModuleWrapper* mod) const
{
	return mod == mModule;
}

}

#endif /* SEQNODE_CPP_ */