/****************************************************************/
/// \class Cross::AutoDirectionStrategy
/// \ingroup Sequence
/// \date Feb 1, 2014
/// \brief When more than 1 route is possible as a sequence is
///         being processed- this strategy provides an
///         automatic route based on priority, errors, and
///         availability.
/****************************************************************/
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
    AutoDirectionStrategy(const Direction& priorityDir) : mPriorityDir(priorityDir) { }
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
