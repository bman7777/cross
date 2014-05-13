/****************************************************************/
/// \class Cross::SequenceIterator
/// \ingroup Sequence
/// \date Jan 6, 2014
/// \brief Iterate through sequence nodes and run each one in
///         turn.  When the end of the node sequence has been
///         reached call the continuer.
/****************************************************************/

#include "cross/Context/Continuer.h"
#include "cross/Context/Context.h"
#include "cross/Sequence/AutoDirectionStrategy.h"
#include "cross/Sequence/Sequence.h"
#include "cross/Sequence/SequenceIterator.h"

namespace Cross
{

/// \brief construct the sequence iterator so it can be used to
///         traverse the sequence tree.
/// \param root - the sequence node that will serve as a start
///         for traversal
/// \param strategy - decision-maker for path selection as we run
SequenceIterator::SequenceIterator(SeqNode* root, IDirectionStrategy* strat) :
    mCurrentProgress(root),
    mDirectionStrategy(strat),
    mOwnsDirectionStrategy(false),
    mIsRunning(false),
    mCompletedContinuer(NULL),
    mContext(NULL)
{
    if(mCurrentProgress)
    {
        if(mDirectionStrategy == NULL)
        {
            mOwnsDirectionStrategy = true;
            mDirectionStrategy = Allocation::Get(mContext)->New<AutoDirectionStrategy>(DIR_FORWARD);
        }
    }
}

/// \brief destructor for iterator which cleans up temp
///         memory allocation(s)
SequenceIterator::~SequenceIterator()
{
    if(mDirectionStrategy && mOwnsDirectionStrategy)
    {
        Allocation::Get(mContext)->Delete(mDirectionStrategy);
    }

    mContextTracker.clear();
}

/// \brief each step in the traversal will continue and allow
///         the iterator to advance to the next stage
/// \param context - context that was run with
/// \param error - any errors that occurred are specified here
void SequenceIterator::Continue(Context* ctx, ErrorCode e)
{
    if(mDirectionStrategy)
    {
        mCurrentProgress = mDirectionStrategy->GetNextNode(mCurrentProgress->Connect(), e);
    }

    bool pendingRun = false;
    if(mCurrentProgress)
    {
        pendingRun = true;

        // start new run
        mCurrentProgress->Run(ctx, this);
    }

    if(!pendingRun && mCompletedContinuer)
    {
        mCompletedContinuer->Continue(mContext, e);
    }
}

/// \brief entry point for sequence iteration- this will
///         start up a new context that can be used to
///         localize services.
/// \param context - the context to fork and run with
/// \param continuer - when done with running, call this
void SequenceIterator::Run(Context* ctx, Continuer* cnt)
{
    if(!mIsRunning)
    {
        mContext = ctx;
        mCompletedContinuer = cnt;
        mIsRunning = true;

        if(mCurrentProgress)
        {
            // make a shiny new context for module
            ContextTrackList::iterator iter = mContextTracker.emplace(mContextTracker.end(), mContext);

            // this will run/instantiate the module
            mCurrentProgress->Run(&(*iter), this);
        }
        else
        {
            Continue(mContext, ERR_NONE);
        }
    }
}

}

