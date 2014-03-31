/*
 * Sequence.cpp
 *
 *  Created on: Jan 5, 2014
 *      Author: brian
 */

#include "cross/Service/SequenceFactory.h"
#include "cross/Sequence/RunContext.h"
#include "cross/Sequence/SeqNode.h"
#include "cross/Sequence/Sequence.h"
#include "cross/Sequence/SeqStream.h"

namespace Cross
{

Sequence::Sequence(Context* ctx) : SeqNode(ctx), mContext(ctx), mRoot(NULL), mIntraConnect(true)
{
}

void Sequence::Run(Context* ctx, Continuer* cnt)
{
	if(mRoot)
	{
		RunContext::BeginRun(ctx, cnt, mRoot);
	}
	else
	{
		SeqNode::Run(ctx, cnt);
	}
}

bool Sequence::operator==(IModuleWrapper* mod) const
{
	bool isSame = false;
	if(mRoot)
	{
		isSame = (*mRoot == mod);
	}
	else
	{
		isSame = SeqNode::operator==(mod);
	}
	return isSame;
}

SeqNode* Sequence::AddConnection(SeqNode* n, Direction d)
{
	SeqNode* returnNode = NULL;
	if(mIntraConnect)
	{
		if(mRoot)
		{
			returnNode = mRoot->Connect()->AddConnection(n, d);
		}
		else
		{
			mRoot = n;
			returnNode = mRoot;
		}
	}
	else
	{
		returnNode = SeqNode::AddConnection(n, d);
	}

	return returnNode;
}

SeqNode* Sequence::AddConnection(IModuleWrapper* m, Direction d)
{
	SeqNode* returnNode = NULL;
	if(mIntraConnect)
	{
		if(mRoot)
		{
			returnNode = mRoot->Connect()->AddConnection(m, d);
		}
		else
		{
			mRoot = SequenceFactory::Get(mContext)->CreateSeqNode(m);
			returnNode = mRoot;
		}
	}
	else
	{
		returnNode = SeqNode::AddConnection(m, d);
	}

	return returnNode;
}

SeqNode* Sequence::AddConnection(SeqStream* s, Direction d)
{
	SeqNode* returnNode = NULL;
	if(mIntraConnect)
	{
		if(mRoot)
		{
			returnNode = mRoot->Connect()->AddConnection(s->GetHead(), d);
		}
		else
		{
			mRoot = s->GetHead();
			returnNode = mRoot;
		}
	}
	else
	{
		returnNode = SeqNode::AddConnection(s->GetHead(), d);
	}

	return returnNode;
}

}
