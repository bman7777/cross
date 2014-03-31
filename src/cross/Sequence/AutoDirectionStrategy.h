/*
 * AutoDirectionStrategy.h
 *
 *  Created on: Feb 1, 2014
 *      Author: brian
 */

#ifndef AUTODIRECTIONSTRATEGY_H_
#define AUTODIRECTIONSTRATEGY_H_

#include "cross/Context/FlowDefine.h"
#include "cross/Sequence/IDirectionStrategy.h"

namespace Cross
{

class SeqNode;

class AutoDirectionStrategy : public IDirectionStrategy
{
public:
	AutoDirectionStrategy(Direction priorityDir) : mPriorityDir(priorityDir) { }
	virtual ~AutoDirectionStrategy() {}

	virtual SeqNode* GetNextNode(SeqConnect* current, ErrorCode e);
	void UpdateDir(Direction dir) { mPriorityDir = dir; }

private:

	SeqNode* GetNextForwardNode(SeqConnect* current);
	SeqNode* GetNextBackwardNode(SeqConnect* current);

	Direction mPriorityDir;
};
}


#endif /* AUTODIRECTIONSTRATEGY_H_ */
