/****************************************************************/
/// \class Cross::SeqStream
/// \ingroup Sequence
/// \date Feb 24, 2014
/// \brief The construction of a sequence can be made using
///         modules, junction, and other sequences.  This is the
///         user's entry point for construction with a very
///         readable interface for forward/backward directions
///         that is customarily used in the world of streams.
/****************************************************************/

#include "cross/Service/SequenceFactory.h"
#include "cross/Context/IModuleWrapper.h"
#include "cross/Sequence/SeqNode.h"
#include "cross/Sequence/Sequence.h"
#include "cross/Sequence/SeqStream.h"

namespace Cross
{

/// \brief constructor for a stream that is capable of appending
///         sequenes, nodes, or modules in ordered fashion to
///         achieve a network of functionality
/// \param ctx - a context to use in creating new nodes for the
///         network.
SeqStream::SeqStream(Context* ctx) :
    mContext(ctx == NULL ? GenesisContext::Get() : ctx),
    mHead(NULL),
    mCurrentNode(NULL)
{
}

/// \brief constructor for a stream that is capable of appending
///         sequenes, nodes, or modules in ordered fashion to
///         achieve a network of functionality
/// \param node - a node is given as root to the stream
/// \param ctx - a context to use in creating new nodes for the
///         network.
SeqStream::SeqStream(SeqNode* node, Context* ctx) :
    mContext(ctx == NULL ? GenesisContext::Get() : ctx),
    mHead(node),
    mCurrentNode(node)
{
}

/// \brief constructor for a stream that is capable of appending
///         sequenes, nodes, or modules in ordered fashion to
///         achieve a network of functionality
/// \param module - a module is given as root to the stream
/// \param ctx - a context to use in creating new nodes for the
///               network.
SeqStream::SeqStream(IModuleWrapper* module, Context* ctx) :
    mContext(ctx == NULL ? GenesisContext::Get() : ctx)
{
    mHead = SequenceFactory::Get(mContext)->CreateSeqNode(module);
    mNodeTracker.push_back(mHead);
    mCurrentNode = mHead;
}

/// \brief copy constructor for stream.  This duplicates the
///         stream structure and variables into a new class.
/// \param other - the other stream which will not be modified
///         in the copy
SeqStream::SeqStream(const SeqStream& other) :
    mHead(other.GetHead()),
    mCurrentNode(other.GetCurrent()),
    mStack(other.mStack),
    mContext(other.GetContext())
{
}

SeqStream::~SeqStream()
{
    for(NodeTrackList::iterator i = mNodeTracker.begin(); i != mNodeTracker.end(); i++)
    {
        SequenceFactory::Get(mContext)->Destroy(*i);
    }
}

/// \brief equals operator for stream.  Functions much like the
///         copy constructor but allows common syntax.
/// \param other - the other stream which will not be modified
///         in the copy
SeqStream& SeqStream::operator=(const SeqStream& other)
{
    mHead = other.GetHead();
    mCurrentNode = other.GetCurrent();
    mStack = other.mStack;

    return *this;
}

/// \brief backwards push to the stream that appends a module
///         based on the state of the current node and the
///         head, if one exists.
/// \param module - a module passed by user to be pushed
/// \return the current progress of the stream
SeqStream& SeqStream::operator<<(IModuleWrapper& module)
{
    if(!mHead)
    {
        mHead = SequenceFactory::Get(mContext)->CreateSeqNode(&module);
        mNodeTracker.push_back(mHead);
        mCurrentNode = mHead;
    }
    else
    {
        bool isNew = mCurrentNode->Connect()->AddConnection(mCurrentNode, &module, DIR_BACKWARD);
        if(isNew)
        {
            mNodeTracker.push_back(mCurrentNode);
        }
    }
    return *this;
}

/// \brief forwards push to the stream that appends a module
///         based on the state of the current node and the
///         head, if one exists.
/// \param module - a module passed by user to be pushed
/// \return the current progress of the stream
SeqStream& SeqStream::operator>>(IModuleWrapper& module)
{
    if(!mHead)
    {
        mHead = SequenceFactory::Get(mContext)->CreateSeqNode(&module);
        mNodeTracker.push_back(mHead);
        mCurrentNode = mHead;
    }
    else
    {
        bool isNew = mCurrentNode->Connect()->AddConnection(mCurrentNode, &module, DIR_FORWARD);
        if(isNew)
        {
            mNodeTracker.push_back(mCurrentNode);
        }
    }
    return *this;
}

/// \brief backwards push to the stream that appends a node
///         based on the state of the current node and the
///         head, if one exists.
/// \param node - a node passed by user to be pushed
/// \return the current progress of the stream
SeqStream& SeqStream::operator<<(SeqNode& node)
{
    if(!mHead)
    {
        mHead = &node;
        mCurrentNode = mHead;
    }
    else
    {
        mCurrentNode->Connect()->AddConnection(mCurrentNode, &node, DIR_BACKWARD);
    }
    return *this;
}

/// \brief forwards push to the stream that appends a node
///         based on the state of the current node and the
///         head, if one exists.
/// \param node - a node passed by user to be pushed
/// \return the current progress of the stream
SeqStream& SeqStream::operator>>(SeqNode& node)
{
    if(!mHead)
    {
        mHead = &node;
        mCurrentNode = mHead;
    }
    else
    {
        mCurrentNode->Connect()->AddConnection(mCurrentNode, &node, DIR_FORWARD);
    }
    return *this;
}

/// \brief backwards push to the stream that appends a
///         sequence based on the state of the current node
///         and the head, if one exists.
/// \param seq - a sequence passed by user to be pushed
/// \return the current progress of the stream
SeqStream& SeqStream::operator<<(Sequence& seq)
{
    if(!mHead)
    {
        mHead = &seq;
        mCurrentNode = mHead;
    }
    else
    {
        mCurrentNode->Connect()->AddConnection(mCurrentNode, &seq, DIR_BACKWARD);
    }
    return *this;
}

/// \brief forwards push to the stream that appends a
///         sequence based on the state of the current node
///         and the head, if one exists.
/// \param seq - a sequence passed by user to be pushed
/// \return the current progress of the stream
SeqStream& SeqStream::operator>>(Sequence& seq)
{
    if(!mHead)
    {
        mHead = &seq;
        mCurrentNode = mHead;
    }
    else
    {
        mCurrentNode->Connect()->AddConnection(mCurrentNode, &seq, DIR_FORWARD);
    }
    return *this;
}

/// \brief backwards push of another stream that appends to
///         the current stream based on the state of the
///         current node and the head, if one exists.
/// \param stream - a stream passed by user to be pushed
/// \return the current progress of the stream
SeqStream& SeqStream::operator<<(SeqStream& stream)
{
    if(!mHead)
    {
        mHead = stream.GetHead();
        mCurrentNode = stream.GetCurrent();
    }
    else
    {
        mCurrentNode->Connect()->AddConnection(mCurrentNode, &stream, DIR_BACKWARD);
    }
    return *this;
}

/// \brief forwards push of another stream that appends to
///         the current stream based on the state of the
///         current node and the head, if one exists.
/// \param stream - a stream passed by user to be pushed
/// \return the current progress of the stream
SeqStream& SeqStream::operator>>(SeqStream& stream)
{
    if(!mHead)
    {
        mHead = stream.GetHead();
        mCurrentNode = stream.GetCurrent();
    }
    else
    {
        mCurrentNode->Connect()->AddConnection(mCurrentNode, &stream, DIR_FORWARD);
    }
    return *this;
}

/// \brief the commands push/pop allow a new sequence
///         context to be created in-place and joined
///         into the current progress of the stream.
/// \param type - what kind of command to run (e.g. push
///         or pop)
/// \return the current progress of the stream
SeqStream& SeqStream::operator>>(Command type)
{
    if(!mHead)
    {
        if(type == Push)
        {
            Sequence* seq = SequenceFactory::Get(mContext)->CreateSequence();
            mNodeTracker.push_back(seq);
            seq->IntraConnect();
            mStack.push(seq);
            mHead = seq;
            mCurrentNode = mHead;
        }
    }
    else
    {
        if(type == Push)
        {
            Sequence* seq = SequenceFactory::Get(mContext)->CreateSequence();
            mNodeTracker.push_back(seq);
            mStack.push(seq);
            seq->IntraConnect();
            mCurrentNode->Connect()->AddConnection(mCurrentNode, seq, DIR_FORWARD);
        }
        else if(type == Pop)
        {
            if(!mStack.empty())
            {
                Sequence* seq = mStack.top();
                seq->InterConnect();
                mCurrentNode = seq;
                mStack.pop();
            }
        }
    }
    return *this;
}

/// \brief for symmetry/compatibility we also provide the
///         reverse of the commands push/pop however there
///         is currently no difference in its function.
/// \param type - what kind of command to run (e.g. push
///         or pop)
/// \return the current progress of the stream
SeqStream& SeqStream::operator<<(Command type)
{
    // direction does not actually matter on these at the moment
    return SeqStream::operator>>(type);
}

}

