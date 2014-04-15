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

/// \brief find a module connection to this node and return the
///         resulting connection
/// \param module - module to check against
/// \return pair that contains the match (or NULL if no match was
///         found)
SeqConnect::SeqPair* SeqConnect::FindConnection(IModuleWrapper* module)
{
    SeqPair* pair = NULL;
    for (Connection::iterator i = mConnect.begin(); i != mConnect.end(); i++)
    {
        if (*(i->first) == module)
        {
            pair = &(*i);
            break;
        }
    }

    return pair;
}

/// \brief find a node connection to this node and return the
///         resulting connection
/// \param node - node to check against
/// \return pair that contains the match (or NULL if no match was
///         found)
SeqConnect::SeqPair* SeqConnect::FindConnection(SeqNode* node)
{
    SeqPair* pair = NULL;
    for (Connection::iterator i = mConnect.begin(); i != mConnect.end(); i++)
    {
        if (i->first == node)
        {
            pair = &(*i);
            break;
        }
    }

    return pair;
}

/// \brief add a connection to this node that involves a
///         direction and another node
/// \param node - the node to connect us to
/// \param dir - the direction of the connection
///         (forward/back)
/// \return the resulting node that is connected with- this
///         may be the passed in node or the existing node
///         that we were already connected to
SeqNode* SeqConnect::AddConnection(SeqNode* n, Direction d)
{
    SeqNode* returnNode = NULL;
    SeqPair* pair = FindConnection(n);
    if (!pair)
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

/// \brief add a connection to this node that involves a
///         direction and another module
/// \param module - the module to connect us to
/// \param dir - the direction of the connection
///         (forward/back)
/// \return the resulting node that is connected with- this
///         may be the passed in node that is already connected
///         and contains this module or a new node
SeqNode* SeqConnect::AddConnection(IModuleWrapper* m, Direction d)
{
    SeqNode* returnNode = NULL;
    SeqPair* pair = FindConnection(m);
    if (!pair)
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

/// \brief add a connection to this node that involves a
///         direction and another stream
/// \param stream - the stream to connect us to
/// \param dir - the direction of the connection
///         (forward/back)
/// \return the resulting node that is connected with- this
///         may be the passed in stream/head or a node that
///         is already connected
SeqNode* SeqConnect::AddConnection(SeqStream* s, Direction d)
{
    SeqPair* pair = FindConnection(s->GetHead());
    if (!pair)
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
