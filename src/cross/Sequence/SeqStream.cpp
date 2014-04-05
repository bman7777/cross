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

SeqStream::SeqStream(Context* ctx) :
    mContext(ctx),
    mHead(NULL),
    mCurrentNode(NULL)
{
}

SeqStream::SeqStream(SeqNode* node, Context* ctx) :
    mContext(ctx),
    mHead(node),
    mCurrentNode(node)
{
}

SeqStream::SeqStream(IModuleWrapper* module, Context* ctx) :
    mContext(ctx)
{
    mHead = SequenceFactory::Get(mContext)->CreateSeqNode(module);
    mCurrentNode = mHead;
}

SeqStream::~SeqStream()
{
}

SeqStream::SeqStream(const SeqStream& other) :
    mHead(other.GetHead()),
    mCurrentNode(other.GetCurrent()),
    mStack(other.mStack),
    mContext(other.GetContext())
{
}

SeqStream& SeqStream::operator=(const SeqStream& other)
{
    mHead = other.GetHead();
    mCurrentNode = other.GetCurrent();
    mStack = other.mStack;

    return *this;
}

SeqStream& SeqStream::operator<<(IModuleWrapper& module)
{
    if(!mHead)
    {
        mHead = SequenceFactory::Get(mContext)->CreateSeqNode(&module);
        mCurrentNode = mHead;
    }
    else
    {
        mCurrentNode = mCurrentNode->Connect()->AddConnection(&module, DIR_BACKWARD);
    }
    return *this;
}

SeqStream& SeqStream::operator>>(IModuleWrapper& module)
{
    if(!mHead)
    {
        mHead = SequenceFactory::Get(mContext)->CreateSeqNode(&module);
        mCurrentNode = mHead;
    }
    else
    {
        mCurrentNode = mCurrentNode->Connect()->AddConnection(&module, DIR_FORWARD);
    }
    return *this;
}

SeqStream& SeqStream::operator<<(SeqNode& node)
{
    if(!mHead)
    {
        mHead = &node;
        mCurrentNode = mHead;
    }
    else
    {
        mCurrentNode = mCurrentNode->Connect()->AddConnection(&node, DIR_BACKWARD);
    }
    return *this;
}

SeqStream& SeqStream::operator>>(SeqNode& node)
{
    if(!mHead)
    {
        mHead = &node;
        mCurrentNode = mHead;
    }
    else
    {
        mCurrentNode = mCurrentNode->Connect()->AddConnection(&node, DIR_FORWARD);
    }
    return *this;
}

SeqStream& SeqStream::operator<<(Sequence& seq)
{
    if(!mHead)
    {
        mHead = &seq;
        mCurrentNode = mHead;
    }
    else
    {
        mCurrentNode = mCurrentNode->Connect()->AddConnection(&seq, DIR_BACKWARD);
    }
    return *this;
}

SeqStream& SeqStream::operator>>(Sequence& seq)
{
    if(!mHead)
    {
        mHead = &seq;
        mCurrentNode = mHead;
    }
    else
    {
        mCurrentNode = mCurrentNode->Connect()->AddConnection(&seq, DIR_FORWARD);
    }
    return *this;
}

SeqStream& SeqStream::operator<<(SeqStream& stream)
{
    if(!mHead)
    {
        mHead = stream.GetHead();
        mCurrentNode = stream.GetCurrent();
    }
    else
    {
        mCurrentNode = mCurrentNode->Connect()->AddConnection(&stream, DIR_BACKWARD);
    }
    return *this;
}

SeqStream& SeqStream::operator>>(SeqStream& stream)
{
    if(!mHead)
    {
        mHead = stream.GetHead();
        mCurrentNode = stream.GetCurrent();
    }
    else
    {
        mCurrentNode = mCurrentNode->Connect()->AddConnection(&stream, DIR_FORWARD);
    }
    return *this;
}

SeqStream& SeqStream::operator>>(Command type)
{
    if(!mHead)
    {
        if(type == Push)
        {
            Sequence* seq = SequenceFactory::Get(mContext)->CreateSequence();
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
            mStack.push(seq);
            seq->IntraConnect();
            mCurrentNode = mCurrentNode->Connect()->AddConnection(seq, DIR_FORWARD);
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

SeqStream& SeqStream::operator<<(Command type)
{
    // direction does not actually matter on these at the moment
    return SeqStream::operator>>(type);
}

}

