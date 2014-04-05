/****************************************************************/
/// \class Cross::Junction
/// \ingroup Sequence
/// \date Feb 10, 2014
/// \brief A junction is a point in a sequence that contains
///         several routes to new sequences.  The chosen route
///         will rely on direction strategies.  A junction is
///         definable by a user, and can be streamed from like
///         a standard sequence stream.
/****************************************************************/

#include "cross/Service/SequenceFactory.h"
#include "cross/Sequence/AutoDirectionStrategy.h"
#include "cross/Sequence/Junction.h"
#include "cross/Sequence/RunContext.h"
#include "cross/Sequence/SeqStream.h"
#include "cross/Sequence/Sequence.h"

namespace Cross
{

Junction::Junction(IDirectionStrategy* strat, Context* ctx) :
    SeqNode(ctx),
    mOwnsDirectionStrategy(false),
    mContext(ctx),
    mStrategy(strat)
{
    mRoot = SequenceFactory::Get(mContext)->CreateSeqNode();
    if(!mStrategy)
    {
        mOwnsDirectionStrategy = true;
        mStrategy = new AutoDirectionStrategy(DIR_FORWARD);
    }
}

Junction::~Junction()
{
    if(mStrategy && mOwnsDirectionStrategy)
    {
        delete mStrategy;
    }
}

void Junction::Run(Context* ctx, Continuer* cnt)
{
    SeqNode* node;
    if(mStrategy)
    {
        node = mStrategy->GetNextNode(mRoot->Connect(), ERR_NONE);
    }

    RunContext::BeginRun(ctx, cnt, node);
}

SeqStream Junction::operator<<(IModuleWrapper& module)
{
    SeqStream stream(mContext);
    stream<<*mRoot<<SeqStream::Push<<module;

    return stream;
}

SeqStream Junction::operator>>(IModuleWrapper& module)
{
    SeqStream stream(mContext);
    stream>>*mRoot>>SeqStream::Push>>module;

    return stream;
}

SeqStream Junction::operator<<(SeqNode& node)
{
    SeqStream stream(mContext);
    stream<<*mRoot<<SeqStream::Push<<node;

    return stream;
}

SeqStream Junction::operator>>(SeqNode& node)
{
    SeqStream stream(mContext);
    stream>>*mRoot>>SeqStream::Push>>node;

    return stream;
}

SeqStream Junction::operator<<(Sequence& sequence)
{
    SeqStream stream(mContext);
    stream<<*mRoot<<SeqStream::Push<<sequence;

    return stream;
}

SeqStream Junction::operator>>(Sequence& sequence)
{
    SeqStream stream(mContext);
    stream>>*mRoot>>SeqStream::Push>>sequence;

    return stream;
}

SeqStream Junction::operator<<(SeqStream& stream)
{
    SeqStream outStream(mContext);
    outStream<<*mRoot<<SeqStream::Push<<stream;

    return outStream;
}

SeqStream Junction::operator>>(SeqStream& stream)
{
    SeqStream outStream(mContext);
    outStream>>*mRoot>>SeqStream::Push>>stream;

    return outStream;
}

}


