/****************************************************************/
/// \class Cross::PriorityDirectionStrategy
/// \ingroup Sequence
/// \date Feb 9, 2014
/// \brief Sibling to the automatic strategy- this is able to
///         select from a prioritized list of direction/module
///         pairs and push the flow of the sequence in a pre-
///         defined direction.
/****************************************************************/

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
