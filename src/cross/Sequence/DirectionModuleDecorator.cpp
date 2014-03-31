/*
 * UpdateDirSeqNode.cpp
 *
 *  Created on: Feb 4, 2014
 *      Author: brian
 */

#include "cross/Context/Continuer.h"
#include "cross/Context/IModuleWrapper.h"
#include "cross/Sequence/AutoDirectionStrategy.h"
#include "cross/Sequence/DirectionModuleDecorator.h"

namespace Cross
{

DirectionModuleDecorator::DirectionModuleDecorator(AutoDirectionStrategy* strat, Direction newDir, IModuleWrapper* mod) :
	mStrategy(strat), mNewDir(newDir), mModule(mod), mContinue(NULL), mKey(MakeFlowKey()), mContext(NULL)
{
}

void DirectionModuleDecorator::Run(Context* ctx, Continuer* cnt)
{
	mContext = ctx;
	mContinue = cnt;
	if(mModule)
	{
		mModule->Run(ctx, this);
	}
	else
	{
		Continue(ctx, ERR_NONE);
	}
}

void DirectionModuleDecorator::Continue(Context* ctx, ErrorCode e)
{
	if(mStrategy)
	{
		mStrategy->UpdateDir(mNewDir);
	}

	if(mContinue)
	{
		mContinue->Continue(ctx, ERR_NONE);
	}
}

}
