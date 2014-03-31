/*
 * SequenceFactory.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: brian
 */

#include "cross/Service/SequenceFactory.h"
#include "cross/Sequence/Sequence.h"
#include "cross/Sequence/SeqNode.h"

namespace Cross
{

Sequence* SequenceFactory::CreateSequence()
{
	return new Sequence(mContext);
}

SeqNode* SequenceFactory::CreateSeqNode(IModuleWrapper* m)
{
	return new SeqNode(mContext, m);
}

}

