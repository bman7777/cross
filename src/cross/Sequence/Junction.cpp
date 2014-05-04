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
#include "cross/Sequence/GenesisContext.h"
#include "cross/Sequence/Junction.h"
#include "cross/Sequence/RunContext.h"
#include "cross/Sequence/SeqStream.h"
#include "cross/Sequence/Sequence.h"

namespace Cross
{

/// \brief constructor for Junctions
/// \param strategy - strategy to determine the next node
///         when processing a current node
/// \param ctx - context for all junction construction
Junction::Junction(IDirectionStrategy* strat, Context* ctx) :
    SeqNode(ctx),
    mOwnsDirectionStrategy(false),
    mStrategy(strat)
{
    if(ctx == NULL)
    {
        ctx = GenesisContext::Get();
    }

    mSeqFactory = SequenceFactory::Get(ctx);
    mRoot = mSeqFactory->CreateSeqNode();
    if(!mStrategy)
    {
        mOwnsDirectionStrategy = true;
        mStrategy = new AutoDirectionStrategy(DIR_FORWARD);
    }
}

/// \brief destructor for junction that destroys all
///         local allocations
Junction::~Junction()
{
    mStreamTracker.clear();

    if(mStrategy && mOwnsDirectionStrategy)
    {
        delete mStrategy;
    }

    mSeqFactory->Destroy(mRoot);
}

/// \brief run the junction based on the state of the system
/// \param ctx -  context to propagate through the run
/// \param cnt - continuer to use when the run is complete
void Junction::Run(Context* ctx, Continuer* cnt)
{
    SeqNode* node;
    if(mStrategy)
    {
        node = mStrategy->GetNextNode(mRoot->Connect(), ERR_NONE);
    }

    RunContext::BeginRun(ctx, cnt, node);
}

/// \brief append a module to the junction
/// \param which module to append
SeqStream& Junction::operator<<(IModuleWrapper& module)
{
    StreamTrackList::iterator iter = mStreamTracker.emplace(mStreamTracker.end(), GetContext());
    *iter<<*mRoot<<SeqStream::Push<<module;

    return *iter;
}

/// \brief append a module to the junction
/// \param which module to append
SeqStream& Junction::operator>>(IModuleWrapper& module)
{
    StreamTrackList::iterator iter = mStreamTracker.emplace(mStreamTracker.end(), GetContext());
    *iter>>*mRoot>>SeqStream::Push>>module;

    return *iter;
}

/// \brief append a node to the junction
/// \param which node to append
SeqStream& Junction::operator<<(SeqNode& node)
{
    StreamTrackList::iterator iter = mStreamTracker.emplace(mStreamTracker.end(), GetContext());
    *iter<<*mRoot<<SeqStream::Push<<node;

    return *iter;
}

/// \brief append a node to the junction
/// \param which node to append
SeqStream& Junction::operator>>(SeqNode& node)
{
    StreamTrackList::iterator iter = mStreamTracker.emplace(mStreamTracker.end(), GetContext());
    *iter>>*mRoot>>SeqStream::Push>>node;

    return *iter;
}

/// \brief append a sequence to the junction
/// \param which sequence to append
SeqStream& Junction::operator<<(Sequence& sequence)
{
    StreamTrackList::iterator iter = mStreamTracker.emplace(mStreamTracker.end(), GetContext());
    *iter<<*mRoot<<SeqStream::Push<<sequence;

    return *iter;
}

/// \brief append a sequence to the junction
/// \param which sequence to append
SeqStream& Junction::operator>>(Sequence& sequence)
{
    StreamTrackList::iterator iter = mStreamTracker.emplace(mStreamTracker.end(), GetContext());
    *iter>>*mRoot>>SeqStream::Push>>sequence;

    return *iter;
}

/// \brief append a stream to the junction
/// \param which stream to append
SeqStream& Junction::operator<<(SeqStream& inStream)
{
    StreamTrackList::iterator iter = mStreamTracker.emplace(mStreamTracker.end(), GetContext());
    *iter<<*mRoot<<SeqStream::Push<<inStream;

    return *iter;
}

/// \brief append a stream to the junction
/// \param which stream to append
SeqStream& Junction::operator>>(SeqStream& inStream)
{
    StreamTrackList::iterator iter = mStreamTracker.emplace(mStreamTracker.end(), GetContext());
    *iter>>*mRoot>>SeqStream::Push>>inStream;

    return *iter;
}

}


