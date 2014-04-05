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
            mDirectionStrategy = new AutoDirectionStrategy(DIR_FORWARD);
        }
    }
}

SequenceIterator::~SequenceIterator()
{
    if(mDirectionStrategy && mOwnsDirectionStrategy)
    {
        delete mDirectionStrategy;
    }
}

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
            Context* ctx = new Context(mContext);

            // this will run/instantiate the module
            mCurrentProgress->Run(ctx, this);
        }
        else
        {
            Continue(mContext, ERR_NONE);
        }
    }
}


}

