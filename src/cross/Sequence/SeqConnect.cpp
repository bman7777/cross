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

/// \brief construct a sequence connection with a context
///         that can be used in all future construction
SeqConnect::SeqConnect(Context* ctx)
{
    mContext = ctx == NULL ? GenesisContext::Get() : ctx;
}

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
/// \param out - the resulting node that is connected with- this
///         may be the passed in node or the existing node
///         that we were already connected to
/// \param in - the node to connect us to
/// \param dir - the direction of the connection
///         (forward/back)
/// \return T: a new node was created, F: new node wasn't created
bool SeqConnect::AddConnection(SeqNode*& out, SeqNode* in, Direction d)
{
    SeqPair* pair = FindConnection(in);
    if (!pair)
    {
        mConnect.push_back(SeqPair(in, d));
        out = in;
    }
    else
    {
        pair->second |= d;
        out = pair->first;
    }

    return false;
}

/// \brief add a connection to this node that involves a
///         direction and another module
/// \param out - the resulting node that is connected with- this
///         may be the passed in node that is already connected
///         and contains this module or a new node
/// \param module - the module to connect us to
/// \param dir - the direction of the connection
///         (forward/back)
/// \return T: a new node was created, F: new node wasn't created
bool SeqConnect::AddConnection(SeqNode*& out, IModuleWrapper* m, Direction d)
{
    bool isNew = false;
    SeqNode* returnNode = NULL;
    SeqPair* pair = FindConnection(m);
    if (!pair)
    {
        SeqNode* node = SequenceFactory::Get(mContext)->CreateSeqNode(m);
        isNew = true;

        mConnect.push_back(SeqPair(node, d));
        out = node;
    }
    else
    {
        isNew = false;
        pair->second |= d;
        out = pair->first;
    }

    return isNew;
}

/// \brief add a connection to this node that involves a
///         direction and another stream
/// \param out - the resulting node that is connected with- this
///         may be the passed in stream/head or a node that
///         is already connected
/// \param stream - the stream to connect us to
/// \param dir - the direction of the connection
///         (forward/back)
/// \return T: a new node was created, F: new node wasn't created
bool SeqConnect::AddConnection(SeqNode*& out, SeqStream* s, Direction d)
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

    out = s->GetCurrent();
    return false;
}

}
