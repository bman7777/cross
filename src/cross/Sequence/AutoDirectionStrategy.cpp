/****************************************************************/
/// \class Cross::AutoDirectionStrategy
/// \ingroup Sequence
/// \date Feb 1, 2014
/// \brief When more than 1 route is possible as a sequence is
///         being processed- this strategy provides an
///         automatic route based on priority, errors, and
///         availability.
/****************************************************************/

#include "cross/Sequence/AutoDirectionStrategy.h"
#include "cross/Sequence/SeqNode.h"
#include "cross/Sequence/Sequence.h"

namespace Cross
{

SeqNode* AutoDirectionStrategy::GetNextNode(SeqConnect* current, ErrorCode e)
{
    SeqNode* returnNode = NULL;
    if(e == ERR_NONE && current)
    {
        //first check forward for children
        if(mPriorityDir == DIR_FORWARD)
        {
            SeqNode* fwdNode = GetNextForwardNode(current);
            if(fwdNode)
            {
                returnNode = fwdNode;
            }
            else
            {
                returnNode = GetNextBackwardNode(current);
            }
        }
        else if(mPriorityDir == DIR_BACKWARD)
        {
            SeqNode* backNode = GetNextBackwardNode(current);
            if(backNode)
            {
                returnNode = backNode;
            }
            else
            {
                returnNode = GetNextForwardNode(current);
            }
        }
    }

    return returnNode;
}

SeqNode* AutoDirectionStrategy::GetNextForwardNode(SeqConnect* current)
{
    for(SeqConnect::Connection::iterator i = current->GetConnectionBegin(); i != current->GetConnectionEnd(); i++)
    {
        if(i->second & DIR_FORWARD)
        {
            return i->first;
        }
    }

    return NULL;
}

SeqNode* AutoDirectionStrategy::GetNextBackwardNode(SeqConnect* current)
{
    for(SeqConnect::Connection::iterator i = current->GetConnectionBegin(); i != current->GetConnectionEnd(); i++)
    {
        if(i->second & DIR_BACKWARD)
        {
            return i->first;
        }
    }

    return NULL;
}

}


