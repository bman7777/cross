/*
 * RunContext.cpp
 *
 *  Created on: Feb 14, 2014
 *      Author: brian
 */

#include "cross/Sequence/RunContext.h"

namespace Cross
{

RunContext::RunContext(Context* ctx, Continuer* cnt, SeqNode* node, IDirectionStrategy* strategy) :
	mContinue(cnt),
	mContext(ctx),
	mIter(node, strategy)
{
	mIter.Run(mContext, this);
}

void RunContext::BeginRun(Context* ctx, Continuer* cnt, SeqNode* node, IDirectionStrategy* strategy)
{
	if(node)
	{
		RunContext* run = new RunContext(ctx, cnt, node, strategy);
	}
	else
	{
		cnt->Continue(ctx, ERR_NONE);
	}
}

void RunContext::Continue(Context* ctx, ErrorCode e)
{
	mContinue->Continue(ctx, e);

	RunContext::FinishRun(this);
}

void RunContext::FinishRun(RunContext* ctx)
{
	delete ctx;
}

}
