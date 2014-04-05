/****************************************************************/
/// \class Cross::SeqConnect
/// \ingroup Sequence
/// \date Mar 24, 2014
/// \brief This helper owns connection between nodes that allow
///         a network of nodes to be created as a sequence.
///         Connections ultimately contain modules, junctions,
///         and other sequences.
/****************************************************************/

#include "cross/Service/SequenceFactory.h"
#include "cross/Sequence/SeqConnect.h"
#include "cross/Sequence/SeqNode.h"
#include "cross/Sequence/SeqStream.h"
#include "cross/Sequence/Sequence.h"

namespace Cross
{

SeqConnect::SeqPair* SeqConnect::FindConnection(IModuleWrapper* module)
{
    SeqPair* pair = NULL;
    for(Connection::iterator i = mConnect.begin(); i != mConnect.end(); i++)
    {
        if(*(i->first) == module)
        {
            pair = &(*i);
            break;
        }
    }

    return pair;
}

SeqConnect::SeqPair* SeqConnect::FindConnection(SeqNode* node)
{
    SeqPair* pair = NULL;
    for(Connection::iterator i = mConnect.begin(); i != mConnect.end(); i++)
    {
        if(i->first == node)
        {
            pair = &(*i);
            break;
        }
    }

    return pair;
}

SeqNode* SeqConnect::AddConnection(SeqNode* n, Direction d)
{
    SeqNode* returnNode = NULL;
    SeqPair* pair = FindConnection(n);
    if(!pair)
    {
        mConnect.push_back(SeqPair(n, d));
        returnNode = n;
    }
    else
    {
        pair->second |= d;
        returnNode = pair->first;
    }

    return returnNode;
}

SeqNode* SeqConnect::AddConnection(IModuleWrapper* m, Direction d)
{
    SeqNode* returnNode = NULL;
    SeqPair* pair = FindConnection(m);
    if(!pair)
    {
        SeqNode* node = SequenceFactory::Get(mContext)->CreateSeqNode(m);

        mConnect.push_back(SeqPair(node, d));
        returnNode = node;
    }
    else
    {
        pair->second |= d;
        returnNode = pair->first;
    }

    return returnNode;
}

SeqNode* SeqConnect::AddConnection(SeqStream* s, Direction d)
{
    SeqPair* pair = FindConnection(s->GetHead());
    if(!pair)
    {
        mConnect.push_back(SeqPair(s->GetHead(), d));
    }
    else
    {
        pair->second |= d;
    }

    return s->GetCurrent();
}

}
