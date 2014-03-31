/*
 * PriorityDirectionStrategy.h
 *
 *  Created on: Feb 9, 2014
 *      Author: brian
 */

#ifndef PRIORITYDIRECTIONSTRATEGY_H_
#define PRIORITYDIRECTIONSTRATEGY_H_

#include <utility>
#include <vector>
#include "cross/Context/FlowDefine.h"
#include "cross/Sequence/IDirectionStrategy.h"

namespace Cross
{

class IModuleWrapper;
class SeqNode;

class PriorityDirectionStrategy : public IDirectionStrategy
{
public:
	PriorityDirectionStrategy() { }
	virtual ~PriorityDirectionStrategy() {}

	void AddNextHighestPriority(IModuleWrapper* module, Direction dir);
	virtual SeqNode* GetNextNode(SeqConnect* current, ErrorCode e);

private:

	SeqNode* GetNextForwardNode(SeqNode* current);
	SeqNode* GetNextBackwardNode(SeqNode* current);

	typedef std::pair<IModuleWrapper*, Direction> PriorityPair;
	typedef std::vector<PriorityPair> PriorityList;
	PriorityList mPriorities;
};

}


#endif /* PRIORITYDIRECTIONSTRATEGY_H_ */
