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

#include "cross/Service/Allocation.h"
#include "cross/Sequence/AutoDirectionStrategy.h"
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
    mRoot = Allocation::Get(ctx)->New<SeqNode>(ctx);
    if(!mStrategy)
    {
        mOwnsDirectionStrategy = true;
        mStrategy = Allocation::Get(ctx)->New<AutoDirectionStrategy>(DIR_FORWARD);
    }
}

/// \brief destructor for junction that destroys all
///         local allocations
Junction::~Junction()
{
    mStreamTracker.clear();

    if(mStrategy && mOwnsDirectionStrategy)
    {
        Allocation::Get(GetContext())->Delete(mStrategy);
    }

    Allocation::Get(GetContext())->Delete(mRoot);
}

/// \brief run the junction based on the state of the system
/// \param ctx -  context to propagate through the run
/// \param cnt - continuer to use when the run is complete
void Junction::Run(Context* ctx, Continuer* cnt)
{
    SeqNode* node;
    if(mStrategy)
    {
        node = mStrategy->GetNextNode(mRoot, ERR_NONE);
    }

    RunContext::BeginRun(ctx, cnt, node);
}

/// \brief append a module to the junction
/// \param which module to append
SeqStream& Junction::operator<<(IModuleWrapper& module)
{
    StreamTrackList::iterator iter = mStreamTracker.emplace(mStreamTracker.end(), mRoot, GetContext());
    *iter<<SeqStream::Push<<module;

    return *iter;
}

/// \brief append a module to the junction
/// \param which module to append
SeqStream& Junction::operator>>(IModuleWrapper& module)
{
    StreamTrackList::iterator iter = mStreamTracker.emplace(mStreamTracker.end(), mRoot, GetContext());
    *iter>>SeqStream::Push>>module;

    return *iter;
}

/// \brief append a junction to the junction
/// \param which node to append
SeqStream& Junction::operator<<(Junction& j)
{
    StreamTrackList::iterator iter = mStreamTracker.emplace(mStreamTracker.end(), mRoot, GetContext());
    *iter<<SeqStream::Push<<j;

    return *iter;
}

/// \brief append a junction to the junction
/// \param which node to append
SeqStream& Junction::operator>>(Junction& j)
{
    StreamTrackList::iterator iter = mStreamTracker.emplace(mStreamTracker.end(), mRoot, GetContext());
    *iter>>SeqStream::Push>>j;

    return *iter;
}

/// \brief append a stream to the junction
/// \param which stream to append
SeqStream& Junction::operator<<(SeqStream& inStream)
{
    StreamTrackList::iterator iter = mStreamTracker.emplace(mStreamTracker.end(), mRoot, GetContext());
    *iter<<SeqStream::Push<<inStream;

    return *iter;
}

/// \brief append a stream to the junction
/// \param which stream to append
SeqStream& Junction::operator>>(SeqStream& inStream)
{
    StreamTrackList::iterator iter = mStreamTracker.emplace(mStreamTracker.end(), mRoot, GetContext());
    *iter>>SeqStream::Push>>inStream;

    return *iter;
}

}


