/****************************************************************/
/// \class Cross::PriorityDirectionStrategy
/// \ingroup Sequence
/// \date Feb 9, 2014
/// \brief Sibling to the automatic strategy- this is able to
///         select from a prioritized list of direction/module
///         pairs and push the flow of the sequence in a pre-
///         defined direction.
/****************************************************************/

#include "cross/Sequence/PriorityDirectionStrategy.h"
#include "cross/Sequence/SeqNode.h"

namespace Cross
{

void PriorityDirectionStrategy::AddNextHighestPriority(IModuleWrapper* module, Direction dir)
{
    mPriorities.push_back(PriorityPair(module, dir));
}

SeqNode* PriorityDirectionStrategy::GetNextNode(SeqConnect* current, ErrorCode e)
{
    SeqNode* newCurrent = NULL;
    if(current)
    {
        for(PriorityList::iterator i = mPriorities.begin(); i != mPriorities.end(); i++)
        {
            bool foundIt = false;
            for(SeqConnect::Connection::iterator j = current->GetConnectionBegin(); j != current->GetConnectionEnd(); j++)
            {
                if((j->second == i->second) && (*(j->first) == i->first))
                {
                    newCurrent = j->first;
                    foundIt = true;
                    break;
                }
            }

            if(foundIt)
            {
                break;
            }
        }
    }

    return newCurrent;
}

}
