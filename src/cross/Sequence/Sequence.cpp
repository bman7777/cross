/****************************************************************/
/// \class Cross::Sequence
/// \ingroup Sequence
/// \date Jan 5, 2014
/// \brief Sequences are networks of nodes.  They carry an
///         isolated context that allows sequences to operate
///         separately from all other surrounding sequences.
/****************************************************************/

#include "cross/Sequence/RunContext.h"
#include "cross/Sequence/SeqNode.h"
#include "cross/Sequence/Sequence.h"
#include "cross/Sequence/SeqStream.h"
#include "cross/Service/Allocation.h"

namespace Cross
{

/// \brief constructor for sequences to contain a flow of
///         sequence nodes
/// \param ctx - context for construction
Sequence::Sequence(Context* ctx) : SeqNode(ctx), mContext(ctx), mRoot(NULL), mIntraConnect(true)
{
}

/// \brief run a sequence to completion
/// \param ctx - a context for the run to propagate
/// \param cnt - a continuer to call on completion
void Sequence::Run(Context* ctx, Continuer* cnt)
{
    if(mRoot)
    {
        RunContext::BeginRun(ctx, cnt, mRoot);
    }
    else
    {
        SeqNode::Run(ctx, cnt);
    }
}

/// \brief determine if this sequence is equal to
///         a module based on the root node
/// \return T: if module is a match; F: if not a match
bool Sequence::operator==(IModuleWrapper* mod) const
{
    bool isSame = false;
    if(mRoot)
    {
        isSame = (*mRoot == mod);
    }
    else
    {
        isSame = SeqNode::operator==(mod);
    }
    return isSame;
}

/// \brief add a connection to this sequence that involves a
///         direction and another node
/// \param out - the resulting node that is connected with- this
///         may be the passed in node or the existing node
///         that we were already connected to
/// \param in - the node to connect us to
/// \param dir - the direction of the connection
///         (forward/back)
/// \return T: a new node was created, F: new node wasn't created
bool Sequence::AddConnection(SeqNode*& out, SeqNode* in, Direction d)
{
    bool isNew = false;
    if(mIntraConnect)
    {
        if(mRoot)
        {
            isNew = mRoot->AddConnection(out, in, d);
        }
        else
        {
            mRoot = in;
            out = mRoot;
        }
    }
    else
    {
        isNew = SeqNode::AddConnection(out, in, d);
    }

    return isNew;
}

/// \brief add a connection to this sequence that involves a
///         direction and another module
/// \param out - the resulting node that is connected with- this
///         may be the passed in node or a newly created module
/// \param in - the node to connect us to
/// \param dir - the direction of the connection
///         (forward/back)
/// \return T: a new node was created, F: new node wasn't created
bool Sequence::AddConnection(SeqNode*& out, IModuleWrapper* m, Direction d)
{
    bool isNew = false;
    if(mIntraConnect)
    {
        if(mRoot)
        {
            isNew = mRoot->AddConnection(out, m, d);
        }
        else
        {
            mRoot = Allocation::Get(mContext)->New<SeqNode>(mContext, m);
            isNew = true;
            out = mRoot;
        }
    }
    else
    {
        isNew = SeqNode::AddConnection(out, m, d);
    }

    return isNew;
}

/// \brief add a connection to this sequence that involves a
///         direction and another stream's head
/// \param out - the resulting node that is connected with- this
///         may be the passed in stream's head or an existing node
/// \param in - the node to connect us to
/// \param dir - the direction of the connection
///         (forward/back)
/// \return T: a new node was created, F: new node wasn't created
bool Sequence::AddConnection(SeqNode*& out, SeqStream* s, Direction d)
{
    bool isNew = false;
    if(mIntraConnect)
    {
        if(mRoot)
        {
            isNew = mRoot->AddConnection(out, s->GetHead(), d);
        }
        else
        {
            mRoot = s->GetHead();
            out = mRoot;
        }
    }
    else
    {
        isNew = SeqNode::AddConnection(out, s->GetHead(), d);
    }

    return isNew;
}

}
